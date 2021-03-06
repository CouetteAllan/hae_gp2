#include <iostream>
#include "Int64Array.hpp"
#include "Chrono.hpp"
#include "List.hpp"
#include "Tree.hpp"
#include <cstdlib>
#include <stdint.h>
#include <utility>
#include <functional>
#include <vector>

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

	*destination = *source;

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

int mainAlgo() {

	Int64Array tablo(16);

	/*{
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
	}*/
	//int posFour = tablo.searchPosition(4);

	for (size_t i = 0; i < 16; i++)
	{
		tablo[i] = i * 2;
	}

	int found28 = tablo.bsearch(28);
	int found22 = tablo.bsearchIter(22);
	return 0;
}



typedef List<double> ListD;
typedef List<int> ListInt;
typedef List<float> ListFloat;
typedef List<std::string> ListString;
int mainList() {

	std::vector<double> vd = { 0.0,2.0,1.0 };
	vd.push_back(13);
	vd.push_back(15);
	vd[0] = 14;
	for (size_t i = 0; i < vd.size(); i++)
	{
		printf("%f ", vd[i]);
	}
	printf("\n---------------------------------------------------------\n\n");

	for (auto f : vd) {
		printf("%f ", f);
	}
	printf("\n---------------------------------------------------------\n\n");

	for (auto iter = vd.begin(); iter != vd.end();)
	{
		printf("%f ", *iter);
		if (*iter == 1.0)
			iter = vd.erase(iter);
		else
			iter++;
	}
	printf("\n---------------------------------------------------------\n\n");

	return 0;
}



int main()
{
	Tree<float>* tf = new Tree<float>(66.0f);
	Tree<std::string>* ts = new Tree<std::string>("sapin");
	ts->insert("lapin");
	ts->insert("zapin");
	ts->insert("vapin");
	ts->insert("rapin");
	ts->insert("japin");


	ts = ts->remove("zapin");
	return 0;
}