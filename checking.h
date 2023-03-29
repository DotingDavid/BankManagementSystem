#ifndef CHECKING_H
#define CHECKING_H

#include <iostream>
#include "account.h"

using std::string;

class CheckingAccount:public Account {
    static int IdCounter;
    double MonthlyFee = 1.00;
public:
    CheckingAccount();
    double getMonthlyFee();
    void printAccountInfo();
    void applyInterest();
};



#endif