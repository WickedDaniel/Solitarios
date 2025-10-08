#pragma once
#include "Card.h";
#include "LinkedList.h";


class Deck
{
private:
	List<Card>* Cards = new LinkedList<Card>();
public:
	Deck() {
		generateDeck();
	}
	void generateDeck() {
		for (Card::SUIT suit : {Card::HEARTS, Card::DIAMONDS, Card::CLUBS, Card::SPADES}) {
			for (int rank = Card::ACE; rank <= Card::K; rank++) {
				Card NewCard = Card((Card::RANK)rank, suit, true); // Creating new card on heap
				Cards->append(NewCard);
			}
		}
	};

	void shuffle() {
		int size = Cards->getSize();
		if (size <= 1) return;

		for (int i = size - 1; i > 0; i--) {
			int j = rand() % (i + 1);

			// Swap elements at position i and j
			Cards->goToPos(i);
			Card cardI = Cards->getElement();

			Cards->goToPos(j);
			Card cardJ = Cards->getElement();

			Cards->goToPos(i);
			Cards->setElement(cardJ);

			Cards->goToPos(j);
			Cards->setElement(cardI);
		}
	};

	void print() {
		Cards->print();
	}
};

