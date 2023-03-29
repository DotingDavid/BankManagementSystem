#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "account.h"

using std::string;

/* struct BD {
    int Month = 0;
    int Day = 0;
    int Year = 0;
    BD();
    BD(int month, int day, int year);
};
 */
class Customer {
    static int IdCounter;
    string CustomerId;
    string FirstName;
    string LastName;
    string Address;
    string Phone;
    //BD BirthDate;
    string BirthDate;
    std::vector<Account*> CustomerAccounts;
public:
    Customer(string firstName, string lastName, string address, string phone, string birthdate);
    void setName(string firstName, string lastName);
    string getId();
    string getName();
    string getFirstName();
    string getLastName();
    void setAddress(string address);
    string getAddress();
    void setPhone(string phone);
    string getPhone();
    //void setBirthDate(BD birthdate);
    void setBirthDate(string birthdate);
    string getBirthDate();
    void addAccount(Account* account);
    void printInformation(int id_width, int first_name_width, int last_name_width, int address_width, int phone_width, int bd_width, int total_width);
    void printCustomerAccounts();
    //int getCustomerAccountsSize();

    ~Customer() {
        for(auto account : CustomerAccounts) 
            delete account;
    }
};




#endif