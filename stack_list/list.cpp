#include "list.h"
#include <iostream>

List::List() : _head(nullptr), _tail(nullptr), _size(0) {}

List::~List() {
	while (!isEmpty()) {
		pop();
	}
}

List::List(const List& other) : _head(nullptr), _tail(nullptr), _size(0) {
	Node* current = other._head;
	while (current) {
		push(current->data);
		current = current->next;
	}
}

List& List::operator=(const List& other) {
	if (this != &other) {
		while (!isEmpty()) {
			pop();
		}
		
		Node* current = other._head;
		while (current) {
			push(current->data);
			current = current->next;
		}
	}
	return *this;
}

void List::push(const ValueType& value) {
	Node* newNode = new Node(value);
	
	if (isEmpty()) {
		_head = newNode;
		_tail = newNode;
	}
	else {
		newNode->prev = _tail;
		_tail->next = newNode;
		_tail = newNode;
	}
	_size++;
}

void List::pop() {
	if (isEmpty()) {
		return;
	}
	
	Node* temp = _tail;
	if (_head == _tail) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		_tail = _tail->prev;
		_tail->next = nullptr;
	}
	
	delete temp;
	_size--;
}

const ValueType& List::top() const {
	return _tail->data;
}

bool List::isEmpty() const {
	return _size == 0;
}

size_t List::size() const {
	return _size;
}
