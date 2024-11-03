# ATMProject
A banking project I worked over the 2023/2024 summer holidays after my GCSEs. I wanted to see how proficient I was with the language after also learning it over the summer.
I wanted to see if I could effectively use dynamic memory allocation, pointers and object - oriented programming, learning and knowing how to use these would help with my Computer Science A-Level.

The majority of the programming was done by me, however, some areas such as obscuring the password, and some of the file handling was done by me. 

# Login
The user details are contained within a class named "NewLoginDetails", utilising setters, getters and constructors to encapsulate/protect the username/password. In the function "login", the user makes the choice to either create an account, or log in into an account.

If the user decides to create a new account, they input a new username and password, where the password is obscured by stars for user safety. However, the passwords must have the conditions of having at least 8 characters, an uppercase character, a lowercase character, a number and a symbol, otherwise, the user must change their password. After these checks, a new object is created, using a pointer which was previously declared near the beginning of "login". Then, the username and password are passed as global variables, a .txt file with the username and password is created, and any memory is freed at the end.

If the user decides to login, the user inputs their username and password, which becomes stored as global variables. However, if the username is correct yet the password is incorrect, the username is set to "NULL" to prevent login.

# Balance
If there are any errors when opening the file, an error message will appear and end the program. Otherwise, 
