#include "IntArray.hpp"

inline IntArray::IntArray() {
	data = (int*)malloc(30 * sizeof(int));
	maxSize = 30;
}

inline IntArray::IntArray(int size) {
	data = (int*)malloc(size * sizeof(int));
	maxSize = size;
}

inline IntArray::~IntArray() {
	free(data);
}

void IntArray::ensure(int size)
{

}

void IntArray::set_unsafe(int pos, int elem)
{

}

void IntArray::set(int pos, int elem)
{

}

void IntArray::push_back(int elem)
{

}

void IntArray::push_front(int elem)
{

}

void IntArray::insert(int pos, int elem)
{

}
