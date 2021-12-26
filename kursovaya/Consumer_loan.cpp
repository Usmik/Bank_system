#include "Consumer_loan.h"

Consumer_loan::Consumer_loan()
{
	aim_of_loan = "";
}

Consumer_loan::~Consumer_loan()
{
}

void Consumer_loan::take_loan(Interface& obj)
{
	if (!check_loan(obj))
		return;
	cout << "Enter an aim of loan = ";
	aim_of_loan = UsmExc::correct_string(15);

	if (aim_of_loan.length() < 3){
		cout << "Loan declined!\n";
		return;
	}

	cout << "Choose, how many BYN you will take [ 100 - 5000 ]\nChoice = ";
	amount = UsmExc::correct_number<int>(100, 5000);

	if (amount <= 2000) percents = 35;
	else if (amount <= 3700) percents = 30;
	else percents = 27;

	cout << "Choose the loan term [ 6 - 24 ] monthes\nChoice: ";
	left_months = monthes = UsmExc::correct_number<int>(6, 24);

	open_loan(obj);
}

istream& operator>>(istream& is, Consumer_loan& obj)
{
	is >> dynamic_cast<Loan&>(obj);
	return is;
}

ostream& operator<<(ostream& os, Consumer_loan& obj)
{
	os << dynamic_cast<Loan&>(obj);
	return os;
}


