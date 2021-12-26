#pragma once
#include<vector>
#include"RingIterator.h"


template<typename T>
class Algorithm
{
public:
	static void find(const T& item, std::vector<T*>& obj, RingIterator<T> begin, RingIterator<T> end);
	static bool is_exist(T& item, RingIterator<T> begin, RingIterator<T> end);
	static void sort(RingIterator<T> begin, RingIterator<T> end);
	static T& delete_item(T& item, RingIterator<T> begin, RingIterator<T> end);
	//static int change(RingIterator<T> begin, RingIterator<T> end);
};

