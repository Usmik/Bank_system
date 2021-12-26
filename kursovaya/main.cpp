#include"Account.h"
#include"Loan.h"
#include"Deposit.h"
#include"Interface.h"
#include<fstream>
#include<Windows.h>


int main()
{
	system("color 5F");
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, nullptr);
	Interface UsmanBankSystem;
	UsmanBankSystem.MainMenu();
	return 0;
}