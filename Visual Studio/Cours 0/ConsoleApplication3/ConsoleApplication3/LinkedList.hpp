#pragma once
#include <cstddef>
#include <stdio.h>
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
	Node* current = nullptr;
	int numberOfNode;

public:

	MyLinkedList() {
		head = nullptr;
		last = nullptr;
		numberOfNode = 0;
	}


	void AddFirst(int value);

	void AddLast(int value);

	void AddInPosition(int value, int index);

	void RemoveFirst();

	void RemoveLast();

	void RemoveAll();

	void PrintLinkedList();

};