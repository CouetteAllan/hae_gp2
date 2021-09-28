// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Toto.h"
#include "Array.hpp"
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

void Strncpy(const char* source, char* destination, size_t num) {
	for (size_t i = 0; i < num; i++)
	{
		destination[i] = source[i];
	}
}

int main()
{
	MyLinkedList* MaListe;



	/*int size = 10;


	IntArray* tablo = new IntArray(size);
	for (size_t i = 0; i < size; i++)
	{
		tablo->Set(i, i * 2);
	}

	for (size_t i = 0; i < size; i++)
	{
		printf("%i\n", tablo->Get(i));
	}


	printf("Nombre de a: %d\n", Countc("banane", 'a'));*/
	return 0;

}