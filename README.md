# Banking System Application

## Overview

The Banking System application is a console-based program designed to manage various banking-related entities such as accounts, employees, transactions, banking operations, branches, and clients. The application allows users to perform CRUD (Create, Read, Update, Delete) operations on these entities, save and load data from files, and perform searches and sorts.

## Features

- **Account Management**: Create, view, update, delete, search, sort, and calculate balances.
- **Employee Management**: Add, view, update, delete, save, and load employee data.
- **Transaction Management**: Create, view, update, delete, save, and load transaction data.
- **Banking Operation Management**: Create, view, update, delete, save, and load banking operation data.
- **Branch Management**: Create, view, update, delete, save, and load branch data.
- **Client Management**: Create, view, update, delete, save, and load client data.

## Prerequisites

Ensure you have a C++ compiler installed on your system:
- For Windows: [MinGW](http://www.mingw.org/)
- For macOS: [Xcode Command Line Tools](https://developer.apple.com/xcode/features/)

## Directory Structure

```
banking-system/
├── include/
│   ├── Account.h
│   ├── AccountNode.h
│   ├── AccountManagement.h
│   ├── Employee.h
│   ├── EmployeeNode.h
│   ├── EmployeeManagement.h
│   ├── Transaction.h
│   ├── TransactionNode.h
│   ├── TransactionManagement.h
│   ├── BankingOperation.h
│   ├── BankingOperationNode.h
│   ├── BankingOperationManagement.h
│   ├── Branch.h
│   ├── BranchNode.h
│   ├── BranchManagement.h
│   ├── Client.h
│   ├── ClientNode.h
│   ├── ClientManagement.h
├── src/
│   ├── Account.cpp
│   ├── AccountManagement.cpp
│   ├── Employee.cpp
│   ├── EmployeeManagement.cpp
│   ├── Transaction.cpp
│   ├── TransactionManagement.cpp
│   ├── BankingOperation.cpp
│   ├── BankingOperationManagement.cpp
│   ├── Branch.cpp
│   ├── BranchManagement.cpp
│   ├── Client.cpp
│   ├── ClientManagement.cpp
│   ├── main.cpp
├── data/
│   ├── accounts.txt
│   ├── employees.txt
│   ├── transactions.txt
│   ├── operations.txt
│   ├── branches.txt
│   ├── clients.txt
└── README.md
```

## How to Compile and Run

### On Windows

1. **Install MinGW**:
   Download and install MinGW from [MinGW](http://www.mingw.org/). Ensure to install `mingw32-gcc-g++` during setup.

2. **Compile the Program**:
   Open the Command Prompt and navigate to the project directory. Run the following commands:

   ```sh
   cd /path/to/your/project/directory
   g++ -Iinclude -o banking_system src/*.cpp

3. **Run the Program**:
   Execute the compiled program:

   ```sh
   banking_system.exe

### On macOS

1. **Install Xcode Command Line Tools**:
   Open Terminal and run:
   ```sh
   xcode-select --install

2. **Compile the Program**:
   Navigate to the project directory in Terminal and run the following commands:

   ```sh
   cd /path/to/your/project/directory
   g++ -Iinclude -o banking_system src/*.cpp

3. **Run the Program**:
   Execute the compiled program:

   ```sh
   ./banking_system

### Usage

When you run the application, you will be presented with the main menu. Follow the prompts to manage different entities.

Main Menu

```
-------------------------------
  Main Menu
-------------------------------
1. Account Management
2. Employee Management
3. Transaction Management
4. Banking Operation Management
5. Branch Management
6. Client Management
7. Exit
-------------------------------
Choose an option:
```

Select an option to navigate to the respective management menu and perform desired operations.