#include "Card.h"

int main() {
	// Test adjacentTo
	Card ACE = Card(Card::ACE, true);
	Card K = Card(Card::K, true);

	cout << ACE.adjacentTo(K) << endl;
	// Test Print
	cout << ACE.toString() << endl;
	cout << K.toString() << endl;

	ACE = Card(Card::K, Card::DIAMONDS, false);
	K = Card(Card::K, Card::CLUBS, true);

	// Test Print with face down and suit
	cout << ACE.toString() << endl;
	cout << K.toString() << endl;
}