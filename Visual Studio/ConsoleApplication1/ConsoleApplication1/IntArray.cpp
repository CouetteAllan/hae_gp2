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
		return;

	data = (int*)realloc(data, (newSize + 1) * sizeof(int));

	for (size_t i = size; i < newSize; i++)
	{
		data[i] = 0;
	}
	size = (newSize + 1);
}

void IntArray::Insert(int value)
{
	int temp = 0;
	int tempIdx = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] > temp) {
			temp = data[i];
			tempIdx = i;
		}
	}

	Resize(size + 1);

	set(tempIdx, temp);


}

void IntArray::InsertAt(int idx, int value)
{
	int sz = size;
	Resize(std::max(idx+1, size + 1));

	for (; sz >= idx; sz--)
		data[sz] = data[sz - 1];
	data[idx] = value;

}
