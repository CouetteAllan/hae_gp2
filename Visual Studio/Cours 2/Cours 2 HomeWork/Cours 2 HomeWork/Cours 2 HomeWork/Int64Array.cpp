#include "Int64Array.hpp"

void Int64Array::ensure(int size)
{
	if (size > maxSize) {
		int oldSize = maxSize;
		data = (int64*)realloc(data, size * sizeof(int64));
		maxSize = currentSize = size;
		zero_memory(data + oldSize, maxSize - oldSize);
	}

	return;
}

void Int64Array::set_unsafe(int pos, int64 elem)
{
	data[pos] = elem;
}

void Int64Array::set(int pos, int64 elem)
{
	ensure(pos + 1);
	set_unsafe(pos, elem);
}

void Int64Array::push_back(int64 elem)
{
	set(currentSize, elem);
}

void Int64Array::push_right(int pos)
{
	if (currentSize == pos);


	ensure(maxSize + 1);

	currentSize--;
	push_right(pos);
}

void Int64Array::push_front(int64 elem)
{


}

void Int64Array::insert(int pos, int64 elem)
{
}

void Int64Array::zero_memory(int64 * data, int bytes)
{
	int64* mem = data;

	if (mem == nullptr) {
		return;
	}


	*mem = 0;
	bytes--;
	if (bytes == 0) {
		return;
	}

	zero_memory(data + 1, bytes);
}
