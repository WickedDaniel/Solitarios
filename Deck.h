#pragma once
#include "Card.h";
#include "LinkedList.h";


class Deck
{
private:
	List<Card>* Cards = new LinkedList<Card>();
public:
	Deck() {

	}
	void generateDeck() {
		for (Card::SUIT suit : {Card::HEARTS, Card::DIAMONDS, Card::CLUBS, Card::SPADES}) {
			for (int rank = Card::ACE; rank <= Card::K; rank++) {
				Card NewCard = Card((Card::RANK)rank, suit, false); // Creating new card on heap
				Cards->append(NewCard);
			}
		}
	};
	void shuffle() {

	};

};

