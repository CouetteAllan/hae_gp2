#pragma once
#include <cstdlib>
#include <stdint.h>
#include <utility>
#include <functional>
#include <iostream>

using int64 = int64_t;

class Int64Array {
public :
	int64_t* data = nullptr;
	int maxSize = 0;
	int curSize = 0;

	Int64Array() {
		data = (int64*)malloc(30 * sizeof(int64));
		maxSize = 30;
		curSize = 0;
		zero_memory(data,maxSize);
	}

	Int64Array(int size) {
		data = (int64*)malloc(size * sizeof(int64));
		maxSize = size;
		curSize = size;
		zero_memory(data,maxSize);
	}

	~Int64Array() {
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	}

	void ensure(int size);

	void set_unsafe(int pos, int64 elem);

	void set(int pos, int64 elem);

	void push_back(int64 elem);

	void push_front(int64 elem);

	void push_right(int pos);

	void insert(int pos, int64 elem);

	void zero_memory(int64* data, int bytes);

	int64& get(int pos)
	{
		ensure(pos + 1);
		if (pos >= curSize)
			curSize = pos + 1;
		return data[pos];
	}

	int64& operator[](int idx) {
		return get(idx);
	};


};



