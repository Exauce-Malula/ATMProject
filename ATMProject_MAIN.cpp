#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <cstddef>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip> // For std::setprecision
#include "ATMProject_Header.h"

//TODO - I need to create a method for notifications and sending money to other accounts, this will probably be the last thing I need to do for the project to be 'complete'.
//     - Rewrite the balance of the recipetant when they have been sent money, and save this in their transaction history.

int main()
{
    if (returnType == -1) {
        return -1;
    }
    if (returnType == 1) {
        return 0;
    }
    login(); //TODO - Create a way to prevent accounts with same usernames, add potential encryption.
    if (returnType == -1) {
        return -1;
    }
    if (returnType == 1) {
        return 0;
    }
    balance(); 
    if (returnType == -1) {
        return -1;
    }
    if (returnType == 1) {
        return 0;
    }
    transaction(); 
    if (returnType == -1) {
        return -1;
    }
    if (returnType == 1) {
        return 0;
    }
}
