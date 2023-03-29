    #include <iostream>
    #include <iomanip>
    #include <limits>
    #include "bank.h"
    #include "maintenance.h"

    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    enum MenuChoice {  //enumerations for switch statement readability
        Deposit = 1,
        Withdraw = 2,
        PrintCustomerAccounts = 3,
        OpenAccount = 4,
        CloseAccount = 5,
        PrintAccounts = 6,
        AddCustomer = 7,
        PrintCustomers = 8,
        ApplyInterest = 9,
        Exit = 0
    };

    int main() {

    Bank bank = Bank();

    //Testing Initialization
    Customer* David = new Customer("David", "Supinosamorris", "440 Buster Brown RD", "(678) 877-7623", "1993-12-31"/* 12, 31, 1993 */);
    bank.BankCustomers.push_back(David);
    Customer* Austin = new Customer("Austin", "Morris", "80 Lewellen Dr", "(478) 579-8500", "1998-09-01"/* 9, 1, 1998 */);
    bank.BankCustomers.push_back(Austin);
    Customer* Annabelle = new Customer("Annabelle", "Reeves", "80 Longer than Lewellen Dr", "(789) 789-7890", "2002-08-24"/* 8, 24, 2002 */);
    bank.BankCustomers.push_back(Annabelle);
    //----------------------------------------------------------*/

    int menuChoice = -1;
    bool exit = false;

    int loggedIn = system("login.exe");

    if(loggedIn == 0) {
        return 0;
    }

    while(menuChoice != 0) {
        system("cls");
        cout << "****** Bank Management ******" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Print Customer's Accounts" << endl;
        cout << "4. Open Account" << endl;
        cout << "5. Close Account" << endl;
        cout << "6. Print Accounts" << endl;
        cout << "7. Add Customer" << endl;
        cout << "8. Print Customers" << endl;
        cout << "9. Apply Interest" << endl;
        cout << "0. Exit Application" << endl << endl;
        cout << "Choice: "; 
        menuChoice = getValidInput(menuChoice);

        string customerId;
        string accountNum;
        
        switch(menuChoice) {
            case MenuChoice(Deposit):
                cout << "Account Number: "; getline(cin, accountNum);
                if(checkCancel(accountNum)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.depositMoney(accountNum);
                toReturn();
                break;
            case MenuChoice(Withdraw):
                cout << "Account Number: "; getline(cin, accountNum);
                if(checkCancel(accountNum)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.withdrawMoney(accountNum);
                toReturn();
                break;
            case MenuChoice(PrintCustomerAccounts):
                cout << "Customer ID: "; getline(cin, customerId);
                if(checkCancel(customerId)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.printCustomerAccounts(customerId);
                toReturn();
                break;
            case MenuChoice(OpenAccount):
                cout << "Customer ID: "; getline(cin, customerId);
                if(checkCancel(customerId)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.openAccount(customerId);
                toReturn();
                break;
            case MenuChoice(CloseAccount):
                cout << "Account Number: "; getline(cin, accountNum);
                if(checkCancel(accountNum)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.closeAccount(accountNum);
                toReturn();
                break;
            case MenuChoice(PrintAccounts):
                bank.printAccounts();
                toReturn();
                break;
            case MenuChoice(AddCustomer):
                bank.addCustomer();
                toReturn();
                break;
            case MenuChoice(PrintCustomers):
                bank.printCustomers();
                toReturn();
                break;
            case MenuChoice(ApplyInterest):
                cout << "Apply Interest? (0 to cancel)" << endl;
                getline(cin, accountNum);
                if(checkCancel(accountNum)) {
                    cout << "Cancelled" << endl;
                    toReturn();
                    break;
                }
                bank.applyInterest();
                toReturn();
                break;
            case MenuChoice(Exit):
                exit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                toReturn();
                break;
        }
        if(exit)
            break; // closes program


    } //end of while loop
    } //end of main

    /* Main menu, letter try again, invalid number restarts menu.. Boolean template.. loop on input
    Add $ signs 
    transfer money between accounts.. and from cehcking to savings, vice versa. 
    */