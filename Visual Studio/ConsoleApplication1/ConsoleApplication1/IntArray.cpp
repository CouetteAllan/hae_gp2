#include "IntArray.hpp"

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
