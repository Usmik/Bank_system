#include "Algorithm.h"
#include"UsmExc.h"

template<typename T>
void Algorithm<T>::find(const T& item, std::vector<T*>& obj, RingIterator<T> begin, RingIterator<T> end)
{
	if (begin == nullptr)
		return;
	do {
		if (*begin == item)
			obj.push_back(&(*begin));
		begin++;
	} while (begin != end);
}

template<typename T>
bool Algorithm<T>::is_exist(T& item, RingIterator<T> begin, RingIterator<T> end)
{
	if (begin == nullptr)
		return false;
	do {
		if (*begin == item)
			return true;
		begin++;
	} while (begin != end);
	return false;
}

template<typename T>
void Algorithm<T>::sort(RingIterator<T> begin, RingIterator<T> end)
{
	if (begin == nullptr)
		return;
	RingIterator<T> j = begin;
	do{
		j = begin;
		do {
			if (*begin > *j)
			{
				T temp = *begin;
				*begin = *j;
				*j = temp;
			}
			j++;
		} while (j != end);
		begin++;
	} while (begin != end);
}

template<typename T>
T& Algorithm<T>::delete_item(T& item, RingIterator<T> begin, RingIterator<T> end)
{
	do {
		if (*begin == item)
		{
			begin->prev->next = begin->next;
			begin->next->prev = begin->prev;
			return *begin;
		}
		begin++;
	} while (begin != end);
	return *begin;
}


