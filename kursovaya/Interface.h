#pragma once
#include"Account.h"
#include"Ring.cpp"
#include<fstream>
#include"UsmExc.h"
#include"Algorithm.cpp"
#include"Benefit_loan.h"
#include"Consumer_loan.h"
#include"Deposit.h"
#include<stack>

class Bank;
class Account;
class Loan;

class Interface
{
private:
	Ring<Loan> Loans;
	Ring<Bank> Clients_info;
	Ring<Account> bank_accounts;
	Ring<Deposit> Deposits;
	
	stack<string> last_operation;
	stack<Account> last_Account;
	stack<Loan> last_Loan;
	stack<Deposit> last_Deposit;
	
	friend class Bank;
	friend class Account;
	friend class Loan;
	friend class Deposit;
public:
	void MainMenu();
	void IndividualMenu();
	void BusinessMenu();
	void AccountMenu();
	void LoanMenu();
	template<typename T>
	void LoanSubMenu();
	void DepositMenu();
	void LoadAll();
	void SaveAll();
	Interface() {};
	~Interface() {};

	template<typename T>
	void change(RingIterator<T> begin, RingIterator<T> end);

	/*template<typename T>
	void apply_name_changes(int id);*/

	template<typename T>
	void cancel_last_operation();
};

