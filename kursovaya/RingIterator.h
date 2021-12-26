#pragma once
#include"RingNode.h"


template<typename T>
class Ring;

template<typename T>
class RingIterator
{
	friend class Ring<T>;
private:
	Node<T>* current;
public:
	RingIterator(Node<T>* ptr)
	{
		current = ptr;
	};
	RingIterator<T>& operator ++(int);
	RingIterator<T>& operator --(int);

	T& operator *();
	Node<T>* operator->();

	bool operator==(RingIterator<T>& other);
	bool operator!=(RingIterator<T>& other);

	bool operator==(std::nullptr_t nullp);

	void operator =(RingIterator<T>& other);
};

