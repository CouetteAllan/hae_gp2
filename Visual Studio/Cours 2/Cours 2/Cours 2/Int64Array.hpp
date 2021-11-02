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
		zero_memory(0,maxSize);
	}

	Int64Array(int size) {
		data = (int64*)malloc(size * sizeof(int64));
		maxSize = size;
		curSize = size;
		zero_memory(0,maxSize);
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

	void push_left(int pos);

	void insert(int pos, int64 elem);

	void insert_ordered(int64 elem);

	int searchPosition(int64 elem);

	void remove(int64 elem);

	void zero_memory(int indx, int bytes);

	void append_sorted(const int64* t, int size);

	void load(const int64* arr, int sz);

	void insertionSort(const int64* arr, int sz);

	int bsearch(int64 elem);

	int bsearchIter(int64 elem);

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

protected:

	void _shift_from_to(int end, int cur);

	int _insert_ordered_at(int pos, int64 elem);

	int _bsearch(int64 elem, int lo, int hi);

	void clear() {
		curSize = 0;
	}

	int _search_position_in_data(int64* data, int64 elem);
};



