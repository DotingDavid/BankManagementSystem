#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "customer.h"

using std::cout;
using std::string;
using std::to_string;
using std::endl;
using std::setw;
using std::left;

/* BD::BD() {
    Month = 0;
    Day = 0;
    Year = 0;
}

BD::BD(int month, int day, int year) {
    Month = month;
    Day = day;
    Year = year;
}
 */
int Customer::IdCounter = 1000;

Customer::Customer(string firstName, string lastName, string address, string phone, string birthdate) {
    FirstName = firstName;
    LastName = lastName;
    Address = address;
    Phone = phone;
    //BD bd(month, day, year);
    //BirthDate = bd;
    BirthDate = birthdate;
    CustomerId = std::to_string(IdCounter);
    IdCounter++;
}

string Customer::getId() {
    return CustomerId;
}

void Customer::setName(string firstName, string lastName) {
    FirstName = firstName;
    LastName = lastName;
}

string Customer::getName() {
    string Name;
    Name = FirstName + " " + LastName;
    return Name;
}

string Customer::getFirstName() {
    return FirstName;
}

string Customer::getLastName() {
    return LastName;
}

void Customer::setAddress(string address) {
    Address = address;
}

string Customer::getAddress() {
    return Address;
}

void Customer::setPhone(string phone) {
    Phone = phone;
}

string Customer::getPhone() {
    return Phone;
}

/* void Customer::setBirthDate(BD birthdate) {
    BirthDate = birthdate;
} */

void Customer::setBirthDate(string birthdate) {
    BirthDate = birthdate;
}

string Customer::getBirthDate() {
    //string BirthDateString = std::to_string(BirthDate.Month) + "/" + std::to_string(BirthDate.Day) + "/" + std::to_string(BirthDate.Year);
    //return BirthDateString;
    return BirthDate;
}

void Customer::addAccount(Account* account) {
    CustomerAccounts.push_back(account);
    cout << account->getAccountNum() << " added successfully" << endl;
}

void Customer::printInformation(int id_width, int first_name_width, int last_name_width, int address_width, int phone_width, int bd_width, int total_width) {
    std::cout << std::left << std::setw(id_width) << "| " + CustomerId
              << std::setw(first_name_width) << "| " + FirstName
              << std::setw(last_name_width) << "| " + LastName
              << std::setw(address_width) << "| " + Address
              << std::setw(phone_width) << "| " + Phone
              << std::setw(bd_width) << "| " + BirthDate << "|" << std::endl;
    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
}

void Customer::printCustomerAccounts() {
    if(CustomerAccounts.empty()) {
        cout << endl << "Customer has no accounts" << endl;
        return;
    }

    int accountNum_width = 6;
    int accountType_width = 7;
    int accountBal_width = 7;
    int accountStatus_width = 8;
    int earnedInterest_width = 15;
    int cellPadding = 3;

    for (auto account : CustomerAccounts) {
        string earnedInterestString = std::to_string(account->earnedInterest());
        string accountBal = to_string(account->getAccountBalance());
        if(accountNum_width < account->getAccountNum().length())
            accountNum_width = account->getAccountNum().length();
        if(accountType_width < account->getAccountType().length())
            accountType_width = account->getAccountType().length();
        if(accountBal_width < accountBal.length())
            accountBal_width = accountBal.length();
        if(account->getAccountStatus() == "Outstanding")
            accountStatus_width = 11;
        if(earnedInterest_width < earnedInterestString.length())
            earnedInterest_width = earnedInterestString.length();
    }

    accountNum_width += cellPadding;
    accountType_width += cellPadding;
    accountBal_width += cellPadding;
    accountStatus_width += cellPadding;
    earnedInterest_width += cellPadding;
    int total_width = accountNum_width+accountType_width+accountBal_width+accountStatus_width+earnedInterest_width;

    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
    std::cout << std::left << std::setw(accountNum_width) << "| Acc #"
              << std::setw(accountType_width) << "| Type"
              << std::setw(accountBal_width) << "| Balance"
              << std::setw(accountStatus_width) << "| Status"
              << std::setw(earnedInterest_width) << "| Earned Interest" << "|" << std::endl;
    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;

    for(int i = 0; i<CustomerAccounts.size(); i++) {
        string accountBal = to_string(CustomerAccounts[i]->getAccountBalance());
        std::cout << std::left << std::setw(accountNum_width) << "| " + CustomerAccounts[i]->getAccountNum()
              << std::setw(accountType_width) << "| " + CustomerAccounts[i]->getAccountType()
              << std::setw(accountBal_width) << "| " + accountBal
              << std::setw(accountStatus_width) << "| " + CustomerAccounts[i]->getAccountStatus()
              << std::setw(earnedInterest_width) << "| " + std::to_string(CustomerAccounts[i]->earnedInterest()) << "|" << std::endl;
        std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
    }
}

/* int Customer::getCustomerAccountsSize() {
    return sizeof(CustomerAccounts);
} */

