#pragma once
#include"Ring.h"
#include<vector>
#include<iomanip>


template<typename T>
void Ring<T>::show()
{
	if (is_empty())
	{
		std::cout << "Have no records" << std::endl;
		return;
	}
	RingIterator<T> beg(this->begin()), end(this->end());
	std::cout << std::setw(5) << "#";
	(*beg).print();
	std::cout << std::endl;
	int i = 1;
	do
	{
		std::cout << std::setw(5) << i++ << *beg << std::endl;
		beg++;
	} while (beg != end);
}


template<typename T>
void Ring<T>::add(T& item)
{
	Node<T>* newItem = new Node<T>;
	newItem->data = item;
	if (is_empty())
	{
		head = newItem;
		head->next = head;
		head->prev = head;
	}
	else
	{
		newItem->next = head;
		newItem->prev = head->prev;
		head->prev->next = newItem;
		head->prev = newItem;
	}
}


template<typename T>
T& Ring<T>::pop()
{
	if(head->next == head)
	{
		Node<T>* temp = head;
		head = nullptr;
		return temp->data;
	}
	Node<T>* cur = head->prev;
	head->prev = cur->prev;
	head->prev->next = head;
	return cur->data;
}


template<typename T>
bool Ring<T>::is_empty()
{
	return head == nullptr;
}

template<typename T>
Node<T>* Ring<T>::get_head()
{
	return head;
}

template<typename T>
void Ring<T>::set_head(Node<T>* h)
{
	head = h;
}


template<typename T>
RingIterator<T> Ring<T>::begin()
{
	return head;
}


template<typename T>
RingIterator<T> Ring<T>::end()
{
	return head;
}

