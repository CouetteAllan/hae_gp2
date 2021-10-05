#pragma once
class Leaf {
	friend class MyBinaryTree;

private:
	int data;
	Leaf* parent;
	Leaf* rightChild;
	Leaf* leftChild;


	Leaf(int d) {
		data = d;
		parent = nullptr;
		rightChild = nullptr;
		leftChild = nullptr;
	}
	Leaf(int d, Leaf* n) {
		data = d;
	}

};

class MyBinaryTree {

};