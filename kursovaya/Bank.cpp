#include "Bank.h"
#include"Interface.h"

bool Bank::operator==(const Bank& obj)
{
	if (obj.last_name.length() and obj.last_name != last_name) return false;
	if (obj.first_name.length() and obj.first_name != first_name) return false;
	if (obj.ID and obj.ID != ID) return false;
	return true;
}

void Bank::operator=(Bank& obj)
{
	this->first_name = obj.first_name;
	this->last_name = obj.last_name;
	this->ID = obj.ID;
}

void Bank::set_ID(int id)
{
	ID = id;
}

int Bank::get_ID()
{
	return ID;
}

void Bank::set_name(string name)
{
	first_name = name;
}

string Bank::get_name()
{
	return first_name;
}

void Bank::set_surname(string surname)
{
	last_name = surname;
}

string Bank::get_surname()
{
	return last_name;
}


Bank::Bank(const Bank& obj)
{
	this->last_name = obj.last_name;
	this->first_name = obj.first_name;
	this->ID = obj.ID;
}

Bank::Bank()
{
	last_name = first_name = "";
	ID = 0;
}

Bank::~Bank()
{
}

void Bank::identify_ID(Interface& intrf)
{
	if (intrf.Clients_info.is_empty()) {
		ID = 1;
		return;
	}
	if (Algorithm<Bank>::is_exist(*this, intrf.Clients_info.begin(), intrf.Clients_info.end()))
	{
		vector<Bank*> founded;
		Algorithm<Bank>::find(*this, founded, intrf.Clients_info.begin(), intrf.Clients_info.end());
		ID = (*founded[0]).ID;
	}
	else {
		ID = (*(intrf.Clients_info.begin()--)).ID + 1;
	}
}

void Bank::identify_name(Interface& intrf)
{
	Bank temp;
	temp.set_ID((*this).get_ID());
	vector<Bank*> founded;
	Algorithm<Bank>::find(temp, founded, intrf.Clients_info.begin(), intrf.Clients_info.end());
	if (!founded.empty())
		*this = *founded[0];
}

bool Bank::verification()
{
	return last_name == "Usmanov" and first_name == "Mihail";
}

void Bank::print()
{
	cout << setw(15) << "Surname" << setw(15) << "Name" << setw(5) << "ID";
}



istream& operator>>(istream& is, Bank& obj)
{
	cout << "Enter Surname = ";
	obj.last_name = UsmExc::correct_string(15);
	cout << "Enter Name = ";
	obj.first_name = UsmExc::correct_string(15);
	return is;
}

ofstream& operator<<(ofstream& ofs, Bank& obj)
{
	ofs << obj.last_name << " " << obj.first_name << " " << obj.ID << endl;
	return ofs;
}

ifstream& operator>>(ifstream& ifs, Bank& obj)
{
	int flag = 0;

	obj.last_name = UsmExc::correct_file_string(ifs, 15);
	if (obj.last_name == "") flag++;
	
	obj.first_name = UsmExc::correct_file_string(ifs, 15);
	if (obj.first_name == "") flag++;
	
	obj.ID = UsmExc::correct_file_int(ifs, 1);
	if (obj.ID == INT_MIN) flag++;
	
	if (flag > 0 and flag < 3) {
		cout << "File (Clients) was corrupted!\n";
		terminate();
	}
	return ifs;
}

ostream& operator<<(ostream& os, Bank& obj)
{
	os << setw(15) << obj.last_name << setw(15) << obj.first_name << setw(5) << obj.ID;
	return os;
}
