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
		if (Stacks[columna]->getSize() < 13) return;
		LinkedList<Card>* ladder = Stacks[columna]->slice(Stacks[columna]->getSize() - 13, Stacks[columna]->getSize());
		ladder->goToStart();

		for (int i = 0; i < 12; i++) {
			Card currentCard = ladder->getElement();
			ladder->next();
			Card nextCard = ladder->getElement();
			if (!nextCard.isDescending(currentCard)) {
				delete ladder;
				return;
			}
		}

		delete ladder;
		ladder = Stacks[columna]->cutTail(13);
		completeLadder->push(ladder);
	}

	void guardarEstado() {
		SpiderState* estado = new SpiderState(Stacks, cardReserve, completeLadder);
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
		cardReserve->clear();
		for (int i = 0; i < 10; i++) {
			Stacks[i]->clear();
		}
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
		SpiderState::reiniciarMovimientos();
		limpiarHistorial();
		cardReserve->clear();
		completeLadder->clear();

		spiderDeck = Deck(2, Card::SPADES);
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
		cout << "Card Reserve: " << cardReserve->topValue() << "x" << cardReserve->getSize() << endl;
	}

	void imprimirCompleteLadders() {
		if (completeLadder->isEmpty()) return;

		LinkedStack<LinkedList<Card>*>* nuevoLadder = new LinkedStack<LinkedList<Card>*>(*completeLadder);
		LinkedStack<LinkedList<Card>*> listaLadder;

		while (!nuevoLadder->isEmpty()) {
			listaLadder.push(nuevoLadder->pop());
		}


		int maxStackSize = 0;
		LinkedStack<LinkedList<Card>*>  listaLadderTemp = listaLadder;
		while (!listaLadderTemp.isEmpty()) {
			int cantidadLadder = listaLadderTemp.pop()->getSize();
			if (cantidadLadder > maxStackSize)
				maxStackSize = cantidadLadder;
		}
		
		for (int row = 0; row < maxStackSize; row++) {
			LinkedStack<LinkedList<Card>*> listaLadderTemp2 = listaLadder;
			while (!listaLadderTemp2.isEmpty()) {
				LinkedList<Card>* ladder = listaLadderTemp2.pop();

				if (row < ladder->getSize()) {
					ladder->goToPos(row);
					cout << ladder->getElement() << " ";
				}
				else {
					cout << "   "; 
				}
			}
			cout << endl;
		}
		delete nuevoLadder;
	}

	void deshacer() {
		deshacerMovimiento();
	}

	void imprimirMovimientos() {
		cout << "Movimientos: " << SpiderState::getMovimientos() << endl;
	}

	void solicitarCartas(bool start = false) {
		if (cardReserve->getSize() < 10)
			return;

		guardarEstado();
		for (int i = 0; i < 10; i++) {
			Card card = cardReserve->pop();
			card.FaceUp = true;
			Stacks[i]->append(card);
		}
	}

	// Columnas 0-9
	bool moverCartas(int columna, int cantidad, int destino) {
		// Hacer slice 
		if (columna < 0 || columna > 9 || destino < 0 || destino > 9 || cantidad <= 0) {
			cout << "Movimiento invalido" << endl;
			return false;
		}
		if (Stacks[columna]->getSize() < cantidad) {
			cout << "Movimiento invalido" << endl;
			return false;
		}
		LinkedList<Card>* columnaOrigen = Stacks[columna];
		LinkedList<Card>* columnaDestino = Stacks[destino];
		LinkedList<Card>* movingCards = columnaOrigen->slice(columnaOrigen->getSize() - cantidad, columnaOrigen->getSize());

		// Verificar que la escalera solicitada para mover sea valida
		Card previousCard;
		for (movingCards->goToStart(); !movingCards->atEnd(); movingCards->next()) {
			if (!movingCards->getElement().FaceUp) {
				cout << "Movimiento invalido" << endl;
				delete movingCards;
				return false;
			}
			if (movingCards->atStart()) {
				previousCard = movingCards->getElement();
				continue;
			}

			Card currentCard = movingCards->getElement();
			if (!currentCard.isDescending(previousCard)) {
				cout << "Movimiento invalido" << endl;
				delete movingCards;
				return false; 
			}
			previousCard = movingCards->getElement();
		}

		// Verificar que la base de la escalera a mover sea descendiente a la base de la columna destino
		if (!columnaDestino->isEmpty()) {
			movingCards->goToStart();
			columnaDestino->goToEnd();
			columnaDestino->previous();

			Card baseCard = movingCards->getElement();
			Card baseDestino = columnaDestino->getElement();
			if (!baseCard.isDescending(baseDestino)) {
				cout << "Movimiento invalido" << endl;
				delete movingCards;
				return false;
			}
		}

		// Realizar el movimiento
		guardarEstado();
		cout << columnaOrigen->getSize() << endl;
		LinkedList<Card>* newTail = columnaOrigen->cutTail(cantidad);
		columnaDestino->append(movingCards);
		columnaOrigen->goToEnd();
		columnaOrigen->previous();

		if (!columnaOrigen->isEmpty() && !columnaOrigen->getElement().FaceUp) {
			Card flippedCard = columnaOrigen->getElement();
			flippedCard.FaceUp = true;
			columnaOrigen->setElement(flippedCard);
		}

		delete newTail;
		delete movingCards;
		escaleraCompleta(destino);
		return true;
	}

	bool rondaTerminada() {
		for (int i = 0; i < 10; i++) {
			if (Stacks[i]->isEmpty()) continue;
			return false;
		}

		return true;
	}

	~SpiderGame() {
		
		for (int i = 0; i < 10; i++) {
			delete Stacks[i];
		}
		delete cardReserve;
		delete completeLadder;
		delete GameStates;
	}

	void imprimirNumeroColumnas() {
		for (int i = 0; i < 10; i++) {
			cout << "  " << i + 1 << "   ";
		}
		cout << endl;
		for (int i = 0; i < 10; i++) {
			cout << "  ↓   ";
		}
		cout << endl;
	}

	void print() {
		cout << endl;
		imprimirMovimientos();
		imprimirNumeroColumnas();
		imprimirStacks();
		imprimirCardReserve();
		imprimirCompleteLadders();
		cout << endl;
	}

};