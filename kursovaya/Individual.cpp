#include "Individual.h"

void Individual::set_age(int new_age)
{
	this->clientAge = new_age;
}

int Individual::get_age()
{
	return clientAge;
}

bool Individual::age_check()
{
	if (clientAge < 18)
	{
		cout << first_name << ", you are too young to do this operation!\nWe wait to you after " 
			<< 18 - clientAge << " years!" << endl;
		return false;
	}
	return true;
}

void Individual::print()
{
	dynamic_cast<Bank&>(*this).print();
}

void Individual::operator=(Individual& obj)
{
	dynamic_cast<Bank&>(*this) = obj;
}


Individual::Individual() : Bank()
{
	clientAge = 0;
}

Individual::Individual(const Individual& obj) : Bank(obj)
{
	clientAge = 18;
}

Individual::~Individual()
{
}

istream& operator>>(istream& is, Individual& obj)
{
	is >> dynamic_cast<Bank&>(obj);
	cout << "Enter client age = ";
	obj.clientAge = UsmExc::correct_number<int>(1, 100);
	return is;
}

ostream& operator<<(ostream& os, Individual& obj)
{
	os << dynamic_cast<Bank&>(obj);
	return os;
}
