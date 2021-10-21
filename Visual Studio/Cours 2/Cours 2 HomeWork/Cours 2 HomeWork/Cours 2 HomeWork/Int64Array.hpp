#pragma once
#include <cstdlib>
#include <stdint.h>
#include <utility>
#include <functional>
#include <iostream>

using int64 = int64_t;
class Int64Array {
public:
	int64* data = nullptr;
	int currentSize = 0;
	int maxSize = 0;

	Int64Array(int size = 0) {
		if (size == 0) {
			maxSize = 16;
			currentSize = size;
		}
		else {
			maxSize = size;
			currentSize = size;
		}
		data = (int64*)malloc(size * sizeof(int64));
		zero_memory(data, maxSize);
	}

	~Int64Array() {
		free(data);
		data = nullptr;
		currentSize = 0;
		maxSize = 0;
	}

	void ensure(int size);

	void set_unsafe(int pos, int64 elem);

	void set(int pos, int64 elem);

	void push_back(int64 elem);

	void push_right(int pos);

	void push_front(int64 elem);

	void insert(int pos, int64 elem);

	void zero_memory(int64* data, int bytes);

};