#pragma once
#include <math.h>

class Card
{
public:
	enum RANK {
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K
	};
	enum FAMILY {
		DIAMONDS, CLUBS, HEARTS, SPADES
	};
	bool adjacentTo(Card &anotherCard) {
		int Difference = abs(this->Rango - anotherCard.Rango);
		if (Difference == 1 || Difference == 12) {
			return true;
		}
	}

private:
	RANK Rango;
	FAMILY Familia;
	bool FaceUp = false;
	Card(RANK r, FAMILY f) {
		Rango = r;
		Familia = f;
	};
	
	~Card() {
	
	};

};

