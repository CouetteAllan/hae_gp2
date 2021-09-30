#pragma once
class Node {
	friend class MyLinkedList;

private:
	int data;
	Node* next;


	Node(int d) {
		data = d;
		next = nullptr;
	}
	Node(int d, Node* n) {
		data = d;
		next = n;
	}

};


class MyLinkedList {
private:
	Node* head;
	Node* last;
	int numberOfNode;

public:

	MyLinkedList() {
		head = nullptr;
		last = nullptr;
		numberOfNode = 0;
	}


	void AddBeginning(int value) {
		Node* newNode = new Node(value);

		newNode->next = head;
		head = newNode;
		if (numberOfNode == 0)//si c'est le seul node de la liste
			last = newNode;// il est à la fois le premier et le dernier
		numberOfNode++;

	}

	void AddLast(int value) {
		Node* newNode = new Node(value);

		last->next = newNode;
		last = newNode;
		if (numberOfNode == 0)
			head = newNode;
		numberOfNode++;
	}



};