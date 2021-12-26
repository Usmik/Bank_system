#pragma once
#include "Individual.h"
#include<math.h>
#include<vector>

class Loan : public Individual
{
public:
	enum class Compare_mode
	{
		Surname, Name, Id, Monthes, Amount, Percents
	};
protected:
	static Compare_mode cmpMode;
	int monthes;
	int amount;
	int percents;
	int left_months;
	void open_loan(Interface& obj);
public:
	void monthly_fee(Interface& obj);
	void identify_loan(Interface& obj);
	void show_loan(Interface& obj);
	bool check_loan(Interface& obj);
	void pay_loan(Interface& obj);
	void close_loan(Interface& obj);
	void item_to_sort();
	Loan& item_to_find();
	int get_leftMonths();
	void change(Interface& obj);
	~Loan();
	Loan();
	Loan(const Loan& obj);
	void print();
	void set_months(int months);
	void set_amount(int amount);
	void set_percents(int percents);
	bool operator ==(const Loan& obj);
	void operator=(Loan& obj);
	bool operator <(Loan& obj);
	bool operator >(Loan& obj);
	friend istream& operator >> (istream& is, Loan& obj);
	friend ostream& operator << (ostream& os, Loan& obj);
	friend ifstream& operator >> (ifstream& is, Loan& obj);
	friend ofstream& operator << (ofstream& os, Loan& obj);
};

