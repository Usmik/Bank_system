#pragma once
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include"UsmExc.h"

using namespace std;


class Interface;

class Bank
{
protected:
	string last_name;
	string first_name;
	int ID;
public:
	Bank(const Bank& obj);
	Bank();
	virtual ~Bank();
	void identify_ID(Interface& intrf);
	void identify_name(Interface& intrf);
	bool verification();
	void print();
	bool operator==(const Bank& obj);
	void operator=(Bank& obj);
	void set_ID(int id);
	int get_ID();
	void set_name(string name);
	string get_name();
	void set_surname(string surname);
	string get_surname();
	friend istream& operator >> (istream& is, Bank& obj);
	friend ostream& operator << (ostream& os, Bank& obj);
	friend ofstream& operator << (ofstream& ofs, Bank& obj);
	friend ifstream& operator >> (ifstream& ifs, Bank& obj);
};

