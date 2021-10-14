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

int Mod(int a, int b) {
	if (b == 0) {
		throw "division by zero";
	}
	if (a == 0)
		return 0;
	if (b == 1)
		return 0;
	if (a < b)
		return a;
	else {
		return Mod(Sub(a, b), b);
	}

}

int Mod2(int a, int b) {
	return a - Mul(Div(a, b) ,b);

}

int Sqr(int a) {
	return Mul(a, a);
}


int Len(int vecX, int vecY) {
	return 0;
}


int Strlen(const char* chaine) {
	int idx = 0;
	while (chaine[idx] != 0) {
		idx++;
	}

	return idx;
}
int indx = 0;
int StrlenRecursive(const char* chaine) {
	if (nullptr == chaine) {
		return 0;
	}

	if (*chaine == 0) {
		return 0;
	}

	return 1 + StrlenRecursive(chaine + 1);
	
}


void Strcpy(const char* source, char* destination) {
	for (size_t i = 0; i < Strlen(source); i++)
	{
		destination[i] = source[i];
	}
}

void StrcpyRecursive(const char* source, char* destination) {
	if (nullptr == source) {
		return;
	}
	if (nullptr == destination) {
		return;
	}

	if (*source == 0) {
		return;
	}

	*destination = *source;

	StrcpyRecursive(source + 1, destination + 1);

}

void StrncpyRecursive(const char* source, char* destination, int nbChars) {
	if (nullptr == source) {
		return;
	}
	if (*source == 0) {
		return;
	}
	*destination = *source;

	nbChars--;
	if (nbChars == 0)
		return;

	StrncpyRecursive(source + 1, destination + 1,nbChars);

}

void ZeroMemory(void* ptr, int nbByte) {
	if (!ptr) {
		return;
	}
	(char*)ptr = 0;


	nbByte--;
	if (nbByte == 0) {
		return;
	}
	ZeroMemory(ptr, nbByte);
}

void Memcpy(const void* source, void* destination, int nbByte) {

	if (nullptr == source) {
		return;
	}

	*destination = *source;

	nbByte--;
	if (nbByte == 0)
		return;
	Memcpy(source + 1, destination + 1, nbByte);
}

int main() {
	int c = Mod2(26, 3);

	int nbrc = StrlenRecursive("Bonjour");
	char tata[256] = {};

	StrncpyRecursive("Bonsoir", tata,4);
	return 0;
}
