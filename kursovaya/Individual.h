#pragma once
#include"Bank.h"

class Individual: public Bank
{
protected:
	int clientAge;
public:
	void set_age(int new_age);
	int get_age();
	bool age_check();
	void print();
	void operator=(Individual& obj);
	friend istream& operator >> (istream& is, Individual& obj);
	friend ostream& operator << (ostream& os, Individual& obj);
	Individual();
	Individual(const Individual& obj);
	~Individual();
};

