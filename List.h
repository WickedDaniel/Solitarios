#pragma once

/*
 *	LinkedList.h - Clase que define la interfaz de una lista
 *	Colaboradores:
 *	- Mauricio Aviles - ??? Creacion de la clase
 *  - Alejandro Villalobos Ramírez - 10/8/2025 Creación del constructor de copia
 *	Descripcion:
 *	- Interfaz pura que define las operaciones basicas de una lista
 */

template <typename E>
class List {
public:
	List() {}
	List(const List<E>& other) {};
	void operator=(const List<E>& other) = delete;
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual void setElement(E element) = 0;
	virtual E getElement() = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atStart() = 0;
	virtual bool atEnd() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};



