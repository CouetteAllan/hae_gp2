#pragma once

#include <cstdlib>
#include <cstring>

struct IntList {
	int			value = 0.0;
	IntList*	next = nullptr;

};


IntList* append(IntList* l, int value);
IntList* appendFirst(IntList* l, int value);
IntList* appendLast(IntList* l, int value);
IntList* remove(IntList* l, int value);
int length(IntList* l);

