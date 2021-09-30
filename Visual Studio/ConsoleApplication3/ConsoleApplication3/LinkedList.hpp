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
	Node* current = nullptr;
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

	void AddInPosition(int value, int index) {
		Node* newNode = new Node(value);
		current = head;

		if (index <= 0) {
			AddBeginning(value);
			return;
		}

		if (index >= numberOfNode) {
			AddLast(value);
			return;
		}

		for (size_t i = 0; i < index-1; i++)
		{
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
		numberOfNode++;

	}

	void RemoveFirst() {

		if (numberOfNode > 0) {
			Node* temp = head;
			head = head->next;
			delete temp;

			numberOfNode--;
			if (numberOfNode == 0)
				last = NULL;
		}

	}

	void RemoveLast() {
		if (numberOfNode > 0) {

			current = head;
			for (size_t i = 0; i < numberOfNode-2; i++)
			{
				current = current->next;
			}
			last = current;
			delete last->next;
			last->next = NULL;
			numberOfNode--; 
		}


	}

	
	void PrintLinkedList() {
		//print la data jusqu'à trouver un pointeur null qui signifie la fin ou alors jusqu'au node "last"
		current = head;
		if (current == NULL)
			return;

		printf("Printing: \n");

		while (current != NULL) {
			printf("%i\n", current->data);
			current = current->next;
		}
		printf("Number of nodes: %i\n", numberOfNode);

	}

};