#pragma once
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
class Card
{
public:
	enum RANK {
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K
	};

	enum SUIT {
		HEARTS, DIAMONDS, CLUBS, SPADES
	};

	SUIT Suit;
	RANK Rank;
	bool FaceUp = false;

	Card() {
		Rank = ACE;
		Suit = SPADES;
		FaceUp = true;
	}

	Card(RANK rank, bool faceUp) {
		Rank = rank;
		Suit = SPADES;
		FaceUp = faceUp;
	};

	Card(RANK rank, SUIT suit, bool faceUp) {
		Suit = suit;
		Rank = rank;
		FaceUp = faceUp;
	};

	bool adjacentTo(Card &anotherCard) {
		int Difference = abs(this->Rank - anotherCard.Rank);
		if (Difference == 1 || Difference == 12) {
			return true;
		}
		return false;
	}

	
	bool isDescending(Card& anotherCard) {
		int Difference = this->Rank - anotherCard.Rank;
		return Difference == -1;
	}

	const string toString() {
		string SuitSymbols[]  = {"", "♥", "♦", "♣", "♠"};
		string RankSymbols[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

		if (!FaceUp) return "|#|";
		return "|"+RankSymbols[Rank] + SuitSymbols[Suit] + "|";
	}

	friend ostream& operator<<(ostream& os, const Card& card) {
		string SuitSymbols[] = { "♥", "♦", "♣", "♠" };
		string RankSymbols[] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
		if (!card.FaceUp) os << "| # |";
		if (card.FaceUp && card.Rank == Card::TEN) os << "|" << RankSymbols[card.Rank] << SuitSymbols[card.Suit] << "|";
		if (card.FaceUp && card.Rank != Card::TEN) os << "| " << RankSymbols[card.Rank] << SuitSymbols[card.Suit] << "|";
		return os;
	}
};


