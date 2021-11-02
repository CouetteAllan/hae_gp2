#pragma once
#include <cstdlib>
#include <stdint.h>
#include <utility>
#include <functional>
#include <iostream>


template<typename Type>
class List {
public:
	Type  val = {};
	List*   next = nullptr;

	List(Type elem) {
		next = nullptr;
		val = elem;
	}
	
	List(Type elem, List* n) {
		next = n;
		val = elem;
	}

	List*  remove(Type elem)
	{
		if (val == elem) {
			List*n = next;
			delete this;
			return n;
		}
		else {
			if (next)
				next->remove(elem);
		}
	}

	List*  push_first(Type elem)
	{
		auto newNode = new List(elem, this);
		return newNode;

	}

	List*  push_back(Type elem)
	{
		List* newNode = new List(elem);

		if (!this)
			return push_first(elem);

		if (next)
			next->push_back(elem);
		else
			next = newNode;

		return this;
	}


};