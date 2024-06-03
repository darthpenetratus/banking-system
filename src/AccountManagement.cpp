#include "../include/AccountManagement.h"
#include <algorithm>

// Constructor
AccountManagement::AccountManagement() : head(nullptr) {}

// Destructor
AccountManagement::~AccountManagement() {
    AccountNode* current = head;
    while (current != nullptr) {
        AccountNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool AccountManagement::isUniqueID(int accountNumber) {
    return usedIDs.find(accountNumber) == usedIDs.end();
}

AccountNode* AccountManagement::findAccountNode(int accountNumber) {
    AccountNode* current = head;
    while (current != nullptr) {
        if (current->account.getAccountNumber() == accountNumber) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void AccountManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Account Management Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. View Account\n";
        std::cout << "3. Update Account\n";
        std::cout << "4. Delete Account\n";
        std::cout << "5. Search Accounts\n";
        std::cout << "6. Sort Accounts\n";
        std::cout << "7. Calculate Total Balance\n";
        std::cout << "8. Calculate Average Balance\n";
        std::cout << "9. Calculate Highest Balance\n";
        std::cout << "10. Save Accounts\n";
        std::cout << "11. Load Accounts\n";
        std::cout << "12. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                updateAccount();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                searchAccounts();
                break;
            case 6:
                sortAccounts();
                break;
            case 7:
                calculateTotalBalance();
                break;
            case 8:
                calculateAverageBalance();
                break;
            case 9:
                calculateHighestBalance();
                break;
            case 10:
                saveAccounts("accounts.txt");
                break;
            case 11:
                loadAccounts("accounts.txt");
                break;
            case 12:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 12);
}

void AccountManagement::createAccount() {
    int accountNumber;
    std::string owner, type, currency;
    float balance;
    do {
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        if (!isUniqueID(accountNumber)) {
            std::cout << "Account number already in use. Please enter a different number.\n";
        }
    } while (!isUniqueID(accountNumber));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    std::cout << "Enter owner: ";
    std::getline(std::cin, owner);

    std::cout << "Enter type (Savings/Checking/Business): ";
    std::getline(std::cin, type);

    std::cout << "Enter currency (USD/EUR/GBP): ";
    std::getline(std::cin, currency);

    std::cout << "Enter balance: ";
    std::cin >> balance;

    try {
        Account newAccount(accountNumber, owner, type, currency, balance);
        AccountNode* newNode = new AccountNode(newAccount);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(accountNumber);
        std::cout << "Account created successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void AccountManagement::viewAccount() {
    int accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    AccountNode* node = findAccountNode(accountNumber);
    if (node) {
        printAccount(node->account);
    } else {
        std::cout << "Account not found.\n";
    }
}

void AccountManagement::updateAccount() {
    int accountNumber;
    std::string owner, type, currency;
    float balance;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    AccountNode* node = findAccountNode(accountNumber);
    if (node) {
        std::cout << "Enter new owner: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        std::getline(std::cin, owner);
        std::cout << "Enter new type (Savings/Checking/Business): ";
        std::getline(std::cin, type);
        std::cout << "Enter new currency (USD/EUR/GBP): ";
        std::getline(std::cin, currency);
        std::cout << "Enter new balance: ";
        std::cin >> balance;
        try {
            node->account.setOwner(owner);
            node->account.setType(type);
            node->account.setCurrency(currency);
            node->account.setBalance(balance);
            std::cout << "Account updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Account not found.\n";
    }
}

void AccountManagement::deleteAccount() {
    int choice;
    std::cout << "Delete by: 1. Account Number 2. Owner 3. Balance\n";
    std::cin >> choice;

    if (choice == 1) {
        int accountNumber;
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        AccountNode* prev = nullptr;
        AccountNode* current = head;
        while (current != nullptr && current->account.getAccountNumber() != accountNumber) {
            prev = current;
            current = current->next;
        }
        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            usedIDs.erase(accountNumber);
            delete current;
            std::cout << "Account deleted successfully.\n";
        } else {
            std::cout << "Account not found.\n";
        }
    } else if (choice == 2) {
        std::string owner;
        std::cout << "Enter owner: ";
        std::cin.ignore();
        std::getline(std::cin, owner);
        AccountNode* prev = nullptr;
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->account.getOwner() == owner) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                usedIDs.erase(current->account.getAccountNumber());
                delete current;
                std::cout << "Account deleted successfully.\n";
                break;
            }
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Account not found.\n";
        }
    } else if (choice == 3) {
        float balance;
        std::cout << "Enter balance: ";
        std::cin >> balance;
        AccountNode* prev = nullptr;
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->account.getBalance() == balance) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                usedIDs.erase(current->account.getAccountNumber());
                delete current;
                std::cout << "Account deleted successfully.\n";
                break;
            }
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Account not found.\n";
        }
    }
}

void AccountManagement::searchAccounts() {
    int choice;
    std::cout << "Search by: 1. Account Number 2. Owner 3. Balance\n";
    std::cin >> choice;

    if (choice == 1) {
        int accountNumber;
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->account.getAccountNumber() == accountNumber) {
                printAccount(current->account);
                return;
            }
            current = current->next;
        }
        std::cout << "Account not found.\n";
    } else if (choice == 2) {
        std::string owner;
        std::cout << "Enter owner: ";
        std::cin.ignore();
        std::getline(std::cin, owner);
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->account.getOwner() == owner) {
                printAccount(current->account);
                return;
            }
            current = current->next;
        }
        std::cout << "Account not found.\n";
    } else if (choice == 3) {
        float balance;
        std::cout << "Enter balance: ";
        std::cin >> balance;
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->account.getBalance() == balance) {
                printAccount(current->account);
                return;
            }
            current = current->next;
        }
        std::cout << "Account not found.\n";
    }
}

void AccountManagement::sortAccounts() {
    int choice;
    std::cout << "Sort by: 1. Account Number 2. Owner 3. Balance\n";
    std::cin >> choice;

    // Convert linked list to array for easier sorting
    int count = 0;
    AccountNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    Account** accounts = new Account*[count];
    current = head;
    for (int i = 0; i < count; i++) {
        accounts[i] = &current->account;
        current = current->next;
    }

    if (choice == 1) {
        std::sort(accounts, accounts + count, [](Account* a, Account* b) {
            return a->getAccountNumber() < b->getAccountNumber();
        });
    } else if (choice == 2) {
        std::sort(accounts, accounts + count, [](Account* a, Account* b) {
            return a->getOwner() < b->getOwner();
        });
    } else if (choice == 3) {
        std::sort(accounts, accounts + count, [](Account* a, Account* b) {
            return a->getBalance() < b->getBalance();
        });
    }

    std::cout << "Sorted Accounts:\n";
    for (int i = 0; i < count; i++) {
        printAccount(*accounts[i]);
    }

    delete[] accounts;
}

void AccountManagement::calculateTotalBalance() {
    float totalBalance = 0.0;
    AccountNode* current = head;
    while (current != nullptr) {
        totalBalance += current->account.getBalance();
        current = current->next;
    }
    std::cout << "Total Balance: " << totalBalance << "\n";
}

void AccountManagement::calculateAverageBalance() {
    float totalBalance = 0.0;
    int count = 0;
    AccountNode* current = head;
    while (current != nullptr) {
        totalBalance += current->account.getBalance();
        count++;
        current = current->next;
    }
    std::cout << "Average Balance: " << (totalBalance / count) << "\n";
}

void AccountManagement::calculateHighestBalance() {
    float highestBalance = 0.0;
    AccountNode* current = head;
    while (current != nullptr) {
        if (current->account.getBalance() > highestBalance) {
            highestBalance = current->account.getBalance();
        }
        current = current->next;
    }
    std::cout << "Highest Balance: " << highestBalance << "\n";
}

void AccountManagement::printAccount(const Account& account) {
    std::cout << std::left << std::setw(15) << "Account Number"
              << std::setw(25) << "Owner"
              << std::setw(15) << "Type"
              << std::setw(10) << "Currency"
              << std::setw(10) << "Balance" << "\n";
    std::cout << std::left << std::setw(15) << account.getAccountNumber()
              << std::setw(25) << account.getOwner()
              << std::setw(15) << account.getType()
              << std::setw(10) << account.getCurrency()
              << std::setw(10) << account.getBalance() << "\n";
}

void AccountManagement::saveAccounts(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        AccountNode* current = head;
        while (current != nullptr) {
            file << current->account.getAccountNumber() << ","
                 << current->account.getOwner() << ","
                 << current->account.getType() << ","
                 << current->account.getCurrency() << ","
                 << current->account.getBalance() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Accounts saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void AccountManagement::loadAccounts(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int accountNumber;
            std::string owner, type, currency;
            float balance;

            std::getline(ss, item, ',');
            accountNumber = std::stoi(item);
            std::getline(ss, owner, ',');
            std::getline(ss, type, ',');
            std::getline(ss, currency, ',');
            std::getline(ss, item, ',');
            balance = std::stof(item);

            Account newAccount(accountNumber, owner, type, currency, balance);
            AccountNode* newNode = new AccountNode(newAccount);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(accountNumber); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Accounts loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}