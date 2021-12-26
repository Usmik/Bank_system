#pragma once
#include "RingIterator.h"

template<typename T>
RingIterator<T>& RingIterator<T>::operator++(int)
{
	current = current->next;
	return *this;
}

template<typename T>
RingIterator<T>& RingIterator<T>::operator--(int)
{
	current = current->prev;
	return *this;
}


template<typename T>
T& RingIterator<T>::operator*()
{
	return current->data;
}

template<typename T>
Node<T>* RingIterator<T>::operator->()
{
	return current;
}

template<typename T>
bool RingIterator<T>::operator==(RingIterator<T>& other)
{
	return current == other.current;
}

template<typename T>
bool RingIterator<T>::operator!=(RingIterator<T>& other)
{
	return current != other.current;
}

template<typename T>
bool RingIterator<T>::operator==(std::nullptr_t nullp)
{
	return current == nullptr;
}

template<typename T>
void RingIterator<T>::operator=(RingIterator<T>& other)
{
	current = other.current;
}
