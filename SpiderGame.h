#pragma once
#include "Stack.h"
#include "Card.h"
#include "Deck.h"
#include "SpiderState.h"
#include "LinkedStack.h"

class SpiderGame
{
private:
	Deck spiderDeck;
	LinkedStack<SpiderState*>* GameStates;
	LinkedList<Card>* Stacks[10];
	LinkedStack<Card>* cardReserve;
	LinkedStack<LinkedList<Card>*>* completeLadder;


	void escaleraCompleta(int columna) {
		// Fondo del stack es la carta mas baja
		// Tope del stack es la carta mas alta
		// Si hay una escalera completa, entonces la más alta debe ser K y la más baja A, osea una distancia de 12

		if (Stacks[columna]->getSize() < 12) return;
		LinkedList<Card>* ladder = Stacks[columna]->slice(Stacks[columna]->getSize() - 12, Stacks[columna]->getSize() + 1);

		completeLadder->push(ladder);
	}

	void nuevoMovimiento() {
		SpiderState* estado = new SpiderState(Stacks, cardReserve, completeLadder);
		estado->movimientos = GameStates->isEmpty() ? 1 : GameStates->topValue()->movimientos + 1;
		GameStates->push(estado);

	}


	void deshacerMovimiento() {

		if (GameStates->isEmpty()) {
			cout << "No hay movimientos para deshacer" << endl;
			return;
		}

		SpiderState* estadoAnterior = GameStates->pop();


		delete completeLadder;
		delete cardReserve;
		for (int i = 0; i < 10; i++) {
			delete Stacks[i];
		}

		completeLadder = estadoAnterior->listCompleteLeader;
		cardReserve = estadoAnterior->listCardReserve;
		for (int i = 0; i < 10; i++) {
			Stacks[i] = estadoAnterior->Stacks[i];
		}

		estadoAnterior->listCompleteLeader = nullptr;
		estadoAnterior->listCardReserve = nullptr;
		for (int i = 0; i < 10; i++) {
			estadoAnterior->Stacks[i] = nullptr;
		}
		delete estadoAnterior;
	}


	void repartirNaipe(Deck currentDeck) {
		currentDeck.shuffle();

		for (int col = 0; col < 10; col++) {
			int cantidadCartas = (col < 4) ? 6 : 5; 
			for (int row = 0; row < cantidadCartas; row++) {
				Card card = currentDeck.drawCard();
				card.FaceUp = false;
				if (row == cantidadCartas - 1)  
					card.FaceUp = true;
				Stacks[col]->append(card);
			}
		}

		while (currentDeck.getSize() != 0) {
			Card card = currentDeck.drawCard();
			card.FaceUp = false;
			cardReserve->push(card);
		}
	}

	void limpiarHistorial() {
		while (!GameStates->isEmpty()) {
			SpiderState* estado = GameStates->pop();
			delete estado;
		}
	}

public:
	SpiderGame() {
		cardReserve = new LinkedStack<Card>();
		for (int stackIndex = 0; stackIndex < 10; stackIndex++) {
			Stacks[stackIndex] = new LinkedList<Card>();
		}
		completeLadder = new LinkedStack<LinkedList<Card>*>();
		GameStates = new LinkedStack<SpiderState*>();
	}

	void inicializarJuego() {
		spiderDeck = Deck(2);
		repartirNaipe(spiderDeck);
	}


	void imprimirStacks() {
		int maxStackSize = 0;
		for (int i = 0; i < 10; i++) {
			if (maxStackSize < Stacks[i]->getSize()) 
				maxStackSize = Stacks[i]->getSize();
		}
		for (int row = 0; row < maxStackSize; row++) {
			for (int col = 0; col < 10; col++) {
				if (Stacks[col]->getSize() <= row) {
					cout << "      ";
					continue;
				}
				Stacks[col]->goToPos(row);
				cout << Stacks[col]->getElement() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void imprimirCardReserve() {
		if (cardReserve->isEmpty()) {
			cout << "Card Reserve: " << "(Vacia) " << endl;
			return;
		}
		cout << "Card Reserve: " << completeLadder->topValue() << "x" << cardReserve->getSize() << endl;
	}

	void imprimirCardLadderComplete() {
		cout << "Card Ladder Complete: " << completeLadder->topValue() << endl;
	}

	void deshacer() {
		deshacerMovimiento();
	}

	void imprimirMovimientos() {
		if (GameStates->isEmpty()) {
			cout << "Movimientos: 0" << endl;
			return;
		}
		cout << "Movimientos: " << GameStates->topValue()->movimientos << endl;
	}

	void solicitarCartas(bool start = false) {
		if (cardReserve->getSize() < 10)
			return;
		for (int i = 0; i < 10; i++) {
			if (Stacks[i]->getSize() == 0)
				return; // Si hay alguna columna vacía no permite está acción
		}
		for (int i = 0; i < 10; i++) {
			Stacks[i]->append(cardReserve->pop());
		}
		nuevoMovimiento();
	}



	~SpiderGame() {
		
		for (int i = 0; i < 10; i++) {
			delete Stacks[i];
		}
		delete cardReserve;
		delete completeLadder;
		delete GameStates;
	}

};

