#pragma once
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string>
#include<limits.h>
#pragma comment(lib, "winmm.lib")

//void MyTerminate();
void CheckString(std::string str, int length);

class UsmExc : public std::exception
{
public:
	int ErrorCode;
	UsmExc(int c) { ErrorCode = c; };
	~UsmExc() { std::cout << "destr\n"; };

	static void ErrorCodes(int code);

	//static void correct_file(std::ifstream& fin, std::string filename);

	template<typename T>
	static T correct_number(T min = INT_MIN, T max = INT_MAX);

	static std::string correct_string(int limit_length = 80);


	static int correct_file_int(std::ifstream& is, int min = INT_MIN, int max = INT_MAX);
	
	static std::string correct_file_string(std::ifstream& is, int limit_length = 80);

	static double correct_file_double(std::ifstream& is, double min = INT_MIN, double max = INT_MAX);
};


template<typename T>
T UsmExc::correct_number(T min, T max)
{
	T res;
	while (1)
	{
		try
		{
			std::cin >> res;
			if (!std::cin.good() or std::cin.peek() != '\n')
				throw UsmExc(1);
			if (res < min)
				throw UsmExc(2);
			if (res > max)
				throw UsmExc(3);
		}
		catch (UsmExc& ex)
		{
			ErrorCodes(ex.ErrorCode);
			continue;
		}
		catch (...)
		{
			std::cout << "ERROR!" << std::endl;
			terminate();
		}
		break;
	}
	return res;
}

