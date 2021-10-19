#pragma once
#include <cstdlib>
#include <utility>
#include <functional>
#include <iostream>

class IntArray {
public :
	int* data = nullptr;
	int maxSize = 0;
	int curSize = 0;

	IntArray();

	IntArray(int size);

	~IntArray();

	void ensure(int size);
	void set_unsafe(int pos, int elem);
	void set(int pos, int elem);
	void push_back(int elem);
	void push_front(int elem);
	void insert(int pos, int elem);
};



