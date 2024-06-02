#include <iostream>
#include "../include/AccountManagement.h"
#include "../include/TransactionManagement.h"
#include "../include/BankingOperationManagement.h"
#include "../include/BranchManagement.h"
#include "../include/EmployeeManagement.h"
#include "../include/ClientManagement.h"

#include <unistd.h> // For getcwd() on Unix-like systems
#include <limits.h> // For PATH_MAX

void showMainMenu() {
    std::cout << "\n-------------------------------\n";
    std::cout << "  Banking System Main Menu\n";
    std::cout << "-------------------------------\n";
    std::cout << "1. Account Management\n";
    std::cout << "2. Transaction Processing\n";
    std::cout << "3. Banking Operations Management\n";
    std::cout << "4. Branch Management\n";
    std::cout << "5. Employee Management\n";
    std::cout << "6. Client Management\n";
    std::cout << "7. Exit\n";
    std::cout << "-------------------------------\n";
    std::cout << "Choose an option: ";
}

int main() {
    // Print the current working directory
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << "\n" << std::endl;
    } else {
        perror("getcwd() error");
    }

    AccountManagement accountManagement;
    TransactionManagement transactionManagement;
    BankingOperationManagement bankingOperationManagement;
    BranchManagement branchManagement;
    EmployeeManagement employeeManagement;
    ClientManagement clientManagement;

    // Load data at startup
    accountManagement.loadAccounts("data/accounts.txt");
    transactionManagement.loadTransactions("data/transactions.txt");
    bankingOperationManagement.loadOperations("data/operations.txt");
    branchManagement.loadBranches("data/branches.txt");
    employeeManagement.loadEmployees("data/employees.txt");
    clientManagement.loadClients("data/clients.txt");

    int choice;
    do {
        showMainMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                accountManagement.manage();
                break;
            case 2:
                transactionManagement.manage();
                break;
            case 3:
                bankingOperationManagement.manage();
                break;
            case 4:
                branchManagement.manage();
                break;
            case 5:
                employeeManagement.manage();
                break;
            case 6:
                clientManagement.manage();
                break;
            case 7:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    // Save data before exiting
    accountManagement.saveAccounts("data/accounts.txt");
    transactionManagement.saveTransactions("data/transactions.txt");
    bankingOperationManagement.saveOperations("data/operations.txt");
    branchManagement.saveBranches("data/branches.txt");
    employeeManagement.saveEmployees("data/employees.txt");
    clientManagement.saveClients("data/clients.txt");

    return 0;
}