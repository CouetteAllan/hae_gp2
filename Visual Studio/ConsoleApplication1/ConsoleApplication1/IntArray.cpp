#include "IntArray.hpp"
#include <algorithm>

void IntArray::set(int idx, int value)
{
	//si indx est hors des bornes du tableau
		//faire throw exception:out of bounds;

	if (idx > size || idx < 0) {
		throw "exception:out of bounds";
	}

	//récupérer la donnée à la case idx et l'affecter
	data[idx] = value;
}

void IntArray::Resize(int newSize)
{
	if (size >= newSize)
		// 	   sortir
		return;
#ifdef MALLOC_VERSION
	data = (int*)realloc(data, newSize * sizeof(int));
	memset(data + size, 0, (newSize - size) * sizeof(int));
	size = newSize;
#else
	int* ndata = new int[newSize];
	memset(ndata, 0, newSize * sizeof(int));
	memcpy(ndata, data, size * sizeof(int));
	int* oldData = data;
	this->data = ndata;
	delete oldData;
	size = newSize;
#endif
}

void IntArray::Insert(int value)
{
	int idx = 0;
	while ((idx < size) && (data[idx] < value))
	{
		idx++;
	}
	InsertAt(idx, value);

}

void IntArray::InsertAt(int idx, int value)
{
	int sz = size;
	Resize(std::max<int>(idx+1, size + 1));

	for (; sz > idx; sz--)
		data[sz] = data[sz - 1];
	data[idx] = value;

}

static int cmp(const void * v0, const void * v1) {
	return *(int*)v0 - *(int*)v1;
}

void IntArray::QSort()
{
	::qsort(data, size, sizeof(int), cmp);
}
