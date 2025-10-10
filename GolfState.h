#pragma once
#include "Stack.h"
#include "Card.h"
#include "LinkedStack.h"
#include "LinkedList.h"

/*
 *	GolfState.h - Clase que controla el registro del juego GolfGame
 *	Colaboradores:
 *	- Daniel Caleb Vargas Mora - 10/7/2025 Creacion de la clase
 *	- Daniel Caleb Vargas Mora - 10/8/2025 Correccion de constructores de copia
 *	- Daniel Caleb Vargas Mora - 10/9/2025 Agregacion de contador de movimientos y solucion de stack underflow
 *  - David Alonso Vega Hidalgo - 10/8/2025 Creación de constructores de copia
 *	Descripcion:
 *	- Funciona como un snapshot del estado actual del juego GolfGame
 */

class GolfState
{
private:
	static int movimientos;
public:
	LinkedList<Card>* Stacks[7];
	LinkedStack<Card>* Hand;
	LinkedStack<Card>* Discards;

	~GolfState() {
		delete Hand;
		delete Discards;
		for (int i = 0; i < 7; i++) {
			delete Stacks[i];
		}
	}

	GolfState() {
		Hand = new LinkedStack<Card>();
		Discards = new LinkedStack<Card>();
		for (int i = 0; i < 7; i++) {
			Stacks[i] = new LinkedList<Card>();
		}
	}
	GolfState(LinkedList<Card>* stacks[7], LinkedStack<Card>* hand, LinkedStack<Card>* discards) {
		Hand = new LinkedStack<Card>(*hand);
		Discards = new LinkedStack<Card>(*discards);
		for (int i = 0; i < 7; i++) {
			if (stacks[i]->isEmpty()) {
				Stacks[i] = new LinkedList<Card>();
				continue;
			}
			Stacks[i] = new LinkedList<Card>(*stacks[i]);
		}
		movimientos++;
	}

	static int getMovimientos() {
		return movimientos;
	}

	static int reiniciarMovimientos() {
		movimientos = 0;
		return movimientos;
	}

	friend ostream& operator<<(ostream& os, const GolfState& golf) {
		os << "This is a gamestate :Troll:";
		return os;
	}
};

int GolfState::movimientos = 0;