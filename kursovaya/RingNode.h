#pragma once
#include<iostream>

template<typename T>
class Node
{
public:
	T data;
	Node* next;
	Node* prev;
	Node()
	{
		next = prev = nullptr;
	};
};

