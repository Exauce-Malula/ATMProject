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

double doubleLocalStoredBalance = NULL;

void RewriteBalance(double doubleLocalStoredBalance, std::string globalUsername) {
	std::fstream file(globalUsername, std::ios::in | std::ios::out); // Open file for input and output

	if (!file.is_open()) { // Error checking for if the file isn't opened correctly.
		std::cerr << "Failed to open the file!" << std::endl;
		returnType = -1;
	}

	// Step 1: Read all lines from the file into a vector
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	// Step 2: Modify the specific line (e.g., line 3, which is index 2 in zero-based indexing)
	int lineNumberToReplace = 2; // Line 3 in zero-based indexing

	if (lines.size() > lineNumberToReplace) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << doubleLocalStoredBalance; // Format double to 2 decimal places
		lines[lineNumberToReplace] = oss.str(); // Replace with formatted double as string
	}
	else {
		std::cerr << "File doesn't have that many lines!" << std::endl;
		returnType = -1;
	}

	// Step 3: Write the modified content back to the file
	// Clear the file and reset the writing position
	file.clear(); // Clear any errors that may have occurred
	file.seekp(0); // Go back to the beginning of the file
	file.seekg(0); // Go back to the beginning of the file for reading (if needed)

	for (const auto& l : lines) {
		file << l << std::endl;
	}

	file.close(); // Close the file
}

bool fileExists(const std::string& filename) {
	std::ifstream file(filename);
	return file.good();  // Returns true if the file exists, false otherwise
}

class actions {
	private:
		double transactionOperations = NULL;
	public:
		actions(double transactionOperations){
			this->transactionOperations = transactionOperations;
		}
		double GetTransactionOperations() {
			return transactionOperations;
		}
		void setTransactionOperations(double transactionOperations) {
			this->transactionOperations = transactionOperations;
		}
};

void balance() {
	std::string usernameNOTXT = globalUsername;
	usernameNOTXT = usernameNOTXT.erase(usernameNOTXT.length() - 4);
	if (globalUsername == "NULL") {
		std::cout << "\nIncorrect password. Please close the application and try again.";
		returnType = -1;
	}
	else {
		// Create an ifstream object to open the file
		std::ifstream inFile(globalUsername);

		// Check if the file was successfully opened
		if (!inFile) {
			std::cerr << "Error opening file. " << globalUsername << " does not exist." << std::endl;
		}
		else { // Checks if there is a balance in the .txt file.
			std::string line;
			int currentLine = 0;
			std::string storedBalance = "";
			int balanceCheckLine = 3;

			// Read file lines
			while (std::getline(inFile, line)) {
				currentLine++;
				if (currentLine == balanceCheckLine) {
					storedBalance = line;
				}
			}

			if (storedBalance.empty()) { // If there is no balance present.
				std::cerr << "File " << globalUsername << " does not have enough lines." << std::endl;
			}
			else {
				std::cout << "Hello " << usernameNOTXT << ", your balance is $" << storedBalance << "." << std::endl;
			}

			double doubleStoredBalance = std::stod(storedBalance); // std::stod converts a string to a double.
			doubleLocalStoredBalance = doubleStoredBalance;
		}
	}
}

void transaction() {
	bool transactionLOOP = true; //Loop for transaction choices.
	char transactionChoice; //To choose options.
	double moneyInput = NULL; //To input a value of money.
	double originalStoredBalance = doubleLocalStoredBalance; // Creates an original stored balance, for file creation of transaction history.
	std::string accountNameInput; //For sending money to an account.

	std::time_t current_time = std::time(nullptr); // Get the current time as a time_t object
	// Convert to a readable string format using ctime

	// Buffer to store the date and time string
	char buffer[26];  // ctime_s requires a buffer of at least 26 characters

	// Convert to a readable string format using ctime_s
	errno_t err = ctime_s(buffer, sizeof(buffer), &current_time);

	while (transactionLOOP == true) { // Loops through options.
		std::cout << "\nWould you like to either deposit your money, withdraw your money, send money to an account or check your history?\nType D for deposit\nType W for withdrawal\nType S to send money to an account\nType H to check your history.\nor\nType X to end the program.";
		std::cin >> transactionChoice;
		switch (transactionChoice) { // Switch statement for choices (STILL BEING WORKED ON.)
		default:
			std::cout << "\nIncorrect letter choice, please try again."; // If user inputs wrong choice.
			break;
		case 'X': // Exit program
			returnType = 1;
			transactionLOOP = false;
			break;
		case 'D': // Deposit
			while (moneyInput == NULL || moneyInput < 0.00) { // Checks for if the money input is positive or negative, has to be positive for deposit.
				std::cout << "\nEnter the amount of money you want to deposit (will be rounded to 2 decimal places):\n", std::cin >> moneyInput;
				if (moneyInput < 0.00) {
					std::cout << "\nUnable to deposit a negative value. Either:\n- Try again and type a positive value\nor\n- Type 0.00 to deposit no money and return to the main menu.\n";
				}
				else if (moneyInput == 0.00) { // User decides not to deposit
					std::cout << "\nNo deposit made. Returning to the main menu.\n";
					break; // Exit the loop and the case without making a transaction
				}
				else {
					break;
				}
			}
			actions* DepositAction; // Creates new object for the class.
			DepositAction = new actions(moneyInput);
			if (DepositAction == nullptr) { // Nullptr check for if memory has been correctly allocated.
				returnType = -1; // Returns with an error.
				break;
			}
			moneyInput = std::round(moneyInput * 100) / 100; // Rounds to 2 decimal places.
			DepositAction->setTransactionOperations(moneyInput); // Setter.

			doubleLocalStoredBalance = doubleLocalStoredBalance + DepositAction->GetTransactionOperations(); // Adds the deposit to the balance.

			if (DepositAction->GetTransactionOperations() == 0.00) { // If the user decides to set the input to 0.00
				moneyInput = NULL;
				originalStoredBalance = doubleLocalStoredBalance;
				delete DepositAction;
				DepositAction = nullptr;
				break;
			}

			if (err == 0) {
				buffer[strcspn(buffer, "\n")] = '\0';
				std::cout << "\nYou have made a deposit of $" << DepositAction->GetTransactionOperations() << " at " << buffer << ", now making your balance $" << doubleLocalStoredBalance << ".\n";

				//Transaction history for DEPOSITS
				std::string transactionHistory = globalUsername + " Transaction History.txt";
				if (fileExists(transactionHistory)) {
					std::ifstream file(transactionHistory);
					std::ofstream outFile(transactionHistory, std::ios::app);
					outFile << "\n"
						<< buffer
						<< ", a transaction of +$"
						<< DepositAction->GetTransactionOperations()
						<< ", increasing the account value from $" << originalStoredBalance
						<< " to $"
						<< doubleLocalStoredBalance
						<< "."; //Writes history of transaction if the file exists already
				}
				else {
					std::ofstream outFile(transactionHistory); // Creates file.

					// Check if the file was successfully opened
					if (!outFile) {
						std::cerr << "Error creating file. user: " << transactionHistory << std::endl;
					}

					// Writes the transaction history, plus the time.
					outFile << buffer
						<< ", a transaction of +$"
						<< DepositAction->GetTransactionOperations()
						<< ", increasing the account value from $"
						<< originalStoredBalance
						<< " to $"
						<< doubleLocalStoredBalance
						<< "."; //Writes history of transaction for a NEWFILE!!
				}
				RewriteBalance(doubleLocalStoredBalance, globalUsername);
			}
			else {
				std::cerr << "\nError converting time to string.\n" << std::endl;
				returnType = -1;
			}

			moneyInput = NULL;
			originalStoredBalance = doubleLocalStoredBalance;
			delete DepositAction;
			DepositAction = nullptr;
			break;

		case 'W': //Withdrawal
			if (originalStoredBalance < -100.00) { // Checks if the account has gone over its overdraft
				std::cout << "\nYour balance of -$" << fabs(originalStoredBalance) << " means you have gone over your overdraft limit. You cannot withdraw money until you are above this limit.\n";
				break;
			}
			while (moneyInput == NULL || moneyInput > 0.00) { // Checks for if the money input is positive or negative, has to be negative for withdrawal.
				if (originalStoredBalance < -100.00) {
					break;
				}
				std::cout << "\nEnter the amount of money you want to withdraw (will be rounded to 2 decimal places):\n", std::cin >> moneyInput;
				if (moneyInput > 0.00) {
					std::cout << "\nUnable to withdraw a positive value. Either:\n- Try again and type a negative value\nor\n- Type 0.00 to withdraw no money and return to the main menu.\n";
				}
				else if (moneyInput == 0.00) { // User decides not to withdraw
					std::cout << "\nNo withdrawal made. Returning to the main menu.\n";
					break; // Exit the loop and the case without making a transaction
				}
				else if (moneyInput < -100.00) {
					std::cout << "\nYou cannot withdraw this amount, this will go over your overdraft limit. Try again and withdraw a lower amount.\n";
					break;
				}
				else if (originalStoredBalance - moneyInput < -100.00 || originalStoredBalance <= -100.00) { //Unable to withdraw money above overdraft limit.
					std::cout << "\nYou cannot withdraw this amount, this will go over your overdraft limit. Try again and withdraw a lower amount.\n";
					break;
				}
				else {
					break;
				}
			}

			if (moneyInput < -100.00) {
				moneyInput = 0.00; // Probably not the best way to do this, but, whenever the user inputs a value less than -100.00, it breaks the switch case, and a statement in the previous while loop will appear.
				break;
			}
			if (originalStoredBalance - moneyInput < -100.00 || originalStoredBalance <= -100.00) {
				moneyInput = 0.00; // Probably not the best way to do this, but, whenever the user inputs a value where if the original stored balance is lower or equal to than -100.00, or if the money input subtract the original balance is lower than -100.00, it breaks the switch case, and a statement in the previous while loop will appear.
				break;
			}

			actions* WithdrawAction; // Creates new object for the class.
			WithdrawAction = new actions(moneyInput);
			if (WithdrawAction == nullptr) { // Nullptr check for if memory has been correctly allocated.
				returnType = -1; // Returns with an error.
				break;
			}
			moneyInput = std::round(moneyInput * 100) / 100; // Rounds to 2 decimal places.
			WithdrawAction->setTransactionOperations(moneyInput); // Setter.

			doubleLocalStoredBalance = doubleLocalStoredBalance + WithdrawAction->GetTransactionOperations(); // Withdraws the money from the balance.

			if (WithdrawAction->GetTransactionOperations() == 0.00) { // If the user decides to set the input to 0.00
				moneyInput = NULL;
				originalStoredBalance = doubleLocalStoredBalance;
				delete WithdrawAction;
				WithdrawAction = nullptr;
				break;
			}

			if (err == 0) {
				buffer[strcspn(buffer, "\n")] = '\0';
				std::cout << "\nYou have withdrawn $" << WithdrawAction->GetTransactionOperations() << " from your account at " << buffer << ", now making your balance $" << doubleLocalStoredBalance << ".\n";

				//Transaction history for WITHDRAWALS
				std::string transactionHistory = globalUsername + " Transaction History.txt";
				if (fileExists(transactionHistory)) {
					std::ifstream file(transactionHistory);
					std::ofstream outFile(transactionHistory, std::ios::app);
					outFile << "\n"
						<< buffer
						<< ", a transaction of -$"
						<< fabs(WithdrawAction->GetTransactionOperations())
						<< ", decreasing the account value from $" << originalStoredBalance
						<< " to $"
						<< doubleLocalStoredBalance
						<< "."; //Writes history of transaction if the file exists already
				}
				else {
					std::ofstream outFile(transactionHistory); // Creates file.

					// Check if the file was successfully opened
					if (!outFile) {
						std::cerr << "Error creating file. user: " << transactionHistory << std::endl;
					}

					// Writes the transaction history, plus the time.
					outFile << buffer
						<< ", a transaction of -$"
						<< fabs(WithdrawAction->GetTransactionOperations())
						<< ", decreasing the account value from $"
						<< originalStoredBalance
						<< " to $"
						<< doubleLocalStoredBalance
						<< "."; //Writes history of transaction for a NEWFILE!!
				}
				RewriteBalance(doubleLocalStoredBalance, globalUsername);
			}
			else {
				std::cerr << "\nError converting time to string.\n" << std::endl;
				returnType = -1;
			}

			moneyInput = NULL;
			originalStoredBalance = doubleLocalStoredBalance;
			delete WithdrawAction;
			WithdrawAction = nullptr;
			break;

		
	/*	case 'S':
			// Sending money: Create a notification system to send money to another account (Line 4 for notification). 
			while (true) {
				while (moneyInput == NULL) {
					std::cout << "\nInput the name of the account you want to send money to:\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::getline(std::cin, accountNameInput); // Asks user for the account name.
					std::cout << "\nInput the amount of money you want to send to " << accountNameInput << ": ", std::cin >> moneyInput; // Asks user for the amount of money they are transferring.
					if (moneyInput < 0.00) {
						std::cout << "\nUnable to send a negative value. Either:\n- Try again and type a positive value\nor\n- Type 0.00 to send no money and return to the main menu.\n";
					}
					else if (moneyInput == 0.00) {
						std::cout << "\nNo transaction made. Returning to the main menu.\n";
						break; // Exit loop if no transaction is made
					}
				}

				// Exit if no money is being transferred
				if (moneyInput == 0.00) {
					break;
				}

				// Initialize before entering conditionally controlled areas
				std::ostringstream stringMoneyInput;
				stringMoneyInput << std::fixed << std::setprecision(2) << moneyInput;

				std::ifstream fileIn(accountNameInput + ".txt"); // Open file for reading
				if (!fileIn.is_open()) {
					std::cerr << "Failed to open the file!" << std::endl;
					returnType = -1;
					break; // Break out of the switch case if file opening fails
				}

				std::vector<std::string> lines;
				std::string line;

				// Step 1: Read all lines from the file into a vector
				while (std::getline(fileIn, line)) {
					lines.push_back(line);
				}
				fileIn.close(); // Close the input file

				int lineNumberToInsert = 3; // Line 4 in zero-based indexing

				if (accountNameInput == "NULL") {
					std::cout << "\nERROR";
					returnType = -1;
					break; // Break if invalid account
				}

				// Create ifstream to open file
				std::ifstream inFile(accountNameInput + ".txt");

				// Check if the file was successfully opened
				if (!inFile) {
					std::cerr << "Error opening file. " << accountNameInput << " does not exist." << std::endl;
					break;
				}

				std::string storedBalance = "";
				int balanceCheckLine = 3;
				int currentLine = 0;

				// Read file lines to check balance
				while (std::getline(inFile, line)) {
					currentLine++;
					if (currentLine == balanceCheckLine) {
						storedBalance = line;
					}
				}

				if (storedBalance.empty()) { // If there is no balance present.
					std::cerr << "File " << accountNameInput << " does not have enough lines." << std::endl;
					break;
				}

				double doubleStoredBalance = std::stod(storedBalance); // std::stod converts a string to a double.
				doubleLocalStoredBalance = doubleStoredBalance;

				std::string newText = "You have been sent $" + stringMoneyInput.str()
					+ " from the user "
					+ globalUsername.erase(globalUsername.length() - 4) +
					". You now have $" + std::to_string(doubleLocalStoredBalance) + ".";

				// Step 2: Check if line 4 is empty and insert text if it is
				if (lines.size() > lineNumberToInsert) {
					if (lines[lineNumberToInsert].empty()) {
						lines[lineNumberToInsert] = newText; // Insert text if line 4 is empty
						std::cout << newText << std::endl;
						doubleLocalStoredBalance -= moneyInput;
						RewriteBalance(doubleLocalStoredBalance, globalUsername);
						originalStoredBalance = doubleLocalStoredBalance;
					}
					else {
						std::cout << "\nThis account is already processing a transfer! Please try again later.\n" << std::endl;
					}
				}
				else if (lines.size() == lineNumberToInsert) {
					// If there are exactly 3 lines, line 4 doesn't exist yet, so add it
					lines.push_back(newText);
					std::cout << buffer
						<< ", a transaction of -$"
						<< fabs(moneyInput)
						<< ", decreasing the account value from $"
						<< originalStoredBalance
						<< " to $"
						<< doubleLocalStoredBalance
						<< ", sending money to the account \"" << accountNameInput
						<< "\"." << std::endl;
				}
				else {
					std::cerr << "INVALID ACCOUNT\n" << std::endl;
					break;
				}

				// Step 3: Write the modified content back to the file
				std::ofstream fileOut(accountNameInput + ".txt"); // Open the file for writing (this overwrites the file)
				if (!fileOut.is_open()) {
					std::cerr << "Failed to open the file for writing!" << std::endl;
					returnType = -1;
					break; // Break out if unable to write to the file
				}

				for (const auto& l : lines) {
					fileOut << l << std::endl;
				}

				fileOut.close(); // Close the output file
				break;
			}
			break;
			*/
			
		case 'H':
			std::string filenameHistory = globalUsername + " Transaction History.txt";
			std::ifstream file(filenameHistory);  // Open the file for reading
			if (!file.is_open()) {
				std::cerr << "Error: Could not open the file " << filenameHistory << std::endl;
				returnType = -1;
				break;
			}

			std::string line;
			std::cout << "\n";
			while (std::getline(file, line)) {  // Read the file line by line
				std::cout << line << std::endl;  // Print each line to the console
			}

			file.close();  // Close the file after reading
			break; 

		}
	}

}
