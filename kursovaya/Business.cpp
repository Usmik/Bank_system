#include "Business.h"



void Business::set_income(int income)
{
	month_income = income;
}

int Business::get_income()
{
	return month_income;
}

bool Business::income_check()
{
	if (month_income < 1000)
	{
		cout << "Sorry, your month income should be more then 1000!\n";
		return false;
	}
	return true;
}

void Business::print()
{
	dynamic_cast<Bank&>(*this).print();
}

Business::Business() : Bank()
{
	month_income = 0;
}

Business::Business(const Business& obj) : Bank(obj)
{
	month_income = 1000;
}

Business::~Business()
{
}

istream& operator>>(istream& is, Business& obj)
{
	is >> dynamic_cast<Bank&>(obj);
	cout << "Enter your income per month = ";
	obj.month_income = UsmExc::correct_number<int>(1);
	return is;
}

ostream& operator<<(ostream& os, Business& obj)
{
	os << dynamic_cast<Bank&>(obj);
	return os;
}
