#include <iostream>
#include <limits>
#include "maintenance.h"

void toReturn() {
    std::cout << std::endl << "Press 'Enter' to return to Main Menu" << std::endl;
    getchar();
}

template <>
bool checkCancel<double>(double input) {
    return input == 0.0;
}

template <>
bool checkCancel<int>(int input) {
    return input == 0;
}

template <>
bool checkCancel<std::string>(std::string input) {
    return input == "0";
}