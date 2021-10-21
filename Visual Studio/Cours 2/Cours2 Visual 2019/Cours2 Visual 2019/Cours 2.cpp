#include <iostream>
#include "Int64Array.hpp"
#include "Chrono.hpp"

int StrLen(const char* chaine) {
	if (!chaine)
		return 0;

	if (!*chaine)
		return 0;

	return 1 + StrLen(chaine + 1);
}

int StrCmp(const char* a, const char* b) {
	if (*a < *b)
		return -1;
	if (*a > *b)
		return 1;
	if (!*a && !*b)
		return 0;
	return StrCmp(a + 1, b + 1);
}

char* findEnd(char* str) {
	if (!str) {
		return nullptr;
	}
	if (*str)
		return findEnd(str + 1);
	else
		return str;
}


void StrCpy(char* destination, const char* source) {
	
	if (!destination)
		return;
	if (!source)
		return;
	if (!*source)
		return;

	*destination = *source ;
	
	StrCpy(destination + 1, source + 1);

}

char* StrCat(char* destination, const char* source) {

	if (!destination) {
		return nullptr;
	}

	char* destEnd = findEnd(destination);
	StrCpy(destEnd, source);
	return destination;
	
}

const char* StrStr(const char* s0, const char* s1) {
	if (!*s1)
		return s0;
	if (!*s0)
		return nullptr;

	if (*s0 == *s1 && StrStr(s0 + 1, s1 + 1) == s0 + 1)
		return s0;

	return StrStr(s0 + 1, s1);
}

const char* StrChr(const char* dst, char c) {
	if (!dst)
		return nullptr;
	if (!*dst)
		return nullptr;
	if (*dst == c)
		return dst;

	return StrChr(dst + 1, c);
}

/*
int mainRecursive() {
	int c = StrLen("bonjour"); // 7
	int cd = StrLen("");// 0
	int ce = StrLen(nullptr);// 0

	int one = StrCmp("bonsoir", "bon"); // 1
	int minusOne = StrCmp("bonjour", "bonsoir");// -1
	int zero = StrCmp("toto", "toto");// 0

	const char* toto = StrStr("Bonjour le monde", "le monde");//le monde

	const char* tata = StrChr("Hello World", 'o');

	return 0;
}*/

int main()
{
	Int64Array tablo(2);

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < 1000000; i++)
		{
			tablo.push_back(rand() % 56456);
		}
		double t1 = getTimeStamp();
		printf("time elapsed %lld s\n", (t1 - t0));
	}

	{
		double t0 = getTimeStamp();
		Int64Array tiAppend;
		tiAppend.append_sorted(tablo.data, tablo.curSize);
		double t1 = getTimeStamp();
		printf("time elapsed tappend %lld s\n", (t1 - t0));
	}

	{
		double t0 = getTimeStamp();
		Int64Array tiSort;
		tiSort.insertionSort(tablo.data, tablo.curSize);
		double t1 = getTimeStamp();
		printf("time elapsed tsort %lld s\n", (t1 - t0));
	}
	
	//int posFour = tablo.searchPosition(4);
	return 0;
}
