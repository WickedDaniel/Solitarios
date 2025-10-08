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
		int OriginalSize = Cards->getSize();
		for (int Index = 0; Index < OriginalSize; Index++) {
			Cards->goToStart();
			Card removedCard = Cards->remove();

			int randomPos = rand() % (Cards->getSize() + 1);
			Cards->goToPos(randomPos);
			Cards->insert(removedCard);
		}
	};

	void print() {
		Cards->print();
	}
};

