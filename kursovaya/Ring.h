#pragma once
#include<iostream>
#include<string>
#include"RingIterator.cpp"


template<typename T>
class Ring
{
	friend class RingIterator<T>;
private:
	Node<T>* head;
public:
	Ring()
	{
		head = nullptr;
	}

	void show();
	void add(T& item);
	T& pop();
	bool is_empty();

	Node<T>* get_head();
	void set_head(Node<T>* h);

	RingIterator<T> begin();
	RingIterator<T> end();
	
	~Ring()
	{
		if (!is_empty())
		{
			Node<T>* t1 = head->next, * t2;
			while (t1 != head)
			{
				t2 = t1->next;
				delete t1;
				t1 = t2;
			}
			delete head;
		}
	}
};
