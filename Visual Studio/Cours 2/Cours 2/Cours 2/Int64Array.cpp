#include "Int64Array.hpp"
#include "Chrono.hpp";

void Int64Array::ensure(int size)
{
	if (size <= maxSize)
		return;
	int oldSize = maxSize;
	maxSize = size * 1.75;

	data = (int64*)realloc(data, maxSize * sizeof(int64));

	zero_memory(oldSize, maxSize - oldSize);
}

void Int64Array::set_unsafe(int pos, int64 elem)
{
	data[pos] = elem;
}

void Int64Array::set(int pos, int64 elem)
{
	ensure(pos + 1);
	set_unsafe(pos, elem);

}

void Int64Array::push_back(int64 elem)
{
	set(curSize, elem);
}

void Int64Array::push_front(int64 elem)
{
	insert(0, elem);

}


void Int64Array::push_right(int pos)
{
	ensure(maxSize + 1);
	_shift_from_to(pos, maxSize);
}

void Int64Array::push_left(int pos)
{
	_shift_from_to(maxSize, pos);
}


void Int64Array::insert(int pos, int64 elem)
{
	push_right(pos);
	set(pos, elem);
}

void Int64Array::insert_ordered(int64 elem)
{
	int pos = _insert_ordered_at(0, elem);
	insert(pos, elem);
}

int Int64Array::searchPosition(int64 elem)
{
	return _search_position_in_data(data, elem);
}

void Int64Array::remove(int64 elem)
{
	int pos = searchPosition(elem);
	if (pos >= 0) {
		data[pos] = 0;
		push_left(pos);
		//data = (int64*)realloc(data, maxSize - 1 * sizeof(int64));
	}
	else
		return;
}

void Int64Array::zero_memory(int indx, int bytes)
{
	memset(data + indx, 0, bytes * sizeof(int64));

}

void Int64Array::append_sorted(const int64* t, int size)
{
	if (size <= 0)
		return;
	insert_ordered(t[0]);
	append_sorted(t + 1, size - 1);
}

void Int64Array::load(const int64* arr, int sz)
{
	if (sz == 0)
		return;
	set(curSize, *arr);
	curSize++;
	load(arr + 1, sz - 1);

}

void Int64Array::insertionSort(const int64* arr, int sz)
{
	clear();
	load(arr, sz);

	int j;
	for (size_t i = 1; i < sz; i++)
	{
		j = i;
		while (j > 0 && data[j] < data[j - 1])
		{
			int temp = data[j];
			data[j] = data[j - 1];
			data[j - 1] = temp;
			j--;
		}
	}
}

int Int64Array::bsearch(int64 elem)
{
	return _bsearch(elem, 0, curSize - 1);
}


int Int64Array::_bsearch(int64 elem, int lo, int hi)
{
	if (hi < lo)
		return -1;

	if (elem == data[lo])
		return lo;
	if (elem == data[hi])
		return hi;

	int mid = (hi + lo) / 2;

	if (elem == data[mid])
		return mid;

	if (elem > data[mid]) {
		return _bsearch(elem, mid, hi-1);
	}
	else
		return _bsearch(elem, lo+1, mid);
}

int Int64Array::bsearchIter(int64 elem)
 {
	int left = 0;
	int right = curSize;
	while ( left <= right)
	{
		if (data[left] == elem)
			return left;
		if (data[right] == elem)
			return right;

		int mid = (left + right) / 2;

		if (data[mid] == elem)
			return mid;
		if (data[mid] < elem)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return -1;
}


void Int64Array::_shift_from_to(int end, int cur)
{
	if (cur <= end)
		return;

	data[cur] = data[cur - 1];

	_shift_from_to(end, cur - 1);
}

int Int64Array::_insert_ordered_at(int idx, int64 elem)
{
	if (idx >= curSize)
		return curSize;

	if (elem < data[idx])
		return 0;

	return 1 + _insert_ordered_at(idx + 1, elem);
}


int Int64Array::_search_position_in_data(int64* data, int64 elem)
{
	//manque le cas où la valeur n'est pas trouvée

	if (*data == elem) {
		return 0;
	}

	return 1 + _search_position_in_data(data + 1, elem);
}
