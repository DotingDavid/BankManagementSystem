#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include <regex>
#include "bank.h"
#include "maintenance.h"

using std::cout;
using std::cin;
using std::endl;

void Bank::addCustomer(){

    //std::string birthdateRegexPattern = "[0-9]{2}-?[0-9]{2}-?[0-9]{4}"; //MM-DD-YYYY
    //std::string birthdateRegexPattern = "(18[8-9][0-9]|19[0-9]{2}|20[01][0-9]|202[0-4])[ -/]?(0[1-9]|1[0-2])[ -/]?(0[1-9]|1[0-9]|2[0-9]|30|31)"; //YYYY-MM-DD

    std::string phoneRegexPattern = "^\\(?([0-9]{3})\\)?[- ]?([0-9]{3})[- ]?([0-9]{4})$";
    std::string birthdateRegexPattern = "(18[8-9][0-9]|19[0-9]{2}|20[01][0-9]|202[0-4])[ -/](0?[1-9]|1[0-2])[ -/](0?[1-9]|1[0-9]|2[0-9]|30|31){1,2}"; //YYYY-MM-DD, works without leading 0 for month and day

    std::regex phoneRegexRule(phoneRegexPattern);
    std::regex birthdateRegexRule(birthdateRegexPattern);

    std::string phoneFormat = "($1) $2-$3";
    std::string birthdateFormat = "$1-$2-$3";
    std::string month = "$2";
    std::string year = "$1";
    std::string day = "$3";


    string firstName;
    string lastName;
    string address;
    string phoneInput;
    string phoneOutput;
    string birthdateInput;
    string birthdateOutput;

    cout << "*****" << "Create a Customer" << "*****" << endl;
    cout << "First Name: "; getline(cin, firstName); if(checkCancel(firstName)) {cout << "Add Customer Cancelled\n"; return;}
    cout << "Last Name: "; getline(cin, lastName); if(checkCancel(lastName)) {cout << "Add Customer Cancelled\n"; return;}
    cout << "Address: "; getline(cin, address); if(checkCancel(address)) {cout << "Add Customer Cancelled\n"; return;}

    while(true) {
    cout << "Phone: "; getline(cin, phoneInput); if(checkCancel(phoneInput)) {cout << "Add Customer Cancelled\n"; return;}
        if(std::regex_match(phoneInput, phoneRegexRule)) {
            phoneOutput = std::regex_replace(phoneInput, phoneRegexRule, phoneFormat);
            break;
        }
        else {
            cout << "Invalid phone number. Please confirm that you have entered a 3 digit area code followed by a 7 digit number." << endl;
        }
    }     
    while(true) {
        cout << "Birthdate (YYYY-MM-DD): "; getline(cin, birthdateInput); if(checkCancel(birthdateInput)) {cout << "Add Customer Cancelled\n"; return;}
        string birthdateMonth;
        string birthdateYear;
        string birthdateDay;
        bool isValid = false;
        if(std::regex_match(birthdateInput, birthdateRegexRule)) {

            birthdateMonth = std::regex_replace(birthdateInput, birthdateRegexRule, month);
            birthdateDay = std::regex_replace(birthdateInput, birthdateRegexRule, day);
            birthdateYear = std::regex_replace(birthdateInput, birthdateRegexRule, year);

            //int birthdateMonthInt = std::stoi(birthdateMonth);
            int birthdateDayInt = std::stoi(birthdateDay);
            int birthdateYearInt = std::stoi(birthdateYear);

            if(birthdateMonth == "04" || birthdateMonth == "06" || birthdateMonth == "09" || birthdateMonth == "11") {
                if(birthdateDayInt > 30)
                    cout << "Invalid Date. This month only has 30 days" << endl;
                else 
                    isValid = true;
            }

            if(birthdateMonth == "02") {
                if(birthdateYearInt % 4 == 0) {
                    //Feb - leap year
                    if(birthdateDayInt > 29)
                        cout << "Invalid Date. February only has 29 days in a leap year" << endl;
                    else
                        isValid = true;
                }
                else {
                    //Feb - not a leap year
                    if(birthdateDayInt > 28)
                        cout << "Invalid Date. February only has 28 days, unless its a leap year" << endl;
                    else
                        isValid = true;
                }
            }

            birthdateOutput = std::regex_replace(birthdateInput, birthdateRegexRule, birthdateFormat);
            if(isValid == true)
                break;
        }
        else {
            cout << "Invalid Birthdate" << endl;
        }
    }
    

    //Confirm information option can go here

    Customer* c = new Customer(firstName, lastName, address, phoneOutput, birthdateOutput);
    BankCustomers.push_back(c);
}

void Bank::openAccount(string customerId) {
    bool found = false;
    for(auto customer : BankCustomers) {
        if(customer->getId() == customerId) {
            found = true;
            cout << "*****" << "Open Account" << "*****" << endl;
            cout << "1. Checking Account" << endl;
            cout << "2. Saving Account" << endl;
            cout << "0. Cancel" << endl;
            int accountChoice = 0;
            accountChoice = getValidInput(accountChoice);

            while(true) {
                if(accountChoice > 2 || accountChoice < 0) {
                    cout << "Invalid Choice, please try again" << endl;
                    accountChoice = getValidInput(accountChoice);
                }
                else {
                    break;
                }
            }

            switch(accountChoice) {
                case 1: {
                    Account* a = new CheckingAccount();
                    for(auto customer : BankCustomers) {
                        if(customerId == customer->getId()) {
                            customer->addAccount(a);
                            BankAccounts.push_back(a);
                        }
                    }  
                    break;
                }
                case 2: {
                    Account* a = new SavingAccount();
                    for(auto customer : BankCustomers) {
                        if(customerId == customer->getId()) {
                            customer->addAccount(a);
                            BankAccounts.push_back(a);
                        }
                    }  
                    break;
                }
                case 0:
                    cout << "Open Account Cancelled" << endl;
                    return;
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;
            }//end of switch statement          
        }//end of if statement
    }//end of for loop
    if(found == false) {
        cout << "Customer not found" << endl;
    }
}


/* void Bank::closeAccount(string accountNum) {
    auto accountIterator = BankAccounts.begin();
    while(accountIterator != BankAccounts.end()) {
        if(accountNum == (*accountIterator)->getAccountNum()) {
            (*accountIterator)->closeAccount();
            ClosedAccounts.push_back(*accountIterator);
            if((*accountIterator)->getAccountBalance() == 0)
                cout << "Account has been closed" << endl;
            if((*accountIterator)->getAccountBalance() < 0) {
                cout << "Account has been closed with an outstanding balance" << endl;
                cout << "Account Balance: " << (*accountIterator)->getAccountBalance() << endl;
            }
            break;    
        }
        accountIterator++;
    }
    if(accountIterator == BankAccounts.end())
        cout << "Account not found" << endl;
} */

void Bank::closeAccount(string accountNum) {
    bool found = false;
    for(auto account : BankAccounts) {
        if(accountNum == account->getAccountNum()) {
            found = true;
            account->closeAccount();
            ClosedAccounts.push_back(account);
            if(account->getAccountBalance() == 0) {
                cout << "Account has been closed" << endl;
            }
            if(account->getAccountBalance() < 0) {
                cout << "Account has been closed with an outstanding balance" << endl;
                cout << "Account Balance: " << account->getAccountBalance() << endl;
            }
        }
    }
    if(!found) {
        cout << "Account not found" << endl;
    }
}

void Bank::printAccounts() {

    if(BankAccounts.empty()) {
        cout << "Bank has no accounts" << endl;
        return;
    }

    int accountNum_width = 6;
    int accountType_width = 7;
    int accountBal_width = 7;
    int accountStatus_width = 6;
    int earnedInterest_width = 15;
    int cellPadding = 3;

    for (auto account : BankAccounts) {
        string earnedInterest = std::to_string(account->earnedInterest());
        string accountBal = std::to_string(account->getAccountBalance());
        if(accountNum_width < account->getAccountNum().length())
            accountNum_width = account->getAccountNum().length();
        if(accountType_width < account->getAccountType().length())
            accountType_width = account->getAccountType().length();
        if(accountBal_width < accountBal.length())
            accountBal_width = accountBal.length();
        if(account->getAccountStatus() == "Outstanding")
            accountStatus_width = 11;
        if(earnedInterest_width < earnedInterest.length())
            accountStatus_width == earnedInterest.length();
    }

    accountNum_width += cellPadding;
    accountType_width += cellPadding;
    accountBal_width += cellPadding;
    accountStatus_width += cellPadding;
    earnedInterest_width += cellPadding;
    int total_width = accountNum_width+accountType_width+accountBal_width+accountStatus_width+earnedInterest_width;

    std::cout << "Bank Accounts" << std::endl;

    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
    std::cout << std::left << std::setw(accountNum_width) << "| Acc #"
              << std::setw(accountType_width) << "| Type"
              << std::setw(accountBal_width) << "| Balance"
              << std::setw(accountStatus_width) << "| Status"
              << std::setw(earnedInterest_width) << "| Earned Interest" << "|" << std::endl;
    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;

    for(auto account : BankAccounts) {
        account->printAccountInfo(accountNum_width, accountType_width, accountBal_width, accountStatus_width, earnedInterest_width, total_width);
    }
}

void Bank::printCustomers() {
    // Set minimum column width values
    int max_id_length = 4;
    int max_first_name_length = 14;
    int max_last_name_length = 14;
    int max_address_length = 27;
    int max_phone_length = 15;
    int max_bd_length = 15;
    int cellPadding = 3;

    // Find maximim column width values
    for(auto customer : BankCustomers) {
        if(max_id_length < customer->getId().length())
            max_id_length = customer->getId().length();
        if(max_first_name_length < customer->getFirstName().length())
            max_first_name_length = customer->getFirstName().length();
        if(max_last_name_length < customer->getLastName().length())
            max_last_name_length = customer->getLastName().length();
        if(max_address_length < customer->getAddress().length())
            max_address_length = customer->getAddress().length();
        if(max_phone_length < customer->getPhone().length())
            max_phone_length = customer->getPhone().length();
    }

    // Adjust the column widths based on the maximum lengths
    id_width = max_id_length + cellPadding;
    first_name_width = max_first_name_length + cellPadding;
    last_name_width = max_last_name_length + cellPadding;
    address_width = max_address_length + cellPadding;    
    phone_width = max_phone_length + cellPadding;
    bd_width = max_bd_length + cellPadding;
    total_width = id_width+first_name_width+last_name_width+address_width+phone_width+bd_width;

    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
    std::cout << std::left << std::setw(id_width) << "| ID#"
              << std::setw(first_name_width) << "| First Name"
              << std::setw(last_name_width) << "| Last Name"
              << std::setw(address_width) << "| Address"
              << std::setw(phone_width) << "| Phone"
              << std::setw(bd_width) << "| BD (YYYY-MM-DD)" << "|" << std::endl;
    std::cout << "+" << std::string(total_width - 1, '-') << "+" << std::endl;
    for(auto customer : BankCustomers) {
        customer->printInformation(id_width, first_name_width, last_name_width, address_width, phone_width, bd_width, total_width);
    }
}

void Bank::printCustomerAccounts(string customerId) {
    bool found = false;
    for(auto customer : BankCustomers) {
        if(customerId == customer->getId()) {
            found = true;
            customer->printCustomerAccounts();
        }
    }
    if(!found) {
        cout << "Customer not found" << endl;
    }
}

void Bank::depositMoney(string accountNum) {
    bool found = false;
    for(auto account : BankAccounts) {
        if(accountNum == account->getAccountNum()) {
            found = true;
            account->depositMoney();
        }
    }
    if(!found) 
        cout << "Account not found" << endl;
}

void Bank::withdrawMoney(string accountNum) {
    bool found = false;
    for(auto account : BankAccounts) {
        if(accountNum == account->getAccountNum()) {
            found = true;
            account->withdrawMoney();
        }
    }
    if(!found)
        cout << "Account not found" << endl;
}

void Bank::applyInterest(){
    for(auto account : BankAccounts) {
        account->applyInterest();
    }
    cout << "Interest Applied" << endl;
}