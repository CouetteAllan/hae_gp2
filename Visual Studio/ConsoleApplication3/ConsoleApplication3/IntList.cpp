#include "IntList.hpp"

int length(IntList* l)
{
	if (!l)		return 0;
	else		return 1 + length(l->next);

}


IntList* appendFirst(IntList* l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	v->next = l;
	return v;
}

IntList* appendLast(IntList* l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	if (!l)
		return appendFirst(l, value);


	if (l->next)
		appendLast(l->next, value);
	else
		l->next = appendFirst(nullptr, value);

	return l;

}

IntList* remove(IntList* l, int value)
{
	//récurrence pour arriver jusqu'à la valeur qu'on veut retirer

	if (!l) {
		return nullptr;
	}

	if (l->value == value) {

		//delete cette liste là
		IntList* rest = l->next;
		free(l);
		return rest;
	}
	else {
		l->next = remove(l->next, value);
		return l;
	}
	
	



}


