\# Bank System (C++)



A console application for managing bank clients, written in C++. Client data is stored in a text file, so it stays saved between runs.



!\[Main menu](images/screenshot.png)



\## Features



\- Show all clients in a formatted table

\- Add new clients, with a check that prevents duplicate account numbers

\- Delete a client, with confirmation

\- Update a client's information, with confirmation

\- Find a client by account number

\- Transactions menu:

&#x20; - Deposit

&#x20; - Withdraw, with a check that prevents withdrawing more than the balance

&#x20; - Total balances of all clients



\## How Data Is Stored



Clients are saved in `ClientFile.txt`, one client per line. The fields are separated by `#//#`:



```

AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance

```



The file in this repository contains sample data for testing.



\## How to Run



1\. Clone the repository:

```

&#x20;  git clone https://github.com/afara-ahmad/bank-system-cpp.git

```

2\. Open `Project\_Course7.sln` in Visual Studio

3\. Press `Ctrl + F5` to build and run



This project runs on Windows, because it uses Windows console commands.



\## What I Practiced



\- Reading from and writing to files with `fstream`

\- Vectors of structs

\- Splitting and joining strings to convert between records and file lines

\- Menus built with enums and switch statements

\- Organizing a larger program into many small functions



\## Author



Ahmad Afara

