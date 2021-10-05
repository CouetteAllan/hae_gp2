// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Toto.h"
#include "IntArray.hpp"
#include "LinkedList.hpp"


int Strlen(const char* maChaine) {
	int idx = 0;
	while (maChaine[idx] != 0) {
		idx++;
	}

	return idx;

}

int Countc(const char* maChaine, char c) {
	int size = Strlen(maChaine);
	int res = 0;


	for (size_t i = 0; i < size; i++)
	{
		if (maChaine[i] == c) {
			res++;
		}
	}
	return res;
}

void Strcpy(const char* source, char* destination) {
	for (size_t i = 0; i < Strlen(source); i++)
	{
		destination[i] = source[i];
	}

}

void Strcpy2(const char* source, char* destination) {
	int idx = 0;
	while (source[idx] != 0) {
		destination[idx] = source[idx];
		idx++;
	}
}

void Strncpy(const char* source, char* destination, size_t num) {
	for (size_t i = 0; i < num; i++)
	{
		destination[i] = source[i];
	}
}

void Strncpy2(const char* source, char* destination, size_t num) {
	int idx = 0;
	while (source[idx] != 0 || idx > num) {
		destination[idx] = source[idx];
		idx++;
	}
}

int main()
{

	/*MyLinkedList* linkedList = new MyLinkedList();

	linkedList->AddBeginning(10);
	linkedList->AddBeginning(20);
	linkedList->AddLast(5);
	linkedList->AddLast(6);
	linkedList->AddLast(7);
	linkedList->AddLast(200);

	linkedList->PrintLinkedList();

	linkedList->AddInPosition(2, 2);
	linkedList->PrintLinkedList();

	linkedList->RemoveFirst();
	linkedList->PrintLinkedList();

	linkedList->RemoveLast();
	linkedList->PrintLinkedList();

	char toto[100] = "toto";

	char chaine[250] = {};
	Strcpy2(toto, chaine);

	printf("%s", chaine);*/

	IntArray toto(4);
	for (int i = 0; i < 4; ++i)
		toto.set(i, 2 * i);
	toto.Insert(3);
	toto.Insert(7);
	toto.Insert(9);
	toto.QSort();
	return 0;
	

}