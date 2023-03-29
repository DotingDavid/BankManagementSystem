#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>

using std::string;

class Account {
    string AccountType;
    double InterestRate;
    std::vector<double> MonthlyEarnedInterest;
protected:
    bool isClosed;
    bool ClosedOutstanding;
    string AccountNum;
    double AccountBalance;
public:
    Account();
    virtual void depositMoney();
    virtual void withdrawMoney();
    double getAccountBalance();
    void checkAccountBalance();
    void setAccountType(string accountType);
    string getAccountType();
    string getAccountNum();
    double getInterestRate();
    void setInterestRate(double newInterestRate);
    void addToEarnedInterest(double earnedInterest);
    double earnedInterest(); //sum all values from vector //adding to vector happens with applyInterest() from bank
    virtual void applyInterest();
    void closeAccount();
    string getAccountStatus();
    void printAccountInfo(int accountNum_width, int accountType_width, int accountBal_width, int accountStatus_width, int earnedInterest_width, int total_width); //Table like format
};

#endif