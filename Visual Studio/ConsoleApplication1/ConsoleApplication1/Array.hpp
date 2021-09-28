#pragma once

class IntArray {
	int* data = nullptr;
	int size = 0;

public:

	IntArray(){
		data = new int[size = 30];
	}

	IntArray(int size) {
		data = new int[size];
		size = this->size;
	}

	void Set(int index, int value) {
		data[index] = value;
	}

	int Get(int index) {
		return data[index];
	}



};