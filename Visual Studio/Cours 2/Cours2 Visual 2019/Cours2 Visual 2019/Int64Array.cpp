#include "Int64Array.hpp"

void Int64Array::ensure(int size)
{
	if (size <= maxSize)
		return;
	int oldSize = maxSize;
	maxSize = curSize = size;
	data = (int64*)realloc(data, maxSize * sizeof(int64));
	zero_memory(data + oldSize, maxSize - oldSize);
}

void Int64Array::set_unsafe(int pos, int64 elem)
{
	data[pos] = elem;
}

void Int64Array::set(int pos, int64 elem)
{
	ensure( pos + 1);
	set_unsafe(pos, elem);

}

void Int64Array::push_back(int64 elem)
{
	set(curSize, elem);
}

void Int64Array::push_front(int64 elem)
{
	insert(0, elem);
	
}


void Int64Array::push_right(int pos)
{
	ensure(maxSize + 1);
	_shift_from_to(maxSize, pos);
}


void Int64Array::insert(int pos, int64 elem)
{
	push_right(pos);
	set(pos, elem);
}

void Int64Array::insert_ordered(int64 elem)
{
	
	//if(elem < data[a])
		//insert(a,elem)
	//else
	//	_shift()
}

int Int64Array::searchPosition(int64 elem)
{
	//manque le cas où on ne trouve pas l'élément dans le tablo

	if (*data == elem)
		return 0;

	++data;
	return 1 + searchPosition(elem);
}

void Int64Array::zero_memory(int64* data, int bytes)
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

	zero_memory(mem + 1, bytes);
}

void Int64Array::_shift_from_to(int end, int cur)
{
	if (end == cur)
		return;

	data[end] = data[end - 1];

	end--;
	_shift_from_to(end, cur);
}





