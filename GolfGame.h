#pragma once
#include "Stack.h"
#include "Card.h"
#include "Deck.h"
#include "GolfState.h"
#include "LinkedStack.h"

/*
 *	GolfGame.h - Clase juego que representa el juego de Soliario Golf
 *	Colaboradores:
 *	- Daniel Caleb Vargas Mora - 10/7/2025 Creación de la clase
 *  - David Alonso Vega Hidalgo - 10/7/2025 Agregación de funcionalidades
 *	Descripcion: 
 *	- Representa el juego Solitario Golf, contiene las funciones necesarias
 *	para inicializar el juego, llevar a cabo sus acciones disponibles y 
 *  validar el gane o pierde de la ronda.
 *  - Imprimir en pantalla el juego actual.
 */

class GolfGame
{
private:
	Deck golfDeck;
	Stack<GolfState*>* GameStates;
	LinkedList<Card>* Stacks[7];
	LinkedStack<Card>* Hand;
	LinkedStack<Card>* Discards;
	
	void repartirNaipe(Deck currentDeck) {
		Hand->clear();
		for (int i = 0; i < 7; i++) {
			Stacks[i]->clear();
		}
		currentDeck.shuffle();

		// Repartir 5 cartas a cada una de las 7 pilas (Stacks)
		// Encargado David
        for (int col = 0; col < 7; col++){
            for (int row = 0; row < 5; row++){
                Card card = currentDeck.drawCard();
                card.FaceUp = true;
                Stacks[col]->append(card);
            }
        }

        // Repartir el resto del naipe al mazo (Hand)
        // Encargado David
		
		while (currentDeck.getSize() != 0){
			Card card = currentDeck.drawCard();
			card.FaceUp = false;
            Hand->push(card);
        }

		voltearCarta(true);
	}

	void deshacerMovimiento() {
		if (GameStates->isEmpty()) {
			cout << "No hay movimientos para deshacer" << endl;
			return;
		}

		GolfState* estadoAnterior = GameStates->pop();

		delete Discards;
		delete Hand;
		for (int i = 0; i < 7; i++) {
			delete Stacks[i];
		}

		Discards = estadoAnterior->Discards;
		Hand = estadoAnterior->Hand;
		for (int i = 0; i < 7; i++) {
			Stacks[i] = estadoAnterior->Stacks[i];
		}

		estadoAnterior->Discards = nullptr;
		estadoAnterior->Hand = nullptr;
		for (int i = 0; i < 7; i++) {
			estadoAnterior->Stacks[i] = nullptr;
		}
		delete estadoAnterior;
	};

	void nuevoMovimiento() {
		GolfState* estado = new GolfState(Stacks, Hand, Discards);
		GameStates->push(estado);
	};

	void limpiarHistorial() {
		while (!GameStates->isEmpty()) {
			GolfState* estado = GameStates->pop();
			delete estado;
		}
	}

public:
	GolfGame() {
		Hand = new LinkedStack<Card>();
		for (int stackIndex = 0; stackIndex < 7; stackIndex++) {
			Stacks[stackIndex] = new LinkedList<Card>();
		}
		Discards = new LinkedStack<Card>();
		GameStates = new LinkedStack<GolfState*>();
	}

	void deshacer() {
		deshacerMovimiento();
	}

	void inicializarJuego() {
		GolfState::reiniciarMovimientos();
		limpiarHistorial();
		Discards->clear();

		golfDeck = Deck();
		repartirNaipe(golfDeck);
	}

	bool rondaTerminada() {
		
		if (Hand->isEmpty()) {
			for (int i = 0; i < 7; i++) {
				Card descarteTope = Discards->topValue();
				if (Stacks[i]->isEmpty()) continue;
				Stacks[i]->goToEnd();
				Stacks[i]->previous();
				if (Stacks[i]->getElement().adjacentTo(descarteTope)) return false;
			}
			return true;
		}

		for (int i = 0; i < 7; i++) {
			if (Stacks[i]->isEmpty()) continue;
			return false;
		}

		return true;
	}

	int calcularPuntaje() {
		int puntaje = 0;
		for (int i = 0; i < 7; i++) {
			puntaje += Stacks[i]->getSize();
		}
		return puntaje - Hand->getSize();
	}

	void imprimirStacks() {
		for (int row = 0; row < 5; row++){
			for (int col = 0; col < 7; col++) {
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

	void imprimirNumeroColumnas() {
		for (int i = 0; i < 7; i++) {
			cout << "  " << i + 1 << "   ";
		}
		cout << endl;
		for (int i = 0; i < 7; i++) {
			cout << "  ↓   ";
		}
		cout << endl;
	}

	void imprimirMovimientos() {
		cout << "Movimientos: " << GolfState::getMovimientos() << endl;
	}

	void imprimirMano() {
		if (Hand->isEmpty()) {
			cout << "Mano: " << "(Vacia) " << endl;
			return;
		}
		cout << "Mano: " << Hand->topValue() << "x" << Hand->getSize() << endl;
	}

	void imprimirDescartes() {
		if (Discards->isEmpty()) {
			cout << "Descartes: " << "(Vacia)" << endl;
			return;
		}
		cout << "Descartes: " << Discards->topValue() << endl;
	}

	void imprimirDescartesExtendido() {
		if (Discards->isEmpty()) {
			cout << "Descartes: " << "(Vacia)" << endl;
			return;
		}
		
		cout << "Descartes: ";
		Discards->print();
	}

	~GolfGame() {
		for (int i = 0; i < 7; i++) {
			delete Stacks[i];
		}
		delete Hand;
		delete Discards;
		delete GameStates;
	}

	void voltearCarta(bool start=false){
		if (Hand->isEmpty()) return;
		if (!start) nuevoMovimiento();

		Card card = Hand->pop();
		card.FaceUp = true;
		Discards->push(card);
	}

	bool descartarCarta(int stackIndex, bool bypass=false){
		if (stackIndex < 0 || stackIndex > 7) {
			cout << "Columna invalida" << endl;
			return 0;
		}
		if (Stacks[stackIndex]->isEmpty()) {
			cout << "Descarte invalido" << endl;
			return 0;
		}
		Stacks[stackIndex]->goToEnd();
		Stacks[stackIndex]->previous();
		Card carta = Stacks[stackIndex]->getElement();
		Card topeDescarte = Discards->topValue();
		if (!carta.adjacentTo(topeDescarte) && !bypass) {
			cout << "Movimiento invalido" << endl;
			return 0;
		}
		nuevoMovimiento();
		carta.FaceUp = true;
		Stacks[stackIndex]->remove();
		Discards->push(carta);
		return true;
	}

	void print() {
		cout << endl;
		imprimirMovimientos();
		imprimirNumeroColumnas();
		imprimirStacks();

		imprimirDescartes();
		imprimirMano();
		cout << endl;
	}
};