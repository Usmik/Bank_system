#include "Deposit.h"
#include"Interface.h"
#include<math.h>

Deposit::Compare_mode Deposit::cmpMode = Deposit::Compare_mode::Id;

void Deposit::set_months(int months)
{
	this->months = months;
}

void Deposit::set_amount(double amount)
{
	this->amount = amount;
}

void Deposit::set_percents(double percents)
{
	this->percents = percents;
}

void Deposit::identify_deposit(Interface& obj)
{
	Deposit temp;
	temp.set_ID(this->get_ID());
	temp.identify_name(obj);
	vector<Deposit*> founded;
	Algorithm<Deposit>::find(temp, founded, obj.Deposits.begin(), obj.Deposits.end());
	if (!founded.empty())
		*this = *founded[0];
}

void Deposit::show_deposit(Interface& obj)
{
	if (Algorithm<Deposit>::is_exist(*this, obj.Deposits.begin(), obj.Deposits.end()))
		cout << first_name << ", your deposit:\n" << "Amount = " <<
		amount << " BYN, Months = " << months << ", Percents = " << percents << " %, Left monthes = "
		<< left_months << endl;
	else
		cout << "You don't have a deposit\n";
}

bool Deposit::deposit_check(Interface& obj)
{
	vector<Deposit*> founded;
	Algorithm<Deposit>::find(*this, founded, obj.Deposits.begin(), obj.Deposits.end());
	if (!founded.empty())
	{
		*this = *founded[0];
		cout << first_name << ", You already have a Deposit\nAmount = "
			<< amount << "  BYN, Months = " << months << ", Percents = " << percents << "%\n";
		return false;
	}

	if (!income_check())
		return false;
	return true;
}

void Deposit::make_deposit(Interface& obj)
{
	if (!deposit_check(obj))
		return;
	cout << "The UsmBank provides revocable deposits:\n" <<
		" -- deposits with capitalization and effective interest rates --\n";
	cout << "Enter amount of deposit [ 100 - 320000 ] BYN\nAmount = ";
	amount = UsmExc::correct_number<double>(100, 320000);
	cout << "Enter number of Month of your deposit [ 3 - 120 ]\nNumber of Months = ";
	left_months = months = UsmExc::correct_number<int>(3, 120);
	if (months > 36 or amount > 5000)
		percents = 25;
	else
		percents = 18;
	obj.Deposits.add(*this);
	obj.last_operation.push("add");
	obj.last_Deposit.push(*this);
}

void Deposit::take_off_deposit(Interface& obj)
{
	if (!Algorithm<Deposit>::is_exist(*this, obj.Deposits.begin(), obj.Deposits.end()))
	{
		cout << "You don't have an maked deposits!\n";
		return;
	}

	obj.last_operation.push("delete");

	if (obj.Deposits.get_head()->data == *this)
	{
		obj.Deposits.set_head(obj.Deposits.get_head()->next);
		obj.last_Deposit.push(obj.Deposits.pop());
		return;
	}

	obj.last_Deposit.push(Algorithm<Deposit>::delete_item(*this, obj.Deposits.begin(), obj.Deposits.end()));
}

void Deposit::change(Interface& obj)
{
	obj.last_Deposit.push(*this);
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
		cout << "Enter new Amount of Deposit: ";
		set_amount(UsmExc::correct_number<double>(1));
	}break;
	case 4: {
		cout << "Enter new number of Months: ";
		set_months(UsmExc::correct_number<int>(1));
		left_months = months;
	}break;
	case 5: {
		cout << "Enter new Percents: ";
		set_percents(UsmExc::correct_number<float>(1, 50));
	}break;
	default:
		return;
		break;
	}
}

void Deposit::item_to_sort()
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

Deposit& Deposit::item_to_find()
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
			set_amount(UsmExc::correct_number<double>(1));
		}break;
		case 5: {
			cout << "Enter Number of Months to search = ";
			set_months(UsmExc::correct_number<int>(1));
		}break;
		case 6: {
			cout << "Enter Percents to search = ";
			set_percents(UsmExc::correct_number<double>(1));
		}
		default:
			break;
		}
	} while (choose != 0);
	return *this;
}

void Deposit::add_to_deposit(Interface& obj)
{
	if (!Algorithm<Deposit>::is_exist(*this, obj.Deposits.begin(), obj.Deposits.end()))
	{
		cout << "You have no created deposits!" << endl;
		return;
	}
	show_deposit(obj);
	cout << "How much money you want to add = ";
	vector<Deposit*> founded;
	Algorithm<Deposit>::find(*this, founded, obj.Deposits.begin(), obj.Deposits.end());
	founded[0]->set_amount(amount + UsmExc::correct_number<double>(0));
	*this = *founded[0];
}

void Deposit::take_part_from_deposit(Interface& obj)
{
	if (!Algorithm<Deposit>::is_exist(*this, obj.Deposits.begin(), obj.Deposits.end()))
	{
		cout << "You have no created deposits!" << endl;
		return;
	}
	show_deposit(obj);
	cout << "How much money you want to take = ";
	vector<Deposit*> founded;
	Algorithm<Deposit>::find(*this, founded, obj.Deposits.begin(), obj.Deposits.end());
	founded[0]->set_amount(amount - UsmExc::correct_number<double>(0, amount));
	*this = *founded[0];
}

void Deposit::print()
{
	dynamic_cast<Business&>(*this).print();
	cout << setw(15) << "Amount, BYN" << setw(15) << "Monthes" << setw(15) << "Percents, %"
		<< setw(15) << "Left months";
}

void Deposit::skip_month(Interface& obj)
{
	RingIterator<Deposit> beg = obj.Deposits.begin();
	RingIterator<Deposit> end = obj.Deposits.end();
	if (beg == nullptr)
		return;
	do {
		(*beg).left_months--;
		(*beg).set_amount((*beg).amount + (*beg).amount * (*beg).percents / 1200);
		if ((*beg).left_months <= 0)
		{
			if (obj.Deposits.get_head()->data == *beg)
			{
				obj.Deposits.set_head(obj.Deposits.get_head()->next);
				obj.Deposits.pop();
				beg++;
				end++;
				if (beg->next->data == end->data)
					break;
				else
					continue;
			}
			else
				Algorithm<Deposit>::delete_item(*beg, obj.Deposits.begin(), obj.Deposits.end());
		}
		beg++;
		if (beg == end)
			break;
	} while (1);
}

void Deposit::calculate_amount(Interface& obj)
{
	if (!Algorithm<Deposit>::is_exist(*this, obj.Deposits.begin(), obj.Deposits.end()))
	{
		cout << "You have no created deposits!" << endl;
		return;
	}
	double probably_cash = pow(1 + percents / 1200, left_months) * amount;
	cout << "Probably cash = " << probably_cash << " BYN\n";
}

bool Deposit::operator==(const Deposit& obj)
{
	if (!(dynamic_cast<Bank&>(*this) == obj)) return false;
	if (obj.amount and obj.amount != amount) return false;
	if (obj.months and obj.months != months) return false;
	if (obj.percents and obj.percents != percents) return false;
	return true;
}

void Deposit::operator=(Deposit& obj)
{
	dynamic_cast<Bank&>(*this) = obj;
	this->amount = obj.amount;
	this->months = obj.months;
	this->percents = obj.percents;
	this->left_months = obj.left_months;
}

bool Deposit::operator<(Deposit& obj)
{
	switch (cmpMode)
	{
	case Deposit::Compare_mode::Surname: return last_name < obj.last_name;
		break;
	case Deposit::Compare_mode::Name: return first_name < obj.first_name;
		break;
	case Deposit::Compare_mode::Id: return ID < obj.ID;
		break;
	case Deposit::Compare_mode::Monthes: return months < obj.months;
		break;
	case Deposit::Compare_mode::Amount: return amount < obj.amount;
		break;
	case Deposit::Compare_mode::Percents: return percents < obj.percents;
		break;
	default:
		return false;
	}
}

bool Deposit::operator>(Deposit& obj)
{
	switch (cmpMode)
	{
	case Deposit::Compare_mode::Surname: return last_name > obj.last_name;
		break;
	case Deposit::Compare_mode::Name: return first_name > obj.first_name;
		break;
	case Deposit::Compare_mode::Id: return ID > obj.ID;
		break;
	case Deposit::Compare_mode::Monthes: return months > obj.months;
		break;
	case Deposit::Compare_mode::Amount: return amount > obj.amount;
		break;
	case Deposit::Compare_mode::Percents: return percents > obj.percents;
		break;
	default:
		return false;
	}
}

Deposit::Deposit() : Business()
{
	amount = left_months = months = 0;
	percents = 0.0;
}

Deposit::Deposit(const Deposit& obj) : Business(obj)
{
	amount = obj.amount;
	left_months = obj.left_months;
	months = obj.months;
	percents = obj.percents;
}

Deposit::~Deposit()
{
}

istream& operator>>(istream& is, Deposit& obj)
{
	is >> dynamic_cast<Business&>(obj);
	return is;
}

ostream& operator<<(ostream& os, Deposit& obj)
{
	os << dynamic_cast<Business&>(obj);
	os << setw(15) << obj.amount << setw(15) << obj.months << setw(15)
		<< obj.percents << setw(15) << obj.left_months;
	return os;
}

ifstream& operator>>(ifstream& is, Deposit& obj)
{
	obj.first_name = obj.last_name = "";
	int flag = 0;
	obj.ID = UsmExc::correct_file_int(is, 1);
	if (obj.ID == INT_MIN) flag++;
	obj.amount = UsmExc::correct_file_double(is, 0);
	if (obj.amount == (double)INT_MIN) flag++;
	obj.months = UsmExc::correct_file_int(is, 0);
	if (obj.months == INT_MIN) flag++;
	obj.percents = UsmExc::correct_file_double(is, 0);
	if (obj.percents == (double)INT_MIN) flag++;
	obj.left_months = UsmExc::correct_file_int(is, 0);
	if (obj.left_months == INT_MIN) flag++;
	if (flag > 0 and flag < 5) {
		cout << "File (Deposits) is corrupted!\n";
		terminate();
	}
	return is;
}

ofstream& operator <<(ofstream& os, Deposit& obj)
{
	if (obj.amount)
		os << obj.ID << " " << obj.amount << " " << obj.months << " "
		<< obj.percents << " " << obj.left_months << endl;
	return os;
}