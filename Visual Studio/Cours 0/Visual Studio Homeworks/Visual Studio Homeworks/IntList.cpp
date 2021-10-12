#include "IntList.hpp"



IntList * AppendFirst(IntList * l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->data = value;
	v->next = l;
	return v;
}

IntList * AppendLast(IntList * l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->data = value;

	if (!l) {
		return AppendFirst(l, value);
	}
	
	if (l->next)
		AppendLast(l->next, value);
	else
		l->next = AppendFirst(nullptr, value);

	return l;
}

IntList * Remove(IntList * l, int value)
{
	if (!l) {
		return nullptr;
	}

	if (l->data == value) {
		IntList* rest = l->next;
		free(l);
		return rest;
	}

	else
	{
		l->next = Remove(l->next, value);
		return l;
	}



	return l;
}

int Count(IntList * l)
{
	if (!l)
		return 0;
	
	else
		return 1 + Count(l->next);
}
