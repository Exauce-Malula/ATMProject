# ATMProject
A banking project I worked over the 2023/2024 summer holidays after my GCSEs. I wanted to see how proficient I was with the language after also learning it over the summer.
I wanted to see if I could effectively use dynamic memory allocation, pointers and object - oriented programming, learning and knowing how to use these would help with my Computer Science A-Level.

The majority of the programming was done by me, however, some areas such as obscuring the password, retrieving the time, and some of the file handling was done by AI generation. 

# Login
The user details are contained within a class named "NewLoginDetails", utilising setters, getters and constructors to encapsulate/protect the username/password. In the function "login", the user makes the choice to either create an account, or log in into an account.

If the user decides to create a new account, they input a new username and password, where the password is obscured by stars for user safety. However, the passwords must have the conditions of having at least 8 characters, an uppercase character, a lowercase character, a number and a symbol, otherwise, the user must change their password. After these checks, a new object is created, using a pointer which was previously declared near the beginning of "login". Then, the username and password are passed as global variables, a .txt file with the username and password is created, and any memory is freed at the end.

If the user decides to login, the user inputs their username and password, which becomes stored as global variables. However, if the username is correct yet the password is incorrect, the username is set to "NULL" to prevent login.

# Balance
If there are any errors when opening the file, an error message will appear and end the program. Otherwise, a welcome message showing the username and balance is printed, all of this happens within the function "balance". 

The next function, "transaction" gives the user the option between depositing money, withdrawing money, send money to an account, check transaction history, or exit the application. Switch cases are utilised for the user to select different options.

To deposit or withdraw, if the user decides they don't want to deposit/withdraw, they would input 0.00. For a deposit, the value must be positive. For a withdrawal, the value must be negative, and that their balance must be greater than -$100.00, as this is the user's overdraft limit. A class is used to represent the action between the balance and the value inputted for either a deposit/withdrawal. A text file is created to store a receipt of the interaction, if there is already a file, the history is added to that file.

To check the history, the transaction history file is printed. 

Additionally, there was an option to send money to other accounts, however, due to the summer being over, plus unable to think of any ideas on how to correctly implement it, I was unable to finish this. Remnants of this code is still left in "ATMProject_BALANCE", as I thought of utilising a notification system in order to notify the user recieving money.

# Improvements
Overall, I think I did well, especially with this being my first ever C++ coding project. However, I could've improved the code by avoiding repeat blocks of codes, which could be represented within multiple functions.
