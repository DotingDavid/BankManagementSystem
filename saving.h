#ifndef SAVING_H
#define SAVING_H

#include <iostream>
#include "account.h"

using std::string;

class SavingAccount:public Account {
    static int IdCounter;
    double MinimumBalance = 100.00;
public:
    SavingAccount();
    double getMinimumBalance();
    void depositMoney();
    void withdrawMoney();
};



#endif