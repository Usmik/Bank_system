#include "Account.h"
#include"Interface.h"
#include<fstream>

Account::Compare_mode Account::cmpMode = Account::Compare_mode::Cash;

void Account::open_account(Interface& obj)
{
	vector<Account*> founded;
	Algorithm<Account>::find(*this, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	if (!founded.empty())
	{
		*this = *founded[0];
		cout << first_name << ", You already have an account\nMoney = " 
			<< this->cash_account << " " << this->currency << endl;
		return;
	}

	if (!age_check()) 
		return;
	
	cout << first_name << ", How much money you want to add on your new cash account?" << endl;
	cash_account = UsmExc::correct_number<double>(0.1, 9999999);
	
	cout << "Choose currency: 1 - BYN / 2 - USD" << endl;
	if (UsmExc::correct_number<int>(1,2) == 1)
		currency = "BYN";
	else
		currency = "USD";

	obj.bank_accounts.add(*this);
	obj.last_operation.push("add");
	obj.last_Account.push(*this);
	cout << "Your account succesfully opened" << endl;
}


void Account::delete_account(Interface& obj)
{
	if (!Algorithm<Account>::is_exist(*this, obj.bank_accounts.begin(), obj.bank_accounts.end())) {
		cout << "You don't have an account!" << endl;
		return;
	}

	cout << "You want to DELETE an account?\n [ 1 ] - Yes\n [ 2 ] - No\n" <<
		"Choice = ";
	if (UsmExc::correct_number<int>(1, 2) == 2)
		return;
	
	obj.last_operation.push("delete");
	if (obj.bank_accounts.get_head()->data == *this)
	{
		obj.bank_accounts.set_head(obj.bank_accounts.get_head()->next);
		obj.last_Account.push(obj.bank_accounts.pop());	
		return;
	}

	obj.last_Account.push(Algorithm<Account>::delete_item(*this, obj.bank_accounts.begin(), obj.bank_accounts.end()));
}


void Account::withdraw_money(Interface& obj)
{
	if (!Algorithm<Account>::is_exist(*this, obj.bank_accounts.begin(), obj.bank_accounts.end()))
	{
		cout << "You should open account before!" << endl;
		return;
	}
	show_account(obj);
	cout << "How much money you want to withdraw = ";
	vector<Account*> founded;
	Algorithm<Account>::find(*this, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	founded[0]->set_cash(cash_account - UsmExc::correct_number<double>(0, cash_account));
	*this = *founded[0];
}


void Account::put_money(Interface& obj)
{
	if (!Algorithm<Account>::is_exist(*this,obj.bank_accounts.begin(), obj.bank_accounts.end()))
	{
		cout << "You should open account before putting money!" << endl;
		return;
	}
	show_account(obj);
	cout << "How much money you want to add = ";
	vector<Account*> founded;
	Algorithm<Account>::find(*this, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	founded[0]->set_cash(cash_account + UsmExc::correct_number<double>(0));
	*this = *founded[0];
}


void Account::show_account(Interface& obj)
{
	if (Algorithm<Account>::is_exist(*this, obj.bank_accounts.begin(), obj.bank_accounts.end()))
		cout << first_name << ", Money on your account = " << cash_account << " " << currency << endl;
	else
		cout << first_name << ", You haven't an account!" << endl;
}


void Account::transfer_money(Interface& obj)
{
	if (!Algorithm<Account>::is_exist(*this, obj.bank_accounts.begin(), obj.bank_accounts.end()))
	{
		cout << "You should open account before!" << endl;
		return;
	}
	Account receiver;
	cout << "Enter Receiver Info\n";
	cin >> receiver;
	receiver.identify_ID(obj);
	receiver.identify_cash(obj);
	if (*this == receiver)
	{
		cout << "You can't transfer money to yourself\n";
		return;
	}
	if (!Algorithm<Account>::is_exist(receiver, obj.bank_accounts.begin(), obj.bank_accounts.end()))
	{
		cout << "Receiver should has an account!" << endl;
		return;
	}
	show_account(obj);
	cout << "How much money you want to transfer = ";
	double money_to_transfer = UsmExc::correct_number<double>(0, cash_account);
	vector<Account*> founded;

	Algorithm<Account>::find(*this, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	founded[0]->set_cash(cash_account - money_to_transfer);
	*this = *founded[0];

	if (currency < receiver.currency) money_to_transfer /= Dollar_Rate;
	else if(currency > receiver.currency) money_to_transfer *= Dollar_Rate;

	Algorithm<Account>::find(receiver, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	founded[1]->set_cash(founded[1]->cash_account + money_to_transfer);
}

Account::~Account()
{
}


Account::Account() : Individual()
{
	cash_account = 0;
	currency = "";
}


Account::Account(const Account& obj) : Individual(obj)
{
	this->cash_account = obj.cash_account;
	this->currency = obj.currency;
}

void Account::identify_cash(Interface& obj)
{
	Account temp;
	temp.set_ID(this->get_ID());
	vector<Account*> founded;
	Algorithm<Account>::find(temp, founded, obj.bank_accounts.begin(), obj.bank_accounts.end());
	if (!founded.empty())
		*this = *founded[0];
	this->identify_name(obj);
}


void Account::item_to_sort()
{
	cout << "By which field do you want to sort:\n [ 1 ] - Surname\n [ 2 ] - Name" <<
		"\n [ 3 ] - ID\n [ 4 ] - cash\n";
	cout << "Choose: ";
	switch (UsmExc::correct_number<int>(1,4))
	{
	case 1: cmpMode = Compare_mode::Surname; break;
	case 2: cmpMode = Compare_mode::Name; break;
	case 3: cmpMode = Compare_mode::Id; break;
	case 4: cmpMode = Compare_mode::Cash; break;
	}
}

Account& Account::item_to_find()
{
	int choose = 0;
	cout << "Fields:\n [ 1 ] - Surname\n [ 2 ] - Name\n [ 3 ] - ID\n [ 4 ] - Cash\n";
	do {
		cout << "Choose by which fields we will search (input 0 to end) = ";
		choose = UsmExc::correct_number(0, 4);
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
			cout << "Enter Cash to search = ";
			set_cash(UsmExc::correct_number<double>(1));
		}break;
		default:
			break;
		}
	} while (choose != 0);
	return *this;
}


void Account::print()
{
	dynamic_cast<Individual&>(*this).print();
	cout << setw(10) << "Cash" << setw(10) << "Currency";
}

void Account::change(Interface& obj)
{	
	obj.last_Account.push(*this);
	obj.last_operation.push("change");
	cout << "We change:\n [ 1 ] - Surname \t [ 4 ] - Back\n [ 2 ] - Name\n [ 3 ] - Cash\nChoice: ";
	switch (UsmExc::correct_number<int>(1, 4))
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
		cout << "Enter new Cash: ";
		set_cash(UsmExc::correct_number<double>(0.1));
	}break;
	default:
		return;
		break;
	}
}


void Account::set_cash(double new_cash)
{
	cash_account = new_cash;
}

double Account::get_cash()
{
	return cash_account;
}

void Account::set_currency(string curr)
{
	currency = curr;
}

string Account::get_currency()
{
	return currency;
}


bool Account::operator==(const Account& obj)
{
	if (!(dynamic_cast<Bank&>(*this) == obj)) return false;
	if (obj.cash_account and obj.cash_account != cash_account) return false;
	if (obj.currency.length() and obj.currency != currency) return false;
	return true;
}


void Account::operator=(Account& obj)
{
	dynamic_cast<Individual&>(*this) = obj;
	this->cash_account = obj.cash_account;
	this->currency = obj.currency;
}


bool Account::operator<(Account& obj)
{
	switch (cmpMode)
	{
	case Account::Compare_mode::Name: return first_name < obj.first_name;
		break;
	case Account::Compare_mode::Surname: return last_name < obj.last_name;
		break;
	case Account::Compare_mode::Id: return ID < obj.ID;
		break;
	case Account::Compare_mode::Cash: return cash_account < obj.cash_account;
		break;
	default:
		return false;
	}
}


bool Account::operator>(Account& obj)
{
	switch (cmpMode)
	{
	case Account::Compare_mode::Name: return first_name > obj.first_name;
		break;
	case Account::Compare_mode::Surname: return last_name > obj.last_name;
		break;
	case Account::Compare_mode::Id: return ID > obj.ID;
		break;
	case Account::Compare_mode::Cash: return cash_account > obj.cash_account;
		break;
	default:
		return false;
	}
}

istream& operator>>(istream& is, Account& obj)
{
	is >> dynamic_cast<Individual&>(obj);
	return is;
}

ostream& operator<<(ostream& os, Account& obj)
{
	os << dynamic_cast<Individual&>(obj);
	os << setw(10) << obj.cash_account << setw(10) << obj.currency;
	return os;
}

ifstream& operator>>(ifstream& is, Account& obj)
{
	int flag = 0;
	obj.first_name = obj.last_name = "";

	obj.ID = UsmExc::correct_file_int(is, 1);
	if (obj.ID == INT_MIN) flag++;

	obj.cash_account = UsmExc::correct_file_double(is, 0);
	if (obj.cash_account == (double)INT_MIN) flag++;

	obj.currency = UsmExc::correct_file_string(is, 3);
	if (obj.currency == "") flag++;

	if (flag > 0 and flag < 3) {
		cout << "File (Accounts) was corrupted!!\n";
		terminate();
	}
	return is;
}

ofstream& operator <<(ofstream& os, Account& obj)
{
	if(obj.cash_account)
	os << obj.ID << " " << obj.cash_account << " " << obj.currency << endl;
	return os;
}