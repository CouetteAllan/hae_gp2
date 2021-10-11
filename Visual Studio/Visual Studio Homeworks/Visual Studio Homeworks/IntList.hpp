#pragma once
#include <cstring>
#include <cstdlib>


struct IntList {
	int data = 0.0;
	IntList* next = nullptr;
};



IntList* AppendFirst(IntList* l, int value);
IntList* AppendLast(IntList* l, int value);
IntList* Remove(IntList* l, int value);
int Count(IntList* l);