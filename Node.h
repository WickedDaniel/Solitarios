#pragma once

/*
 *	Node.h - Clase que define un nodo para listas enlazadas
 *	Colaboradores:
 *	- Mauricio Aviles - ??? Creacion de la clase
 *	Descripcion:
 *  - Define un nodo para listas enlazadas
 */

template <typename E>
class Node {
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};

