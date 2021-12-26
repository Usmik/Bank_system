#include "Interface.h"
#include<typeinfo>
#include<vector>
#include"File_txt.h"

void Interface::MainMenu()
{
	cout << "Welcome to USM Bank" << endl;
	cout << "Menu:\n [ 1 ] - Open system\n [ 2 ] - Create new system\nChoose: ";
	if (UsmExc::correct_number<int>(1,2) == 1)
		LoadAll();
	system("CLS");
	cout << "You come to our company as a:\n [ 1 ] - Individual\t[ 3 ] - EXIT\n [ 2 ] - Business\nChoose: ";
	switch (UsmExc::correct_number<int>(1,3))
	{
	case 1: IndividualMenu(); break;
	case 2: BusinessMenu(); break;
	case 3:
		break;
	}
	cout << "Do you want to Save ALL information?\n [ 1 ] - Yes\n [ 2 ] - No\nAnswer = ";
	if (UsmExc::correct_number<int>(1, 2) == 1)
		SaveAll();
}

void Interface::IndividualMenu()
{
	while (1)
	{	
		RingIterator<Account> it1 = bank_accounts.begin();
		RingIterator<Account> end1 = bank_accounts.end();
		if (!(it1 == nullptr))
		{
			do {
				(*it1).identify_cash(*this);
				it1++;
			} while (it1 != end1);
		}
		RingIterator<Loan> it2 = Loans.begin();
		RingIterator<Loan> end2 = Loans.end();
		if (!(it2 == nullptr))
		{
			do {
				(*it2).identify_loan(*this);
				it2++;
			} while (it2 != end2);
		}
		system("CLS");
		cout << "Work with:\n [ 1 ] - Account\t [ 3 ] - Back to Main Menu\n [ 2 ] - Loan\nChoose: ";
		switch (UsmExc::correct_number<int>(1,3))
		{
		case 1: AccountMenu(); break;
		case 2: LoanMenu(); break;
		case 3: return;
		}
	}
}

void Interface::BusinessMenu()
{
	while (1)
	{
		system("CLS");
		cout << "Work with:\n [ 1 ] - Deposit\t [ 2 ] - Back to Main Menu\nChoose: ";
		switch (UsmExc::correct_number<int>(1, 2))
		{
		case 1: DepositMenu(); break;
		case 2: return;
		}
	}
}

void Interface::AccountMenu()
{
	system("CLS");
	Account person;
	cin >> person;
	person.identify_ID(*this);
	person.identify_cash(*this);
	if (!Algorithm<Bank>::is_exist(person, Clients_info.begin(), Clients_info.end()))
		Clients_info.add(person);
	while (1)
	{
		person.identify_cash(*this);
		cout << "\n [ 1 ] - Show Account\t[ 8 ] - BACK\n [ 2 ] - Open Account\n [ 3 ] - Delete Account\n [ 4 ] - Put money\n" <<
			" [ 5 ] - Withdraw money\n [ 6 ] - Transfer money\n [ 7 ] - Cancel last operation\n";
		int choice;
		if (person.verification())
		{
			cout << "Admin :: [ -3 ] - Find account\nAdmin :: [ -2 ] - Change account\nAdmin :: [ -1 ] - Sort accounts\n"
				<<"Admin ::[0] - Show accounts\nChoice: ";
			choice = UsmExc::correct_number<int>(-3, 8);
		}
		else {
			cout << "Choice: ";
			choice = UsmExc::correct_number<int>(1, 8);
		}
		system("CLS");
		switch (choice)
		{
		case -3: {
			if (bank_accounts.is_empty()) break;
			Account temp;
			vector<Account*> founded;
			Algorithm<Account>::find(temp.item_to_find(), founded, bank_accounts.begin(), bank_accounts.end());
			if (!founded.empty())
				founded[0]->print();
			cout << "\n";
			for (Account* i : founded)
				cout << *i << endl;
		} break;
		case -2:bank_accounts.show();
			change(bank_accounts.begin(), bank_accounts.end());
			break;
		case -1: {
			Account temp;
			temp.item_to_sort();
			Algorithm<Account>::sort(bank_accounts.begin(), bank_accounts.end());
		}break;
		case 0: {
			cout << "Accounts:\n";
			bank_accounts.show();
			cout << "\nClients:\n";
			Clients_info.show();
		} break;
		case 1: person.show_account(*this); break;
		case 2: person.open_account(*this); break;
		case 3: person.delete_account(*this); break;
		case 4: person.put_money(*this); break;
		case 5: person.withdraw_money(*this); break;
		case 6: person.transfer_money(*this); break;
		case 7: cancel_last_operation<Account>(); break;
		default:
		{
			while (!last_Account.empty())
			{
				last_Account.pop();
				last_operation.pop();
			}
			return;
		}
		break;
		}
	}
}

void Interface::LoanMenu()
{
	while (1)
	{
		system("CLS");
		cout << "Work with:\n [ 1 ] - Benefit Loan\t [ 3 ] - Back\n [ 2 ] - Consumer Loan\nChoose: ";
		switch (UsmExc::correct_number<int>(1, 3))
		{
		case 1: LoanSubMenu<Benefit_loan>(); break;
		case 2: LoanSubMenu<Consumer_loan>(); break;
		case 3: return;
		}
	}
}


template<typename T>
void Interface::LoanSubMenu()
{
	T person;
	cin >> person;
	person.identify_ID(*this);
	person.identify_loan(*this);
	if (!Algorithm<Bank>::is_exist(person, Clients_info.begin(), Clients_info.end()))
		Clients_info.add(person);
	while (1)
	{
		person.identify_loan(*this);
		cout << "\n [ 1 ] - Show loan\t[ 7 ] - BACK\n [ 2 ] - Take loan\n [ 3 ] - Close loan\n [ 4 ] - Pay for loan\n" <<
			" [ 5 ] - Calculate monthly fee\n [ 6 ] - Cancel last operation\n";
		int choice;
		if (person.verification())
		{
			cout << "Admin :: [ -3 ] - Find loan\nAdmin :: [ -2 ] - Change loan\nAdmin :: [ -1 ] - Sort loans\nAdmin :: [ 0 ] - Show loans\nChoice: ";
			choice = UsmExc::correct_number<int>(-3, 7);
		}
		else {
			cout << "Choice: ";
			choice = UsmExc::correct_number<int>(1, 7);
		}
		system("CLS");
		switch (choice)
		{
		case -3: {
			if (Loans.is_empty()) break;
			Loan temp;
			vector<Loan*> founded;
			Algorithm<Loan>::find(temp.item_to_find(), founded, Loans.begin(), Loans.end());
			if (!founded.empty())
				founded[0]->print();
			cout << "\n";
			for (Loan* i : founded)
				cout << *i << endl;
		}break;
		case -2: {
			Loans.show();
			change(Loans.begin(), Loans.end());
		} break;
		case -1: {
			Benefit_loan temp;
			temp.item_to_sort();
			Algorithm<Loan>::sort(Loans.begin(), Loans.end());
		}break;
		case 0: {
			cout << "Loans:\n";
			Loans.show();
			cout << "\nClients:\n";
			Clients_info.show();
		} break;
		case 1: person.show_loan(*this); break;
		case 2: person.take_loan(*this); break;
		case 3: person.close_loan(*this); break;
		case 4: person.pay_loan(*this); break;
		case 5: person.monthly_fee(*this); break;
		case 6: cancel_last_operation<Loan>(); break;
		default:
		{
			while (!last_Loan.empty())
			{
				last_Loan.pop();
				last_operation.pop();
			} 
			return; 
			break;
		}
		}
	}
}

template<typename T>
void Interface::cancel_last_operation()
{
	if (last_operation.empty())
	{
		cout << "You can't cancel last operation!\n";
		return;
	}
	string tmp(typeid(T).name());
	if (tmp.find("Account") != string::npos)
	{
		if (last_operation.top() == "delete")
		{
			Account check;
			check.set_ID(last_Account.top().get_ID());
			if (!Algorithm<Account>::is_exist(check, bank_accounts.begin(), bank_accounts.end()))
				bank_accounts.add(last_Account.top());
			last_operation.pop();
			last_Account.pop();
		}
		else if (last_operation.top() == "add")
		{
			if (last_Account.top() == bank_accounts.get_head()->data)
			{
				bank_accounts.set_head(bank_accounts.get_head()->next);
				bank_accounts.pop();
			}
			else
				Algorithm<Account>::delete_item(last_Account.top(), bank_accounts.begin(), bank_accounts.end());
			last_operation.pop();
			last_Account.pop();
		}
		else if (last_operation.top() == "change")
		{
			Account temp_acc;
			temp_acc.set_ID(last_Account.top().get_ID());
			vector<Account*> accounts;
			vector<Bank*> banks;
			Algorithm<Account>::find(temp_acc, accounts, bank_accounts.begin(), bank_accounts.end());
			Algorithm<Bank>::find(temp_acc, banks, Clients_info.begin(), Clients_info.end());
			*accounts[0] = last_Account.top();
			*banks[0] = last_Account.top();
			last_operation.pop();
			last_Account.pop();
		}
	}
	else if (tmp.find("Loan") != string::npos)
	{
		if (last_operation.top() == "delete")
		{
			Loan check_loan;
			check_loan.set_ID(last_Loan.top().get_ID());
			if (last_Loan.top().get_leftMonths() != 0 and
				!Algorithm<Loan>::is_exist(check_loan, Loans.begin(), Loans.end()))
				Loans.add(last_Loan.top());
			last_operation.pop();
			last_Loan.pop();
		}
		else if (last_operation.top() == "add")
		{
			if (last_Loan.top() == Loans.get_head()->data)
			{
				Loans.set_head(Loans.get_head()->next);
				Loans.pop();
			}
			else
				Algorithm<Loan>::delete_item(last_Loan.top(), Loans.begin(), Loans.end());
			last_operation.pop();
			last_Loan.pop();
		}
		else if (last_operation.top() == "change")
		{
			Loan temp_loan;
			temp_loan.set_ID(last_Loan.top().get_ID());
			vector<Loan*> loans;
			vector<Bank*> banks;
			Algorithm<Loan>::find(temp_loan, loans, Loans.begin(), Loans.end());
			Algorithm<Bank>::find(temp_loan, banks, Clients_info.begin(), Clients_info.end());
			*loans[0] = last_Loan.top();
			*banks[0] = last_Loan.top();
			last_operation.pop();
			last_Loan.pop();
		}
	}
	else if (tmp.find("Deposit") != string::npos)
	{
		if (last_operation.top() == "delete")
		{
			Deposit check_dep;
			check_dep.set_ID(last_Deposit.top().get_ID());
			if (!Algorithm<Deposit>::is_exist(check_dep, Deposits.begin(), Deposits.end()))
				Deposits.add(last_Deposit.top());
			last_operation.pop();
			last_Deposit.pop();
		}
		else if (last_operation.top() == "add")
		{
			if (last_Deposit.top() == Deposits.get_head()->data)
			{
				Deposits.set_head(Deposits.get_head()->next);
				Deposits.pop();
			}
			else
				Algorithm<Deposit>::delete_item(last_Deposit.top(), Deposits.begin(), Deposits.end());
			last_operation.pop();
			last_Deposit.pop();
		}
		else if (last_operation.top() == "change")
		{
			Deposit temp_deposit;
			temp_deposit.set_ID(last_Deposit.top().get_ID());
			vector<Deposit*> deposits;
			vector<Bank*> banks;
			Algorithm<Deposit>::find(temp_deposit, deposits, Deposits.begin(), Deposits.end());
			Algorithm<Bank>::find(temp_deposit, banks, Clients_info.begin(), Clients_info.end());
			*deposits[0] = last_Deposit.top();
			*banks[0] = last_Deposit.top();
			last_operation.pop();
			last_Deposit.pop();
		}
	}
}

void Interface::DepositMenu()
{
	system("CLS");
	Deposit person;
	cin >> person;
	person.identify_ID(*this);
	person.identify_deposit(*this);
	if (!Algorithm<Bank>::is_exist(person, Clients_info.begin(), Clients_info.end()))
		Clients_info.add(person);
	while (1)
	{
		person.identify_deposit(*this);
		cout << "\n [ 1 ] - Show deposit\t[ 8 ] - BACK\n [ 2 ] - Make deposit\n [ 3 ] - Take off deposit\n" <<
			" [ 4 ] - Add money to deposit\n" <<
			" [ 5 ] - Take a part of deposit\n [ 6 ] - Calculate final cash\n [ 7 ] - Cancel last operation\n";
		int choice;
		if (person.verification())
		{
			cout << "Admin :: [ -4 ] - Find deposits\nAdmin :: [ -3 ] - Skip month\nAdmin :: [ -2 ] - Change deposit\n" <<
				"Admin ::[ -1 ] - Sort deposits\nAdmin ::[ 0 ] - Show deposits\nChoice: ";
			choice = UsmExc::correct_number<int>(-4, 8);
		}
		else {
			cout << "Choice: ";
			choice = UsmExc::correct_number<int>(1, 8);
		}
		system("CLS");
		switch (choice)
		{
		case -4: {
			if (Deposits.is_empty()) break;
			Deposit temp;
			vector<Deposit*> founded;
			Algorithm<Deposit>::find(temp.item_to_find(), founded, Deposits.begin(), Deposits.end());
			if (!founded.empty())
				founded[0]->print();
			cout << "\n";
			for (Deposit* i : founded)
				cout << *i << endl;
		}break;
		case -3: person.skip_month(*this); break;
		case -2:Deposits.show();
			change(Deposits.begin(), Deposits.end());
			break;
		case -1: {
			if (Deposits.is_empty()) break;
			Deposit temp_dep;
			temp_dep.item_to_sort();
			Algorithm<Deposit>::sort(Deposits.begin(), Deposits.end());
		}break;
		case 0: {
			cout << "Deposits:\n";
			Deposits.show();
			cout << "\nClients:\n";
			Clients_info.show();
		} break;
		case 1: person.show_deposit(*this); break;
		case 2: person.make_deposit(*this); break;
		case 3: person.take_off_deposit(*this); break;
		case 4: person.add_to_deposit(*this); break;
		case 5: person.take_part_from_deposit(*this); break;
		case 6: person.calculate_amount(*this); break;
		case 7: cancel_last_operation<Deposit>(); break;
		default:
		{
			while (!last_Deposit.empty())
			{
				last_Deposit.pop();
				last_operation.pop();
			}
			return;
		}
		break;
		}
	}
}

void Interface::LoadAll()
{

	File_txt f1("clients.txt");
	if (f1.open_to_read())
	{
		f1.remote();
		Bank temp1;
		while (f1.read_element_from_file<Bank>(temp1))
			Clients_info.add(temp1);
	}
	else
		return;
	
	File_txt f2("accounts.txt");
	if (f2.open_to_read())
	{
		f2.remote();
		Account temp2;
		while (f2.read_element_from_file<Account>(temp2))
		{
			temp2.identify_name(*this);
			bank_accounts.add(temp2);
		}
	}

	File_txt f3("loans.txt");
	if (f3.open_to_read())
	{
		f3.remote();
		Loan temp3;
		while (f3.read_element_from_file<Loan>(temp3))
		{
			temp3.identify_name(*this);
			Loans.add(temp3);
		}
	}
	
	File_txt f4("deposits.txt");
	if (f4.open_to_read())
	{
		f4.remote();
		Deposit temp4;
		while (f4.read_element_from_file<Deposit>(temp4))
		{
			temp4.identify_name(*this);
			Deposits.add(temp4);
		}
	}
}

void Interface::SaveAll()
{

	File_txt f1("clients.txt");
	if (f1.open_to_write())
	{
		if (!Clients_info.is_empty())
		{
			RingIterator<Bank> it = Clients_info.begin();
			RingIterator<Bank> end = Clients_info.end();
			do {
				f1.wrire_element_in_file<Bank>(*it);
				it++;
			} while (it != end);
		}
	}
	
	File_txt f2("accounts.txt");
	if (f2.open_to_write())
	{
		if (!bank_accounts.is_empty())
		{
			RingIterator<Account> it = bank_accounts.begin();
			RingIterator<Account> end = bank_accounts.end();
			do {
				f2.wrire_element_in_file<Account>(*it);
				it++;
			} while (it != end);
		}
	}

	

	File_txt f3("loans.txt");
	if (f3.open_to_write())	{
		if (!Loans.is_empty()) {
			RingIterator<Loan> it = Loans.begin();
			RingIterator<Loan> end = Loans.end();
			do {
				f3.wrire_element_in_file<Loan>(*it);
				it++;
			} while (it != end);
		}
	}

	
	File_txt f4("deposits.txt");
	if (f4.open_to_write()) {
		if (!Deposits.is_empty()) {
			RingIterator<Deposit> it = Deposits.begin();
			RingIterator<Deposit> end = Deposits.end();
			do {
				f4.wrire_element_in_file<Deposit>(*it);
				it++;
			} while (it != end);
		}
	}
}

template<typename T>
void Interface::change(RingIterator<T> begin, RingIterator<T> end)
{
	if (begin == nullptr)
		return;
	std::cout << "In which class do you want to make changes?\nChoice = ";
	int k = UsmExc::correct_number<int>(1);
	while (--k)
		begin++;
	(*begin).change(*this);
	
	Bank temp;
	temp.set_ID((*begin).get_ID());
	vector<Bank*> founded;
	Algorithm<Bank>::find(temp, founded, Clients_info.begin(), Clients_info.end());
	*founded[0] = *begin;

}
