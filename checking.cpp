#include <iostream>
#include <string>
#include "checking.h"

using std::cout;
using std::endl;

int CheckingAccount::IdCounter = 5000;

CheckingAccount::CheckingAccount() :Account() {
    string accountNum;
    accountNum = "C-" + std::to_string(IdCounter);
    IdCounter++;
    AccountNum = accountNum;
    setAccountType("Checking");
    MonthlyFee = 1.00;
}

double CheckingAccount::getMonthlyFee() {
    return MonthlyFee;
}

void CheckingAccount::printAccountInfo() {
    
}

void CheckingAccount::applyInterest() {
    if(AccountBalance <= 0) {
        return;
    }

    AccountBalance -= MonthlyFee;
    
    if(AccountBalance <= 0) {
        return;
    }
    else{
        double earnedInterest;
        double newAccountBalance;

        newAccountBalance = AccountBalance + (AccountBalance*getInterestRate());
        earnedInterest = newAccountBalance - AccountBalance;
        AccountBalance = newAccountBalance;
        addToEarnedInterest(earnedInterest);
    }
}