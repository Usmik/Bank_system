#pragma once
#include "Bank.h"

class Business : public Bank
{
protected:
	int month_income;
public:
	void set_income(int income);
	int get_income();
	bool income_check();
	void print();
	Business();
	Business(const Business& obj);
	~Business();
	friend istream& operator >> (istream& is, Business& obj);
	friend ostream& operator << (ostream& os, Business& obj);
};

