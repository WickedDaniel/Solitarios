#pragma once
#include "Stack.h"
#include "Card.h"
#include "LinkedStack.h"
#include "LinkedList.h"

class SpiderState
{
public:
	int movimientos = 0;
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
		listCardReserve = new LinkedStack<Card>(*cardReserve);
		listCompleteLeader = new LinkedStack<LinkedList<Card>*>(*completeLadder);
		for (int i = 0; i < 10; i++) {
			Stacks[i] = new LinkedList<Card>(*stacks[i]);
		}
	}

	friend ostream& operator<<(ostream& os, const SpiderState& spider) {
		os << "This is a gamestate :Troll:";
		return os;
	}
};