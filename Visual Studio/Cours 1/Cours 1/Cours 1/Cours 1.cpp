#include <iostream>

int main()
{
	int* toto = new int[150];

	for (int i = 0; i < 150; i++)
	{
		toto[i] = i * i;
	}

	for (int i = 149; i >= 0; i--)
	{
		printf("%i\n", toto[i]);
	}

	return 0;
}
