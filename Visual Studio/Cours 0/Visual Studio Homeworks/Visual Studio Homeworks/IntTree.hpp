#pragma once
#include <cstring>
#include <cstdlib>

struct IntTree {

	int value = 0.0;
	IntTree* fg = nullptr;
	IntTree* fd = nullptr;
};

int Count(IntTree* head);
IntTree* Create(int value);
IntTree* Insert(IntTree* head, int value);
IntTree* Remove(IntTree* head, int value);
IntTree* Merge(IntTree* a, IntTree* b);