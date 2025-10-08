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

        // Convert to array
        Card* tempArray = new Card[size];

        Cards->goToStart();
        for (int i = 0; i < size; i++) {
            tempArray[i] = Cards->getElement();
            Cards->next();
        }

        // Fisher-Yates shuffle
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            // Swap
            Card temp = tempArray[i];
            tempArray[i] = tempArray[j];
            tempArray[j] = temp;
        }

        // Put back
        Cards->clear();
        for (int i = 0; i < size; i++) {
            Cards->append(tempArray[i]);
        }

        delete[] tempArray;
	};

	void print() {
		Cards->print();
	}
};

