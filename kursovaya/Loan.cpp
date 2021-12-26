#include "Loan.h"
#include"Interface.h"

Loan::Compare_mode Loan::cmpMode = Loan::Compare_mode::Id;

void Loan::open_loan(Interface& obj)
{
	obj.Loans.add(*this);
	obj.last_operation.push("add");
	obj.last_Loan.push(*this);
}

void Loan::monthly_fee(Interface& obj)
{
	if (Algorithm<Loan>::is_exist(*this, obj.Loans.begin(), obj.Loans.end()))
	{
		double month_percent = (double)percents / 1200;
		double coef = month_percent * pow(1 + month_percent, monthes) / (pow(1 + month_percent, monthes) - 1);
		cout << "Monthly fee = " << coef * amount << " BYN" << endl;
	}
	else
		cout << "Smile :) You don't have a loan\n";
}

void Loan::identify_loan(Interface& obj)
{
	Loan temp;
	temp.set_ID(this->get_ID());
	vector<Loan*> founded;
	Algorithm<Loan>::find(temp, founded, obj.Loans.begin(), obj.Loans.end());
	if (!founded.empty())
		*this = *founded[0];
	this->identify_name(obj);
}

void Loan::show_loan(Interface& obj)
{
	if (Algorithm<Loan>::is_exist(*this, obj.Loans.begin(), obj.Loans.end()))
		cout << first_name << ", your loan:\n" << "Amount = " <<
		amount << " BYN, Monthes = " << monthes << ", Percents = " << percents << " %, Left monthes = " 
		<< left_months << endl;
	else
		cout << "Smile :) You don't have a loan\n";
}

bool Loan::check_loan(Interface& obj)
{
	vector<Loan*> founded;
	Algorithm<Loan>::find(*this, founded, obj.Loans.begin(), obj.Loans.end());
	if (!founded.empty())
	{
		*this = *founded[0];
		cout << first_name << ", You already have a loan\nAmount = "
			<< amount << "  BYN, Monthes = " << monthes << ", Percents = " << percents << "%\n";
		return false;
	}

	if (!age_check())
		return false;
	return true;
}

void Loan::pay_loan(Interface& obj)
{
	vector<Loan*> founded;
	Algorithm<Loan>::find(*this, founded, obj.Loans.begin(), obj.Loans.end());
	if (!founded.empty())
	{
		(*founded[0]).left_months--;
		*this = *founded[0];
		if ((*founded[0]).left_months == 0)
			(*founded[0]).close_loan(obj);
	}
	else
		cout << "You don't have a loan!\n";
}

void Loan::close_loan(Interface& obj)
{
	if (!Algorithm<Loan>::is_exist(*this, obj.Loans.begin(), obj.Loans.end()))
	{
		cout << "You don't have an opened loans!\n";
		return;
	}
	if (left_months > monthes / 2) {
		cout << "You should pay 50 or more % of loan, to have a possibility to close it\n";
		return;
	}

	obj.last_operation.push("delete");

	if (obj.Loans.get_head()->data == *this)
	{
		obj.Loans.set_head(obj.Loans.get_head()->next);
		obj.last_Loan.push(obj.Loans.pop());
		return;
	}

	obj.last_Loan.push(Algorithm<Loan>::delete_item(*this, obj.Loans.begin(), obj.Loans.end()));
}

void Loan::item_to_sort()
{
	cout << "By which field do you want to sort:\n [ 1 ] - Surname\n [ 2 ] - Name" <<
		"\n [ 3 ] - ID\n [ 4 ] - Amount\n [ 5 ] - Monthes\n [ 6 ] - Percents\n";
	cout << "Choose: ";
	switch (UsmExc::correct_number<int>(1, 6))
	{
	case 1: cmpMode = Compare_mode::Surname; break;
	case 2: cmpMode = Compare_mode::Name; break;
	case 3: cmpMode = Compare_mode::Id; break;
	case 4: cmpMode = Compare_mode::Amount; break;
	case 5: cmpMode = Compare_mode::Monthes; break;
	case 6: cmpMode = Compare_mode::Percents; break;
	}
}

Loan& Loan::item_to_find()
{
	int choose = 0;
	cout << "Fields:\n [ 1 ] - Surname\n [ 2 ] - Name\n [ 3 ] - ID\n [ 4 ] - Amount\n [ 5 ] - Monthes\n [ 6 ] - Percents\n";
	do {
		cout << "Choose by which fields we will search (input 0 to end) = ";
		choose = UsmExc::correct_number(0, 6);
		switch (choose)
		{
		case 1: {
			cout << "Enter Surname to search = ";
			set_surname(UsmExc::correct_string(15));
		}break;
		case 2: {
			cout << "Enter Name to search = ";
			set_name(UsmExc::correct_string(15));
		}break;
		case 3: {
			cout << "Enter ID to seacrh = ";
			set_ID(UsmExc::correct_number<int>(1));
		}break;
		case 4: {
			cout << "Enter Amount to search = ";
			set_amount(UsmExc::correct_number<int>(1));
		}break;
		case 5: {
			cout << "Enter Number of Months to search = ";
			set_months(UsmExc::correct_number<int>(1));
		}break;
		case 6: {
			cout << "Enter Percents to search = ";
			set_percents(UsmExc::correct_number<int>(1));
		}
		default:
			break;
		}
	} while (choose != 0);
	return *this;
}

int Loan::get_leftMonths()
{
	return left_months;
}

void Loan::change(Interface& obj)
{
	obj.last_Loan.push(*this);
	obj.last_operation.push("change");
	cout << "We change:\n [ 1 ] - Surname \t [ 6 ] - Back\n [ 2 ] - Name\n [ 3 ] - Amount\n [ 4 ] - Months\n [ 5 ] - Percents\n Choice: ";
	switch (UsmExc::correct_number<int>(1, 6))
	{
	case 1: {
		cout << "Enter new Surname: ";
		set_surname(UsmExc::correct_string(15));
	}break;
	case 2: {
		cout << "Enter new Name: ";
		set_name(UsmExc::correct_string(15));
	}break;
	case 3: {
		cout << "Enter new Amount of loan: ";
		set_amount(UsmExc::correct_number<int>(1));
	}break;
	case 4: {
		cout << "Enter new Months count: ";
		set_months(UsmExc::correct_number<int>(1));
		left_months = monthes;
	}break;
	case 5: {
		cout << "Enter new Percents: ";
		set_percents(UsmExc::correct_number<int>(1));
	}break;
	default:
		return;
		break;
	}
}

Loan::~Loan()
{
}

Loan::Loan() : Individual()
{
	amount = percents = monthes = left_months = 0;
}

Loan::Loan(const Loan& obj) : Individual(obj)
{
	amount = obj.amount;
	monthes = obj.monthes;
	percents = obj.percents;
	left_months = obj.left_months;
}

void Loan::print()
{
	dynamic_cast<Individual&>(*this).print();
	cout << setw(15) << "Amount, BYN" << setw(15) << "Monthes" << setw(15) << "Percents, %"
		<< setw(15) << "Left months";
}

void Loan::set_months(int months)
{
	left_months = monthes = months;
}

void Loan::set_amount(int amount)
{
	this->amount = amount;
}

void Loan::set_percents(int percents)
{
	this->percents = percents;
}

bool Loan::operator==(const Loan& obj)
{
	if (!(dynamic_cast<Bank&>(*this) == obj)) return false;
	if (obj.amount and obj.amount != amount) return false;
	if (obj.monthes and obj.monthes != monthes) return false;
	if (obj.percents and obj.percents != percents) return false;
	return true;
}

void Loan::operator=(Loan& obj)
{
	dynamic_cast<Individual&>(*this) = obj;
	this->amount = obj.amount;
	this->monthes = obj.monthes;
	this->percents = obj.percents;
	this->left_months = obj.left_months;
}

bool Loan::operator<(Loan& obj)
{
	switch (cmpMode)
	{
	case Loan::Compare_mode::Surname: return last_name < obj.last_name;
		break;
	case Loan::Compare_mode::Name: return first_name < obj.first_name;
		break;
	case Loan::Compare_mode::Id: return ID < obj.ID;
		break;
	case Loan::Compare_mode::Monthes: return monthes < obj.monthes;
		break;
	case Loan::Compare_mode::Amount: return amount < obj.amount;
		break;
	case Loan::Compare_mode::Percents: return percents < obj.percents;
		break;
	default:
		return false;
	}
}


bool Loan::operator>(Loan& obj)
{
	switch (cmpMode)
	{
	case Loan::Compare_mode::Surname: return last_name > obj.last_name;
		break;
	case Loan::Compare_mode::Name: return first_name > obj.first_name;
		break;
	case Loan::Compare_mode::Id: return ID > obj.ID;
		break;
	case Loan::Compare_mode::Monthes: return monthes > obj.monthes;
		break;
	case Loan::Compare_mode::Amount: return amount > obj.amount;
		break;
	case Loan::Compare_mode::Percents: return percents > obj.percents;
		break;
	default:
		return false;
	}
}


istream& operator>>(istream& is, Loan& obj)
{
	is >> dynamic_cast<Individual&>(obj);
	return is;
}

ostream& operator<<(ostream& os, Loan& obj)
{
	os << dynamic_cast<Individual&>(obj);
	os << setw(15) << obj.amount << setw(15) << obj.monthes << setw(15)
		<< obj.percents << setw(15) << obj.left_months;
	return os;
}

ifstream& operator>>(ifstream& is, Loan& obj)
{
	obj.first_name = obj.last_name = "";
	int flag = 0;
	obj.ID = UsmExc::correct_file_int(is, 1);
	if (obj.ID == INT_MIN) flag++;
	obj.amount = UsmExc::correct_file_int(is, 0);
	if (obj.amount == INT_MIN) flag++;
	obj.monthes = UsmExc::correct_file_int(is, 0);
	if (obj.monthes == INT_MIN) flag++;
	obj.percents = UsmExc::correct_file_int(is, 0);
	if (obj.percents == INT_MIN) flag++;
	obj.left_months = UsmExc::correct_file_int(is, 0);
	if (obj.left_months == INT_MIN) flag++;
	if (flag > 0 and flag < 5) {
		cout << "File (Loans) is corrupted!\n";
		terminate();
	}
	return is;
}

ofstream& operator <<(ofstream& os, Loan& obj)
{
	if (obj.amount)
		os << obj.ID << " " << obj.amount << " " << obj.monthes << " "
		<< obj.percents << " " << obj.left_months << endl;
	return os;
}

