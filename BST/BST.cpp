#include "BST.h"
#include <iostream>

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left, Node *right)
	: keyValuePair(key, value), parent(parent),left(left), right(right) {}

BinarySearchTree::Node::Node(const Node &other)
	: keyValuePair(other.keyValuePair), parent(nullptr), left(nullptr), right(nullptr) {}

bool BinarySearchTree::Node::operator==(const Node &other) const
{
	return keyValuePair.first == other.keyValuePair.first;
}
