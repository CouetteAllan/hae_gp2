#include "LinkedList.hpp"

void MyLinkedList::AddFirst(int value)
{
	Node* newNode = new Node(value);

	newNode->next = head;
	head = newNode;
	if (numberOfNode == 0)//si c'est le seul node de la liste
		last = newNode;// il est à la fois le premier et le dernier
	numberOfNode++;

}

void MyLinkedList::AddLast(int value)
{
	Node* newNode = new Node(value);

	last->next = newNode;
	last = newNode;
	if (numberOfNode == 0)
		head = newNode;
	numberOfNode++;
}

void MyLinkedList::AddInPosition(int value, int index)
{
	Node* newNode = new Node(value);
	current = head;

	if (index <= 0) {
		AddFirst(value);
		return;
	}

	if (index >= numberOfNode) {
		AddLast(value);
		return;
	}

	for (size_t i = 0; i < index - 1; i++)
	{
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
	numberOfNode++;

}

void MyLinkedList::RemoveFirst()
{

	if (numberOfNode > 0) {
		Node* temp = head;
		head = head->next;
		delete temp;

		numberOfNode--;
		if (numberOfNode == 0)
			last = NULL;
	}

}

void MyLinkedList::RemoveLast()
{
	if (numberOfNode > 0) {

		current = head;
		for (size_t i = 0; i < numberOfNode - 2; i++)
		{
			current = current->next;
		}
		last = current;
		delete last->next;
		last->next = NULL;
		numberOfNode--;
	}


}

void MyLinkedList::RemoveAll()
{
	while (numberOfNode > 0) {
		RemoveFirst();
	}
}

void MyLinkedList::PrintLinkedList()
{
	//print la data jusqu'à trouver un pointeur null qui signifie la fin ou alors jusqu'au node "last"
	current = head;
	if (current == NULL) {
		printf("Nothing to Print");
		return;
	}


	printf("Printing: \n");

	while (current != NULL) {
		printf("%i\n", current->data);
		current = current->next;
	}
	printf("Number of nodes: %i\n", numberOfNode);

}


