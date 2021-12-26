#pragma once
#include "Business.h"
#include"Algorithm.h"
#include<vector>

class Deposit : public Business
{
public:
	enum class Compare_mode
	{
		Surname, Name, Id, Monthes, Amount, Percents
	};
private:
	static Compare_mode cmpMode;
	double percents;
	int months;
	double amount;
	int left_months;
public:
	void set_months(int months);
	void set_amount(double amount);
	void set_percents(double percents);
	void identify_deposit(Interface& obj);
	void show_deposit(Interface& obj);
	bool deposit_check(Interface& obj);
	void make_deposit(Interface& obj);
	void take_off_deposit(Interface& obj);
	void change(Interface& obj);
	void item_to_sort();
	Deposit& item_to_find();
	void add_to_deposit(Interface& obj);
	void take_part_from_deposit(Interface& obj);
	void print();
	void skip_month(Interface& obj);
	void calculate_amount(Interface& obj);
	bool operator ==(const Deposit& obj);
	void operator=(Deposit& obj);
	bool operator <(Deposit& obj);
	bool operator >(Deposit& obj);
	friend istream& operator >> (istream& is, Deposit& obj);
	friend ostream& operator << (ostream& os, Deposit& obj);
	friend ifstream& operator >> (ifstream& is, Deposit& obj);
	friend ofstream& operator << (ofstream& os, Deposit& obj);
	Deposit();
	Deposit(const Deposit& obj);
	~Deposit();
};

