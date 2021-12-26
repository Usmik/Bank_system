#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class File_txt
{
private:
	string file_name;
	ifstream is;
	ofstream os;
public:
	File_txt(string name);
	~File_txt();
	bool open_to_write();
	bool open_to_read();
	void remote();
	
	template<typename T>
	bool read_element_from_file(T& obj);

	template<typename T>
	bool wrire_element_in_file(T& obj);
};

template<typename T>
inline bool File_txt::read_element_from_file(T& obj)
{
	if (is >> obj)
		return true;
	else
		return false;
}

template<typename T>
inline bool File_txt::wrire_element_in_file(T& obj)
{
	if (os << obj)
		return true;
	else
		return false;
}
