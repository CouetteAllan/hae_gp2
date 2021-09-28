#pragma once





class MyLinkedList {

public:

	struct Node {
		int* data;
		struct Node* next;

		Node(int* value, Node* next = NULL) {
			data = value;
			this->next = next;
		}
	};

	Node *head, *tail;

	MyLinkedList(int* firstData) {
		head->data = firstData;
	}


	void AddAfter(Node* prevNode, int* newData) {
		Node* newNode = new Node(newData);
		prevNode->next = newNode;

	}

};