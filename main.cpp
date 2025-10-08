#include "Card.h"
#include "Deck.h"

int main() {
	srand(time(0));
	// Test Deck
	Deck deck = Deck();
	deck.print();

	// Test Shuffle
	deck.shuffle();
	deck.print();
}