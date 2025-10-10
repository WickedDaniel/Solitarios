#pragma once

/*
 *	Stack.h - Clase que define la interfaz de una pila
 *	Colaboradores:
 *	- Mauricio Aviles - ??? Creacion de la clase
 *  - David Alonso Vega Hidalgo - 10/8/2025 Creación del constructor de copia
 *	Descripcion:
 *	- Interfaz pura que define las operaciones basicas de una pila
 */

template <typename E>
class Stack {
public:
	Stack() {}
	Stack(const Stack<E>& other) {}
	void operator= (const Stack<E>& other) = delete;
	virtual ~Stack() {}
	virtual void push(E element) = 0;
	virtual E pop() = 0;
	virtual E topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};

