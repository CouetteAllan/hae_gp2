#include "IntTree.hpp"

int Count(IntTree * head)
{
	if (!head)
		return 0;

	return 1 + Count(head->fg) + Count(head->fd);
}

IntTree * Create(int value)
{
	IntTree* v = (IntTree*)malloc(sizeof(IntTree));
	v->value = value;
	v->fd = v->fg = nullptr;

	return v;
}

IntTree * Insert(IntTree * head, int value)
{
	if (!head) {
		return Create(value);
	}

	if (head->value > value) {
		if (head->fg)
			Insert(head->fg, value);
		else
			head->fg = Create(value);

	}
	else {
		if (head->fd)
			Insert(head->fd, value);
		else
			head->fd = Create(value);
	}


	return nullptr;
}

IntTree * Remove(IntTree * head, int value)
{
	return nullptr;
}

IntTree * Merge(IntTree * a, IntTree * b)
{
	return nullptr;
}
