#pragma once
#include "Loan.h"
class Consumer_loan :
    public Loan
{
private:
    string aim_of_loan;
public:
    Consumer_loan();
    ~Consumer_loan();
    void take_loan(Interface& obj);
    friend istream& operator >> (istream& is, Consumer_loan& obj);
    friend ostream& operator << (ostream& os, Consumer_loan& obj);
};

