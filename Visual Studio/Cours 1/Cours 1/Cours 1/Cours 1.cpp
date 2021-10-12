#include <iostream>
#include "IntArray.hpp"





int main()
{
	IntArray tata(20);

	for (int i = 0; i < 20; ++i)
	{
		tata.set(i, i * i);
	}

	tata.Reverse();

	int s6[6] = { 1,2,3,4,5,6 };

	IntArray* maCopie = IntArray::fromArray(s6, 5);

	return 0;
}
