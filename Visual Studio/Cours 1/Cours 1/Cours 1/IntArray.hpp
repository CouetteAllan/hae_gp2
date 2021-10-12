#pragma once
#include <cstdlib>
#include <utility>
#include <functional>
#include <iostream>



//#define MALLOC_VERSION
class IntArray {
	int* data = nullptr;
	int size = 0;

public:

	IntArray() {
		//faire l'allocation dynamic des data qui sera de taille "suffisament grande"
		//data = new int[size = 30];
		data = (int*)malloc(30 * sizeof(int));
	};

	IntArray(int size) {
		//faire l'allocation dynamic des data qui sera de taille "suffisament grande"
		data = new int[size];
		this->size = size;

	};

	~IntArray() {
		//libérer la mémoire allouée par le constructeur
		delete[] data;
	}

	void set(int idx, int value);

	void Resize(int newSize);

	void Insert(int value);

	void InsertAt(int idx, int value);

	void Reverse();

	void Iter(std::function<void(int)> f);

	int Sum();

	static IntArray* fromArray(int* data, int len);

	void QSort(/*void* arr, size_t elementCount, size_t elementSize,*/ );

	int get(int idx) {
		//si indx est hors des bornes du tableau
		//faire throw exception:out of bounds;
		if (idx > size || idx < 0) {
			throw "exception:out of bounds";
		}



		//récupérer la donnée à la case idx et la retourner
		return data[idx];
	};
};
