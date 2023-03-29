#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include "saving.h"
#include "maintenance.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int SavingAccount::IdCounter = 5000;

SavingAccount::SavingAccount() {
    string accountNum;
    accountNum = "S-" + std::to_string(IdCounter);
    IdCounter++;
    AccountNum = accountNum;
    setAccountType("Saving");
    setInterestRate(0.10);
    MinimumBalance = 100.00;
}

double SavingAccount::getMinimumBalance() {
    return MinimumBalance;
}

void SavingAccount::depositMoney() {
if(isClosed == false) {
    double amount;
    if(AccountBalance == 0) {
    cout << "Minimum Deposit is $100" << endl;
    cout << "Deposit Amount: $";
    amount = getValidInput(amount);
    if(checkCancel(amount)) {
        cout << "Transaction Cancelled" << endl;
        return;
    }
    while(amount < 100) {
        cout << "Minimum Deposit is $100" << endl;
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
    else {
        cout << "Deposit Amount: $";
        amount = getValidInput(amount);
        while(amount < 0) {
            cout << "Deposit must be a positive number" << endl;
            cout << "Deposit Amount: $" << endl;
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
}
else if (ClosedOutstanding == true) {
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
    else if (amount > abs(AccountBalance)) {
        cout << "Cannot deposit more than you owe" << endl;
    }
}       
else {
    cout << "Account is permanently closed, no deposit possible" << endl;
}
}

void SavingAccount::withdrawMoney() {  //No Withdraw Possible for closedOutstanding == true;
if(isClosed) {
    cout << "Account is closed, no withdraw possible" << endl;
}
if(AccountBalance <= 0) {
    cout << "Insuffiecient Funds" << endl;
    return;
}
if(isClosed == false || ClosedOutstanding == false) {
    double amount;
    cout << "Withdraw Amount: $";
    amount = getValidInput(amount);
    if(checkCancel(amount)) {
        cout << "Transaction Cancelled" << endl;
        return;
    }
        while((getAccountBalance() - amount) < MinimumBalance || amount < 0) {
            while(amount < 0) {
                cout << "Withdrawal must be a positive number" << endl;
                cout << "Withdraw Amount: $";
                getValidInput(amount);
                if(checkCancel(amount)) {
                    cout << "Transaction Cancelled" << endl;
                    return;
                }
            }
            while((getAccountBalance() - amount) < MinimumBalance) {
                cout << "Minimum Balance must be $100.00" << endl;
                cout << "Withdraw Amount: $";
                amount = getValidInput(amount);
                if(checkCancel(amount)) {
                    cout << "Transaction Cancelled" << endl;
                    return;
                }
            }
        }
    AccountBalance -= amount;
    cout << endl << "Withdrew $" << amount << " from account " << AccountNum << endl;
    cout <<"New Account Balance: $" << AccountBalance << endl;
}
if(ClosedOutstanding == true) {
    cout << "Account is closed, no withdraw possible" << endl;
}
}
