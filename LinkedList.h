#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedList : public List<E> {
private:
	Node<E>* head;
	Node<E>* current;
	Node<E>* tail;
	int size;

public:
	LinkedList() {
		head = current = tail = new Node<E>();
		size = 0;
	}

	LinkedList(const LinkedList<E>& other) {
		head = current = tail = new Node<E>();
		size = 0;

		if (other.size == 0) throw runtime_error("Constructor con lista vacia");

		Node<E>* temp = other.head->next;
		while (temp != nullptr) {
			this->append(E(temp->element));
			temp = temp->next;
		}
	}
	~LinkedList() {
		clear();
		delete head;
	}
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = current->next;
		size++;
	}
	void append(E element) {
		tail = tail->next = new Node<E>(element);
		size++;
	}
	void append(const LinkedList<E>* other) {
		if (other->size == 0) return;
		Node<E>* temp = other->head->next;
		while (temp != nullptr) {
			this->append(E(temp->element));
			temp = temp->next;
		}
	}

	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");

		E result = current->next->element;
		Node<E>* temp = current->next;

		// Check if we're removing the tail BEFORE changing pointers
		if (temp == tail)
			tail = current;

		current->next = temp->next;
		delete temp;
		size--;
		return result;
	}
	void clear() {
		while (head->next != nullptr) {
			current = head->next;
			head->next = current->next;
			delete current;
		}
		current = tail = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Invalid position.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current)
				temp = temp->next;
			current = temp;
		}
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail;
	}
	int getPos() {
		int pos = 0;
		Node<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}

	bool isEmpty(){
		return getSize() == 0;
	}

	LinkedList<E>* slice(int start, int end) {
		if (start < 0 || end > size || start > end) throw runtime_error("Invalid slice indices.");
		if (end - start == 0) return new LinkedList<E>();
		LinkedList<E>* newList = new LinkedList<E>();
		Node<E>* temp = head->next;
		for (int i = 0; i < start; i++) {
			temp = temp->next;
		}
		for (int i = start; i < end; i++) {
			newList->append(E(temp->element));
			temp = temp->next;
		}

		return newList;
	}

	LinkedList<E>* cutTail(int cutSize) {
		if (cutSize < 0 || cutSize > size) throw runtime_error("Invalid cut size.");
		if (cutSize == 0) return new LinkedList<E>();
		LinkedList<E>* newList = new LinkedList<E>();
		int start = size - cutSize;
		this->goToEnd();
		for (int i = 0; i < cutSize; i++) {
			this->previous();
			newList->insert(this->remove());
		}
		return newList;
	}

	void print() {
		Node<E>* temp = head->next;
		cout << "[ ";
		while (temp != nullptr) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};

