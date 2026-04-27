#pragma once
#include <cstddef>
#include "StackImplementation.h"

class List : public IStackImplementation {
	private:
		struct Node {
			ValueType data;
			Node* next;
			Node* prev;
			Node(const ValueType& val) 
				: data(val), next(nullptr), prev(nullptr) {}
		};
		
		Node* _head = nullptr;
		Node* _tail = nullptr;
		size_t _size = 0;
	
	public:
		List();
		~List();
		List(const List& other);
		List& operator=(const List& other);

		void push(const ValueType& value) override;
		void pop() override;
		const ValueType& top() const override;
		bool isEmpty() const override;
		size_t size() const override;
};
