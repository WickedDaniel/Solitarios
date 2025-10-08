#pragma once
#include "Stack.h"
#include "Card.h"
#include "Deck.h"
#include "GolfState.h"
#include "LinkedStack.h"
class GolfGame
{
private:
	Deck golfDeck;
	Stack<GolfState>* GameStates;
	List<Card>* Stacks[7];
	Stack<Card>* Hand;
	Stack<Card>* Discards;
	
	void deshacerMovimiento() {
		if (GameStates->isEmpty()) {
			cout << "No hay movimientos para deshacer" << endl;
			return;
		}
		GolfState estadoAnterior = GameStates->pop();
		Discards = estadoAnterior.Discards;
		Hand = estadoAnterior.Hand;
		for (int i = 0; i < 7; i++) {
			Stacks[i] = estadoAnterior.Stacks[i];
		}
	};
	void nuevoMovimiento() {
		GameStates->push(GolfState(Stacks, Hand, Discards));
	};

	void repartirNaipe(Deck currentDeck) {
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

		voltearCarta();
	}

public:
	GolfGame() {
		Hand = new LinkedStack<Card>();
		for (int stackIndex = 0; stackIndex < 7; stackIndex++) {
			Stacks[stackIndex] = new LinkedList<Card>();
		}
		Discards = new LinkedStack<Card>();
		GameStates = new LinkedStack<GolfState>();
	}

	void inicializarJuego() {
		golfDeck = Deck();
		repartirNaipe(golfDeck);
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

	void imprimirMano() {
		if (Hand->isEmpty()) {
			cout << "Mano: " << "(Vacia) " << endl;
			return;
		}
		cout << "Mano: " << Hand->topValue() << "x" << Hand->getSize() << endl;
	}

	void imprimirDescartes() {
		cout << "Descartes: " << Discards->topValue() << endl;
	}

	void imprimirDescartesExtendido() {
		cout << "Descartes: " << Discards->topValue() << endl;
	}

	~GolfGame() {
		delete[] Stacks;
		delete Hand;
		delete Discards;
		delete GameStates;
	}

	void voltearCarta(){
		if (Hand->isEmpty())
			return;
		Card card = Hand->pop();
		card.FaceUp = true;
		Discards->push(card);
		nuevoMovimiento();
	}

	void descartarCarta(int stackIndex){
		Stacks[stackIndex]->goToEnd();
		Stacks[stackIndex]->previous();
		Card carta = Stacks[stackIndex]->getElement();
		Card topeDescarte = Discards->topValue();
		if (!carta.adjacentTo(topeDescarte)) {
			cout << "Movimiento invalido" << endl;
			return;
		}

		carta.FaceUp = true;
		Stacks[stackIndex]->remove();
		Discards->push(carta);
		nuevoMovimiento();
	}
};