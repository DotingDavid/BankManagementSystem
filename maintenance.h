#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>

void toReturn();

template <typename T>
T getValidInput(T& input) {
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice, please try again" << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input; // breaks out of loop
        }
    }
}

template <typename T>
bool inputFailed(T& input) {
    while (true) {
        if (std::cin.fail()) {
            return false;
        }
        else {
            return true;
        }
    }
}

template <typename T>
bool checkCancel(T input);

#endif