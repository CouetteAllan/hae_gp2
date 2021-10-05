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
	Leaf(int d, Leaf* r, Leaf* l, Leaf* p) {
		data = d;
		rightChild = r;
		leftChild = l;
		parent = p;
	}

	Leaf(int d, Leaf* p) {
		data = d;
		parent = p;
	}

};

class MyBinaryTree {

};