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

class NewLoginDetails {
	private:
		// Creates a class which contains the username and password for a new login.
		std::string username = "";
		std::string password = "";
	public:
		std::string GetUsername() {
			return username;
			// Getter for the username, makes it public.
		}
		void SetUsername(const std::string& username) {
			this->username = username;
			// Setter for the username.
		}
		std::string GetPassword() {
			return password;
			// Getter for the password, makes it public.
		}
		void SetPassword(const std::string& password) {
			this->password = password;
			// Setter for the password.
		}
		NewLoginDetails(const std::string& username, const std::string& password) {
			this->username = username;
			this->password = password;
			// Constructor for the password and username.
		}
};

void login() {
	int accountCheck = NULL;
	bool loopCheck = true;
	bool passwordCheckloop = true;

	std::cout << "Welcome to Malula Banks©.\nPlease login or create a new account.\nType 0 to create an account, or type 1 to login. ", std::cin >> accountCheck;
	std::cin.ignore();

	if (accountCheck > 1 || accountCheck < 0) {
		// Checks if the user input is incorrect, then loops until it gets a correct input.
		while (loopCheck == true) {
			std::cout << "\nIncorrect input. Type 0 to create an account, or type 1 to login. ", std::cin >> accountCheck;
			std::cin.ignore();
			if (accountCheck == 0 || accountCheck == 1) {
				loopCheck = false;
			}
		}
	}

	if (accountCheck == 0) {
		NewLoginDetails* newAccount{};
		// Creates a pointer to the class object, named newAccount.
		std::string newUserName = "";
		std::string newPassword = "";
		std::cout << "\nEnter a username: ", std::getline(std::cin, newUserName);
		//Username input.

		while (passwordCheckloop == true) { // A password loop, checks for conditions for the password to be viable.
			
			std::cout << "\nEnter a password:\n"; // Asks the user to input a password.
			
			/*
				Password input: this masks the password with the '*' symbol, remember that this is a WINDOWS API only feature, will not work on
				any UNIX operating systems.
			*/

			char ch;
			while ((ch = _getch()) != '\r') { // _getch() reads a single character without echoing it
				if (ch == '\b') { // Handle backspace
					if (!newPassword.empty()) {
						newPassword.pop_back();
						std::cout << "\b \b"; // Remove the last asterisk
					}
				}
				else {
					newPassword.push_back(ch);
					std::cout << '*';
				}
			}
			const char* passwordArray = newPassword.c_str(); // Converts the password string to a 'C - style' char array.

			int lowercaseCount = 0;
			int uppercaseCount = 0;
			int numberCount = 0;
			int symbolCount = 0;
			int overallCharCheck = 0;

			for (size_t i = 0; i < newPassword.size(); i++) { // For loop checks for if there are at least a symbol, a number, an uppercase and lowercase letter.
				if (lowercaseCount == 0) {
					if (islower(passwordArray[i])) {
						lowercaseCount++;
					}
				}
				if (uppercaseCount == 0) {
					if (isupper(passwordArray[i])) {
						uppercaseCount++;
					}
				}
				if (numberCount == 0) {
					if (isdigit(passwordArray[i])) {
						numberCount++;
					}
				}
				if (symbolCount == 0) {
					if (ispunct(passwordArray[i])) {
						symbolCount++;
					}
				}
			}
			overallCharCheck = lowercaseCount + uppercaseCount + numberCount + symbolCount; // overallCharCheck must equal 4 in order for the password to be correct.

			std::cout << std::endl; // Move to the next line after password input
			if (newPassword.size() >= 8 && overallCharCheck == 4) { // Intended outcome, in order to break the loop and move on.
				passwordCheckloop = false;
				break;
			}
			else if (newPassword.size() < 8) { // If the password is under 8 characters.
				std::cout << "\n";
				std::cout << "Password too small. Try again.\n";
				newPassword = "";
				std::cin.clear();
			}
			else if (overallCharCheck != 4) { // Missing symbol check.
				if (lowercaseCount == 0) {
					std::cout << "\nYou must include a lowercase letter in your password.";
				}
				if (uppercaseCount == 0) {
					std::cout << "\nYou must include an uppercase letter in your password.";
				}
				if (numberCount == 0) {
					std::cout << "\nYou must include a number in your password.";
				}
				if (symbolCount == 0) {
					std::cout << "\nYou must include a symbol in your password.";
				}
				newPassword = "";
				std::cin.clear();
			}
		}

		newAccount = new NewLoginDetails(newUserName, newPassword); // Creates a new object, which has been allocated in the newAccount pointer.
		if (newAccount == nullptr) { // Standard nullptr check.
			std::cout << "\nERROR: Memory incorrectly allocated. Please close the application and try again later.";
			delete newAccount;
		}
		else {
			std::string fileName = newAccount->GetUsername() + ".txt";
			std::ofstream outFile(fileName); // Creates file.

			// Check if the file was successfully opened
			if (!outFile) {
				std::cerr << "Error creating file. user: " << fileName << std::endl;
			}

			// Optionally, write some content to the file
			outFile << newAccount->GetUsername() << std::endl << newAccount->GetPassword() << std::endl << "0.00";

			// Close the file
			outFile.close();

			std::cout << "File created successfully: " << fileName << std::endl;
		}
		globalPassword = newAccount->GetPassword();
		globalUsername = newAccount->GetUsername() + ".txt";
		newAccount = nullptr;
		delete newAccount;
		// Frees memory.
	}



	else if (accountCheck == 1) {
		std::string loginUsername = "";
		std::string loginPassword = "";
		int usernameCheckLine = 1;
		int passwordCheckLine = 2;

		std::cout << "\nPlease login:\nUsername:\n";
		std::getline(std::cin, loginUsername);
		loginUsername = loginUsername + ".txt";
		// Inputs username. 

		std::cout << "\nPassword:\n";
		char ch;
		while ((ch = _getch()) != '\r') { // _getch() reads a single character without echoing it
			if (ch == '\b') { // Handle backspace
				if (!loginPassword.empty()) {
					loginPassword.pop_back();
					std::cout << "\b \b"; // Remove the last asterisk
				}
			}
			else {
				loginPassword.push_back(ch);
				std::cout << '*';
			}
		} // Inputs password, replaces letters with an asterisk "*".
		std::cout << std::endl;

		// Create an ifstream object to open the file
		std::ifstream inFile(loginUsername);

		// Check if the file was successfully opened
		if (!inFile) {
			std::cerr << "Error opening file. " << loginUsername << " does not exist." << std::endl;
		}
		else {
			std::string line;
			int currentLine = 0;
			std::string storedUsername = "";
			std::string storedPassword = "";

			// Read file lines - Compares and checks the lines for the username and password.
			while (std::getline(inFile, line)) {
				currentLine++;
				if (currentLine == usernameCheckLine) {
					storedUsername = line;
				}
				if (currentLine == passwordCheckLine) {
					storedPassword = line;
				}
			}

			if (storedUsername.empty() || storedPassword.empty()) { // Error message if there are any missing lines.
				std::cerr << "File " << loginUsername << " does not have enough lines. DATA NOT FOUND" << std::endl;
			}
			else {

				if (loginPassword == storedPassword) { // Successful login
					std::cout << "Login successful!" << std::endl;
				}
				else { // Unsuccessful login
					std::cerr << "Incorrect password, please try again." << std::endl;
					returnType = -1;
				}

			}
			if (loginPassword != storedPassword) { // Password check, this is so that if the username is correct, but if the password is incorrect, you are unable to access the account.
				globalUsername = "NULL";
			}
			else { // Passes the username and password into global variables.
				globalPassword = loginPassword;
				globalUsername = loginUsername;
			}

		}

		// Close the file
		inFile.close();

		

	}
}