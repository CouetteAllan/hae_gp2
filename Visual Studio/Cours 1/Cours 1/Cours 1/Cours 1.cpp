#include <iostream>
#include "IntArray.hpp"





/*int main01()
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
}*/

void Memcpy(char* dst, const char* src, int len) {
	for (size_t i = 0; i < len; i++)
		dst[i] = src[i];
}

const char * StrChr(const char * grange, char chat) {
	int index = 0;
	char found;
	while (*grange) {
		if (*grange == chat)
			return grange;
		grange++;

	}
	return nullptr;
}

const char * StrStr(const char * a, const char* b) {
	
	size_t bLen = strlen(b);

	while (*a){
		bool found = true;

		for (size_t i = 0; i < bLen; i++){
			if (a[i] != b[i]) {
				a++;
				found = false;
				break;
			}
		}
		if (found) 
			return a;
		

	}
	return nullptr;
}/*
int main2() {
	int s[4] = { 0,0,0,0 };
	int t[4] = { 0,1,2,3 };

	const char* toto = "Bonjour je m'appelle Toto";
	const char* tata = "Bonsoir";

	const char * result = StrStr(toto, tata);

	printf(result);
}*/


int Add(int a, int b) {
	if (b == 0)
		return a;
	else
		if (b > 0)
			return 1 + Add(a, b - 1);
		else
			return -1 + Add(a, b + 1);
}

int Sub(int a, int b) {
	return Add(a, -b);
}

int Mul(int a, int b) {

	if (b == 0 || a == 0)
		return 0;
	
	if (b == 1)
		return a;
	if (a == 1)
		return b;

	if (b > 0)
		return a + Mul(a, b - 1);
	else
		return -a + Mul(a, b + 1);
}

int Div(int a, int b) {
	if (b == 0) {
		throw "division by zero";
	}
	if (a == 0)
		return 0;
	if (b == 1)
		return a;
	if (a < b)
		return 0;

	return 1 + Div(Sub(a, b), b);
}

int Mod(int a, int b); // reste de la division

int Len(int vecX, int vecY); // avec les fonctions precédentes



int main() {
	int c = Div(10, 2);



	return 0;
}
