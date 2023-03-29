#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <cmath>
#include "account.h"
#include "maintenance.h"

using std::cout;
using std::cin;
using std::endl;

Account::Account() {
    AccountBalance = 0;
    InterestRate = 0.05;
    isClosed = false;
    ClosedOutstanding = false;
}

void Account::depositMoney() {
if(isClosed == false && ClosedOutstanding == false) {
    double amount;
    cout << "Deposit Amount: $";
    amount = getValidInput(amount);
    if(checkCancel(amount)) {
        cout << "Transaction Cancelled" << endl;
        return;
    }
    while(amount < 0) {
        cout << "Deposit must be a positive number" << endl;
        cout << "Deposit Amount: $";
        amount = getValidInput(amount);
        if(checkCancel(amount)) {
            cout << "Transaction Cancelled" << endl;
            return;
        }
    }
    AccountBalance += amount;
    cout << endl << "Deposited $" << amount << " into account " << AccountNum << endl;
    cout << "New Account Balance: $" << AccountBalance << endl;
}
else if(ClosedOutstanding == true) {
    double amount;
    cout << "Account is closed but has an outstanding balance" << endl;
    cout << "Current Balance: $" << AccountBalance << endl;
    cout << "Deposit Amount: $";
    amount = getValidInput(amount);
    if(checkCancel(amount)) {
        cout << "Transaction Cancelled" << endl;
        return;
    }

    while(amount < 0) {
        cout << "Deposit must be a positive number" << endl;
        cout << "Deposit Amount: $";
        amount = getValidInput(amount);
        if(checkCancel(amount)) {
            cout << "Transaction Cancelled" << endl;
            return;
        }
    }
    if(amount <= abs(AccountBalance)) {
        AccountBalance += amount;
        cout << endl << "Deposited $" << amount << " into account " << AccountNum << endl;
        cout << "New Account Balance: $" << AccountBalance << endl;
        if(AccountBalance == 0) {
            ClosedOutstanding = false;
            isClosed = true;
            cout << "Account " << AccountNum << " has been fully closed" << endl;
        } 
    }
    else if(amount > abs(AccountBalance)) {
        cout << "Cannot deposit more than you owe" << endl;
    }
}
else {
    cout << "Account is permananetly closed, no deposit possible" << endl;
}
}

void Account::withdrawMoney() {
    if(AccountBalance <= 0) {
        cout << "Insufficient Funds" << endl;
        return;
    }
    if(isClosed == false && ClosedOutstanding == false) {
        if(AccountBalance <= 0) {
            cout << "Insufficient Funds" << endl;
            return;
        }
        double amount;
        cout << "Withdrawal Amount: $";
        amount = getValidInput(amount);
        if(checkCancel(amount)) {
            cout << "Transaction Cancelled" << endl;
            return;
        }
        while(amount < 0) {
            cout << "Withdrawal must be a positive number" << endl;
            cout << "Withdrawal Amount: $";
            amount = getValidInput(amount);
            if(checkCancel(amount)) {
                cout << "Transaction Cancelled" << endl;
                return;
            }
        }
        AccountBalance -= amount;
        cout << endl << "Withdrew $" << amount << " out of account " << AccountNum << endl;    
        cout << "New Account Balance: $" << AccountBalance << endl;
    }
    else {
        cout << "Account is closed, no withdrawal possible" << endl;
    }

}

double Account::getAccountBalance() {
    return AccountBalance;
}

void Account::checkAccountBalance() {
    cout << "$" << AccountBalance << endl;
}

void Account::setAccountType(string accountType) {
    AccountType = accountType;
}

string Account::getAccountType() {
    return AccountType;
}

string Account::getAccountNum() {
    return AccountNum;
}

double Account::getInterestRate() {
    return InterestRate;
}

double Account::earnedInterest() {
    double earnedInterest = 0;
    for(int month : MonthlyEarnedInterest) {
        earnedInterest += month;
    }
    return earnedInterest;
}

void Account::applyInterest() {
    if(AccountBalance < 0) {
        //cout << "Account Balance is negative, no interest applied." << endl;
        return;
    }
    
    double earnedInterest = 0;
    double newAccountBalance = 0;

    newAccountBalance = AccountBalance + (AccountBalance*InterestRate);
    earnedInterest = newAccountBalance - AccountBalance;
    AccountBalance = newAccountBalance;
    MonthlyEarnedInterest.push_back(earnedInterest);
    
}

void Account::printAccountInfo(int accountNum_width, int accountType_width, int accountBal_width, int accountStatus_width, int earnedInterest_width, int total_width) {
    string earnedInterestString = std::to_string(earnedInterest());
    string accountBal = std::to_string(AccountBalance);
    std::cout << std::left << std::setw(accountNum_width) << "| " + AccountNum
            << std::setw(accountType_width) << "| " + AccountType
            << std::setw(accountBal_width) << "| " + accountBal
            << std::setw(accountStatus_width) << "| " + getAccountStatus()
            << std::setw(earnedInterest_width) << "| " + earnedInterestString << "|" << std::endl;
    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
}

void Account::setInterestRate(double newInterestRate) {
    InterestRate = newInterestRate;
}

void Account::addToEarnedInterest(double earnedInterest) {
    MonthlyEarnedInterest.push_back(earnedInterest);
}

string Account::getAccountStatus() {
    if(isClosed == false && ClosedOutstanding == false)
        return "Open";
    if(ClosedOutstanding == true)
        return "Outstanding";
    if(isClosed == true && ClosedOutstanding == false)
        return "Closed";
    return "N/A";
}

void Account::closeAccount() {
    if(AccountBalance > 0) {
        cout << "Account Balance: " << AccountBalance << endl;
        cout << "Withdraw Amount: " << AccountBalance << endl;
        AccountBalance = 0;
    }
    if(AccountBalance == 0) {
        isClosed = true;
        ClosedOutstanding = false;
    }
    else if(AccountBalance < 0) {
        isClosed = true;
        ClosedOutstanding = true;
    }
}