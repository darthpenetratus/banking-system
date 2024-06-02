#include "../include/AccountManagement.h"

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
        std::cout << "5. Back to Main Menu\n";
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
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);
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
    
    std::cout << "Enter owner: ";
    std::cin.ignore();
    std::getline(std::cin, owner);
    std::cout << "Enter type (Savings/Checking/Business): ";
    std::cin >> type;
    std::cout << "Enter currency (USD/EUR/GBP): ";
    std::cin >> currency;
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
        std::cin.ignore();
        std::getline(std::cin, owner);
        std::cout << "Enter new type (Savings/Checking/Business): ";
        std::cin >> type;
        std::cout << "Enter new currency (USD/EUR/GBP): ";
        std::cin >> currency;
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

void AccountManagement::printAccount(const Account& account) {
    std::cout << "Account Number: " << account.getAccountNumber() << "\n";
    std::cout << "Owner: " << account.getOwner() << "\n";
    std::cout << "Type: " << account.getType() << "\n";
    std::cout << "Currency: " << account.getCurrency() << "\n";
    std::cout << "Balance: " << account.getBalance() << "\n";
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