#pragma once
#include "Loan.h"
class Benefit_loan :
    public Loan
{
private:
    string benefit;
public:
    Benefit_loan();
    ~Benefit_loan();
    void take_loan(Interface& obj);
    friend istream& operator >> (istream& is, Benefit_loan& obj);
    friend ostream& operator << (ostream& os, Benefit_loan& obj);
};

