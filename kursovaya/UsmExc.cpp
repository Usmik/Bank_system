#include "UsmExc.h"

void CheckInt(std::string str)
{
	std::string nums = "0123456789";
	for (int i = 0; unsigned(i) < str.length(); i++)
		if (nums.find(str[i]) == std::string::npos)
			throw UsmExc(7);
}

void CheckDouble(std::string str)
{
	std::string nums = "0123456789.";
	for (int i = 0; unsigned(i) < str.length(); i++)
		if (nums.find(str[i]) == std::string::npos)
			throw UsmExc(7);
}

void CheckString(std::string str, int length)
{
	std::string nums = "0123456789";
	for (int i = 0; unsigned(i) < nums.length(); i++)
		if (str.find(nums[i]) != std::string::npos)
			throw UsmExc(4);

	for (int i = 0; unsigned(i) < str.length(); i++)
		if (str[i] < 'A' or str[i] > 'Z' and str[i] < 'a' or str[i] > 'z')
			throw UsmExc(5);

	if (str.length() > unsigned(length))
		throw UsmExc(6);
}

void UsmExc::ErrorCodes(int code)
{
	if (code >= 1 and code <= 3)
		PlaySound(TEXT("interror.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (code >= 4 and code <= 6)
		PlaySound(TEXT("stringerror.wav"), NULL, SND_FILENAME | SND_ASYNC);
	switch (code)
	{
	case 1: std::cout << "Input error\nEntered number, contains letters or punctuations\nTry again\n"; break;
	case 2: std::cout << "Input error\nEntered number less then limit\nTry again\n"; break;
	case 3: std::cout << "Input error\nEntered number more then limit\nTry again\n"; break;
	case 4: std::cout << "Input error\nEntered string contains a digits\nTry again\n"; break;
	case 5: std::cout << "Input error\nEntered string must contain only Latin letters\nTry again\n"; break;
	case 6: std::cout << "Input error\nEntered string exceeds the limits\nTry again\n"; break;
	default:
		break;
	}
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

//void UsmExc::correct_file(std::ifstream& fin, std::string filename)
//{
//	fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//	try
//	{
//		fin.open(filename);
//	}
//	catch (const std::ifstream::failure& ex)
//	{
//		std::cout << "Opening file error\n";
//		std::cout << ex.code();
//		std::terminate();
//	}
//}

std::string UsmExc::correct_string(int limit_length)
{
	std::string res;
	while (1)
	{
		try
		{
			std::cin >> res;
			CheckString(res, limit_length);
		}
		catch (UsmExc& ex)
		{
			ErrorCodes(ex.ErrorCode);
			continue;
		}
		break;
	}
	return res;
}

std::string UsmExc::correct_file_string(std::ifstream& is, int limit_length)
{
	std::string res = "";
	try
	{
		if (is >> res)
			CheckString(res, limit_length);
	}
	catch (...)
	{
		std::cout << "File was corrupted!!\n";
		terminate();
	}
	return res;
}

int UsmExc::correct_file_int(std::ifstream& is, int min, int max)
{
	std::string tmp = "";
	int res = INT_MIN;
	try
	{
		if (is >> tmp)
		{
			CheckInt(tmp);
			res = std::stoi(tmp);
			if (!is.good() or is.peek() != '\n' and is.peek() != ' ')
				throw 1;
			else if (res < min)
				throw 2;
			else if (res > max)
				throw 3;
		}
		else
			return INT_MIN;
	}
	catch (...)
	{
		std::cout << "File was corrupted!\n";
		terminate();
	}
	return res;
}

double UsmExc::correct_file_double(std::ifstream& is, double min, double max)
{
	std::string tmp = "";
	double res = (double)INT_MIN;
	try
	{
		if (is >> tmp)
		{
			CheckDouble(tmp);
			res = std::stod(tmp);
			if (!is.good() or is.peek() != '\n' and is.peek() != ' ')
				throw 1;
			else if (res < min)
				throw 2;
			else if (res > max)
				throw 3;
		}
		else
			return (double)INT_MIN;
	}
	catch (...)
	{
		std::cout << "File was corrupted!\n";
		terminate();
	}
	return res;
}