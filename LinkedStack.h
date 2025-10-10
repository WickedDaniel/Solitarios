#pragma once

#include <stdexcept>
#include <iostream>
#include "Node.h"
#include "Stack.h"

/*
 *	LinkedStack.h - Clase que implementa una lista enlazada
 *	Colaboradores:
 *	- Mauricio Aviles - ??? Creacion de la clase
 *  - David Alonso Vega Hidalgo - 10/8/2025 Creación de constructor de copia
 *	- Daniel Caleb Vargas Mora - 10/8/2025 Correccion de constructores de copia
 *	Descripcion:
 *	- Extiende la clase List para implementar una lista enlazada con nodos.
 */

using std::runtime_error;
using std::cout;
using std::endl;


template <typename E>
class LinkedStack : public Stack<E> {
private:
	Node<E>* top;
	int size;

public:
	LinkedStack() {
		top = nullptr;
		size = 0;
	}

	LinkedStack(const LinkedStack<E>& other) {
		top = nullptr;
		size = 0;

		if (other.top == nullptr) return;
		LinkedStack<E> tempStack;


		Node<E>* temp = other.top;
		while (temp != nullptr) {
			tempStack.push(E(temp->element));
			temp = temp->next;
		}
		while (!tempStack.isEmpty()) {
			push(tempStack.pop());
		}
	}

	~LinkedStack() {
		clear();
	}
	void push(E element) {
		top = new Node<E>(element, top);
		size++;
	}
	E pop() {
		if (size == 0)
			throw runtime_error("Stack underflow.");
		E result = top->element;
		Node<E>* temp = top;
		top = top->next;
		delete temp;
		size--;
		return result;
	}
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack underflow.");
		return top->element;
	}
	void clear() {
		while (top != nullptr) {
			Node<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[ ";
		Node<E>* temp = top;
		while (temp != nullptr) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}

};

