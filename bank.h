#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include "customer.h"
#include "account.h"
#include "saving.h"
#include "checking.h"

using std::string;

class Bank {
public: // public for testing, change when not testing
    std::vector<Customer*> BankCustomers;
    std::vector<Account*> BankAccounts;
    std::vector<Account*> ClosedAccounts;
//public:

    //table column values
    int total_width;
    int id_width;
    int first_name_width;
    int last_name_width;
    int address_width;
    int phone_width;
    int bd_width;

    Bank(){};
    void addCustomer();
    void openAccount(string customerId);
    void closeAccount(string accountNum);
    void printAccounts();
    void printCustomers();
    void printCustomerAccounts(string customerId);
    void depositMoney(string accountNum); 
    void withdrawMoney(string accountNum);
    void applyInterest();
    
    ~Bank() {
        for(auto customer : BankCustomers) {
            delete customer;
        }
        for(auto account : BankAccounts) {
            delete account;
        }
    }
};


#endif