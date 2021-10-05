#pragma once
#include <cstdlib>

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
