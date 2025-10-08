#include "Card.h"

int main() {
	Card newCard = Card(Card::ACE, Card::HEARTS, true);
	cout << newCard.toString() << endl;
}