#ifndef ATMProject_Header
#define ATMProject_Header

#include <string>

void login();

extern std::string globalPassword;
extern std::string globalUsername;
extern int returnType;

void balance();

void transaction();

#endif
