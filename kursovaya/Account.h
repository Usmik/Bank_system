#pragma once
#include "Individual.h"
#include<stack>
const double Dollar_Rate = 2.55;

class Account : public Individual
{
protected:
	double cash_account;
	string currency;
public:
	enum class Compare_mode {
		Name, Surname, Id, Cash
	};
	void open_account(Interface& obj);
	void delete_account(Interface& obj);
	void withdraw_money(Interface& obj);
	void put_money(Interface& obj);
	void show_account(Interface& obj);
	void transfer_money(Interface& obj);
	~Account();
	Account();
	Account(const Account& obj);
	void identify_cash(Interface& obj);
	void item_to_sort();
	Account& item_to_find();
	void print();
	void change(Interface& obj);
	void set_cash(double new_cash);
	double get_cash();
	void set_currency(string curr);
	string get_currency();
	bool operator ==(const Account& obj);
	void operator=(Account& obj);
	bool operator <(Account& obj);
	bool operator >(Account& obj);
	friend istream& operator >> (istream& is, Account& obj);
	friend ostream& operator << (ostream& os, Account& obj);
	friend ifstream& operator >> (ifstream& is, Account& obj);
	friend ofstream& operator << (ofstream& os, Account& obj);
private:
	static Compare_mode cmpMode;
};
