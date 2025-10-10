#pragma once

#include "Card.h"
#include "LinkedList.h"

/*
 *  Deck.h - Clase mazo que representa un mazo de Cartas
 *  Colaboradores:
 *  - Daniel Caleb Vargas Mora - 10/7/2025 Creacion
 *  - Daniel Caleb Vargas Mora - 10/8/2025 Adaptacion para multiples barajas
 *  - Alejandro Villalobos Ramírez - 10/9/2025 Corrección para evitar limpiar las cartas
 *  Descripcion:
 *  - Representa el naipe de cartas en el juego, contiene funciones
 *  para generar, barajar y sacar cartas del naipe dejandolo vacio.
 *  - Se puede crear un mazo con multiples barajas indicandolo en el 
 *  constructor.
 */

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
    Deck(int decks, Card::SUIT suitToUse) {
        Cards->clear();
        for (int i = 0; i < decks; i++)
			generateDeck(suitToUse);
	}
	void generateDeck() {
		for (Card::SUIT suit : {Card::HEARTS, Card::DIAMONDS, Card::CLUBS, Card::SPADES}) {
			for (int rank = Card::ACE; rank <= Card::K; rank++) {
				Card NewCard = Card((Card::RANK)rank, suit, true); // Creating new card on heap
				Cards->append(NewCard);
			}
		}
	};
    void generateDeck(Card::SUIT suitToUse) {
        for (Card::SUIT suit : {Card::HEARTS, Card::DIAMONDS, Card::CLUBS, Card::SPADES}) {
            for (int rank = Card::ACE; rank <= Card::K; rank++) {
                Card NewCard = Card((Card::RANK)rank, suitToUse, true);
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
        // https://www.geeksforgeeks.org/dsa/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
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

