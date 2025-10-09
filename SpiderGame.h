#pragma once
#include "Stack.h"
#include "Card.h"
#include "Deck.h"
#include "GolfState.h"
#include "LinkedStack.h"
class SpiderGame
{
private:
	Deck spiderDeck;
	Stack<GolfState>* GameStates;
	List<Card>* Stacks[10];
	Stack<Card>* cardReserve;
	Stack<Card>* cardLadderComplete;

	void deshacerMovimiento() {}

	void nuevoMovimiento() {
		GameStates->push(GolfState(Stacks, cardReserve, cardLadderComplete));
	}

	void repartirNaipe(Deck currentDeck) {
		currentDeck.shuffle();

		for (int col = 0; col < 4; col++) {
			for (int row = 0; row < 6; row++) {
				Card card = currentDeck.drawCard();
				card.FaceUp = false;
				if (row == 5)
					card.FaceUp = true;
				Stacks[col]->append(card);
			}
		}
		for (int col = 0; col < 4; col++) {
			for (int row = 0; row < 5; row++) {
				Card card = currentDeck.drawCard();
				card.FaceUp = false;
				if (row == 4)
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

public:
	SpiderGame() {
		cardReserve = new LinkedStack<Card>();
		for (int stackIndex = 0; stackIndex < 10; stackIndex++) {
			Stacks[stackIndex] = new LinkedList<Card>();
		}
		cardLadderComplete = new LinkedStack<Card>();
		GameStates = new LinkedStack<GolfState>();
	}

	void inicializarJuego() {
		spiderDeck = Deck(2);
		repartirNaipe(spiderDeck);
	}


	void imprimirStacks() {
		for (int row = 0; row < 6; row++) {
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
		cout << "Card Reserve: " << cardLadderComplete->topValue() << "x" << cardReserve->getSize() << endl;
	}

	void imprimirCardLadderComplete() {
		cout << "Card Ladder Complete: " << cardLadderComplete->topValue() << endl;
	}

	~SpiderGame() {
		delete[] Stacks;
		delete cardReserve;
		delete cardLadderComplete;
		delete GameStates;
	}

};

