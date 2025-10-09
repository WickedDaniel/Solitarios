#pragma once
#include "Stack.h"
#include "Card.h"
#include "LinkedStack.h"
#include "LinkedList.h"

class GolfState
{
public:
	int movimientos = 0;
	LinkedList<Card>* Stacks[7];
	LinkedStack<Card>* Hand;
	LinkedStack<Card>* Discards;

	~GolfState() {
		delete Hand;
		delete Discards;
		for (int i = 0; i < 7; i++) {
			delete Stacks[i];
		}
	}

	GolfState() {
		Hand = new LinkedStack<Card>();
		Discards = new LinkedStack<Card>();
		for (int i = 0; i < 7; i++) {
			Stacks[i] = new LinkedList<Card>();
		}
	}
	GolfState(LinkedList<Card>* stacks[7], LinkedStack<Card>* hand, LinkedStack<Card>* discards) {
		Hand = new LinkedStack<Card>(*hand);
		Discards = new LinkedStack<Card>(*discards);
		for (int i = 0; i < 10; i++) {
			Stacks[i] = new LinkedList<Card>(*Stacks[i]);
		}
	}

	friend ostream& operator<<(ostream& os, const GolfState& golf) {
		os << "This is a gamestate :Troll:";
		return os;
	}
};

