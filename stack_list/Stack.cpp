#include "Stack.h"
#include "list.h"
#include "vector.h"
#include <iostream>
#include <stdexcept>

Stack::Stack(StackContainer container) 
	: _containerType(container) {
		if (container == StackContainer::Vector) {
			_pimpl = new Vector();
		}
		else if (container == StackContainer::List) {
			_pimpl = new List();
		}
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container) 
	: _containerType(container) {
		if (container == StackContainer::Vector) {
			_pimpl = new Vector();
		}
		else if (container == StackContainer::List) {
			_pimpl = new List();
		}
		
		for (size_t i = 0; i < arraySize; i++) {
			push(valueArray[i]);
		}
}

Stack::Stack(const Stack& copyStack) : _containerType(copyStack._containerType) {
	switch (_containerType) {
		case StackContainer::Vector:
			_pimpl = new Vector(*dynamic_cast<Vector*>(copyStack._pimpl));
			break;
		case StackContainer::List:
			_pimpl = new List(*dynamic_cast<List*>(copyStack._pimpl));
			break;
		default:
			break;
	}
}

Stack& Stack::operator=(const Stack& copyStack) {
	if (this != &copyStack)
	{
		Stack temp(copyStack);
		std::swap(_pimpl, temp._pimpl);
		std::swap(_containerType, temp._containerType);
	}
	return *this;
}

Stack::Stack(Stack&& moveStack) noexcept : _pimpl(moveStack._pimpl), _containerType(moveStack._containerType){
	moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
	if (this != &moveStack) {
		delete _pimpl;
		_pimpl = moveStack._pimpl;
		_containerType = moveStack._containerType;
		moveStack._pimpl = nullptr;
	}
	return *this;
}

Stack::~Stack() {
	delete _pimpl;
}

void Stack::push(const ValueType& value) {
	if (_pimpl) {
		_pimpl->push(value);
	}
}

void Stack::pop() {
	if (_pimpl) {
		_pimpl->pop();
	}
}

const ValueType& Stack::top() const {
	if (!_pimpl) {
		throw std::runtime_error("Stack not initialized");
	}
	return _pimpl->top();
}

bool Stack::isEmpty() const {
	return _pimpl ? _pimpl->isEmpty() : true;
}

size_t Stack::size() const {
	return _pimpl ? _pimpl->size() : 0;
}
