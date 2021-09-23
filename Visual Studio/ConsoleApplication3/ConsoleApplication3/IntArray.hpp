#pragma once

class IntArray {
	int* data = nullptr;

public:

	IntArray(int size) {
		//faire l'allocation dynamic des data qui sera de taille "suffisament grande"
		data = new int[size];
		
	}

	void set(int idx, int value) {
		//récupérer la donnée à la case idx et l'affecter
		data[idx] = value;
	};

	int get(int idx) {
		//récupérer la donnée à la case idx et la retourner
		return data[idx];
	};
};