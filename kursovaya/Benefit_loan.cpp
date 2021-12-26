#include "Benefit_loan.h"

Benefit_loan::Benefit_loan() :Loan()
{
	benefit = "";
}

Benefit_loan::~Benefit_loan()
{
}

void Benefit_loan::take_loan(Interface& obj)
{
	if (!check_loan(obj))
		return;
	cout << "Our Bank supports only Education and Housing\nEnter a benefit = ";
	benefit = UsmExc::correct_string(15);

	if (benefit == "Education" or benefit == "education")
	{
		percents = 25;
		cout << "Choose the loan term: [ 6 - 48 ] monthes\nChoice: ";
		left_months = monthes = UsmExc::correct_number<int>(6, 48);
		cout << "Choose, how many BYN you will take [ 2000 - 12000 ]\nChoice = ";
		amount = UsmExc::correct_number<int>(2000, 12000);
	}
	else if (benefit == "Housing" or benefit == "housing")
	{
		percents = 17;
		cout << "Choose the loan term: [ 24 - 72 ] monthes\nChoice: ";
		left_months = monthes = UsmExc::correct_number<int>(24, 72);
		cout << "Choose, how many BYN you will take [ 4000 - 20000 ]\nChoice = ";
		amount = UsmExc::correct_number<int>(4000, 20000);
	}
	else
	{
		cout << "We don't support " << benefit << " loans\n";
		return;
	}
	open_loan(obj);
}

istream& operator>>(istream& is, Benefit_loan& obj)
{
	is >> dynamic_cast<Loan&>(obj);
	return is;
}

ostream& operator<<(ostream& os, Benefit_loan& obj)
{
	os << dynamic_cast<Loan&>(obj);
	return os;
}
