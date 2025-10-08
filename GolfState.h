#pragma once
#include "Stack.h"
#include "Card.h"

class GolfState
{
public:
	List<Card>* Stacks[7];
	Stack<Card>* Hand;
	Stack<Card>* Discards;

	~GolfState() {
		delete Hand;
		delete Discards;
		for (int i = 0; i < 7; i++) {
			delete Stacks[i];
		}
	}
	GolfState() {
	}
	GolfState(List<Card>* stacks[7], Stack<Card>* hand, Stack<Card>* discards) {

	}

	friend ostream& operator<<(ostream& os, const GolfState& golf) {
		os << "This is a gamestate :Troll:";
		return os;
	}
};

