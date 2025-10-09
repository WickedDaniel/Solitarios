    #pragma once
#include "Card.h"
#include "LinkedList.h"


class Deck
{
private:
    // Se utiliza LinkedList para realizar un mejor shuffle
	// debido a que se puede acceder a cualquier posicion
	LinkedList<Card>* Cards = new LinkedList<Card>();
public:
	Deck(int decks=1) {
        Cards->clear();
		for (int i = 0; i < decks; i++)
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

    int getSize() {
		return Cards->getSize();
    }

	Card drawCard() {
        if (Cards->getSize() == 0)
            throw std::runtime_error("No cards left in the deck.");
        Cards->goToStart();
        Card drawnCard = Cards->getElement();
        Cards->remove();
        return drawnCard;
	};

	void shuffle() {
		// Fisher-Yates shuffle algorithm
        int size = Cards->getSize();
        if (size <= 1) return;

        Card* tempArray = new Card[size];
        Cards->goToStart();
        for (int i = 0; i < size; i++) {
            tempArray[i] = Cards->getElement();
            Cards->next();
        }

        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Card temp = tempArray[i];
            tempArray[i] = tempArray[j];
            tempArray[j] = temp;
        }
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

