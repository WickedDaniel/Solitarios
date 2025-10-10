#pragma once
#include "Stack.h"
#include "Card.h"
#include "LinkedStack.h"
#include "LinkedList.h"


class SpiderState
{
private:
	static int movimientos;
public:
	LinkedList<Card>* Stacks[10];
	LinkedStack<Card>* listCardReserve;
	LinkedStack<LinkedList<Card>*>* listCompleteLeader;

	~SpiderState() {
		delete listCardReserve;
		delete listCompleteLeader;
		for (int i = 0; i < 10; i++) {
			delete Stacks[i];
		}
	}

	SpiderState() {
		listCardReserve = new LinkedStack<Card>();
		listCompleteLeader = new LinkedStack<LinkedList<Card>*>();
		for (int i = 0; i < 10; i++) {
			Stacks[i] = new LinkedList<Card>();
		}
	}
	SpiderState(LinkedList<Card>* stacks[10], LinkedStack<Card>* cardReserve, LinkedStack<LinkedList<Card>*>* completeLadder) {
		movimientos++;
		listCardReserve = new LinkedStack<Card>(*cardReserve);
		listCompleteLeader = new LinkedStack<LinkedList<Card>*>(*completeLadder);
		for (int i = 0; i < 10; i++) {
			if (stacks[i]->isEmpty()) {
				Stacks[i] = new LinkedList<Card>();
				continue;
			}
			Stacks[i] = new LinkedList<Card>(*stacks[i]);
		}
	}

	static int getMovimientos() {
		return movimientos;
	}

	static int reiniciarMovimientos() {
		movimientos = 0;
		return movimientos;
	}

	friend ostream& operator<<(ostream& os, const SpiderState& spider) {
		os << "This is a gamestate :Troll:";
		return os;
	}
};

int SpiderState::movimientos = 0;