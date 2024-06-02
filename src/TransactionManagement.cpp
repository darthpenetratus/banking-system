#include "../include/TransactionManagement.h"

// Constructor
TransactionManagement::TransactionManagement() : head(nullptr) {}

// Destructor
TransactionManagement::~TransactionManagement() {
    TransactionNode* current = head;
    while (current != nullptr) {
        TransactionNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool TransactionManagement::isUniqueID(int transactionID) {
    return usedIDs.find(transactionID) == usedIDs.end();
}

void TransactionManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Transaction Processing Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Create Transaction\n";
        std::cout << "2. View Transaction\n";
        std::cout << "3. Update Transaction\n";
        std::cout << "4. Cancel Transaction\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                createTransaction();
                break;
            case 2:
                viewTransaction();
                break;
            case 3:
                updateTransaction();
                break;
            case 4:
                cancelTransaction();
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

void TransactionManagement::createTransaction() {
    int transactionID, senderAccount, recipientAccount;
    std::string date, purpose;
    float amount;
    do {
        std::cout << "Enter transaction ID: ";
        std::cin >> transactionID;
        if (!isUniqueID(transactionID)) {
            std::cout << "Transaction ID already in use. Please enter a different ID.\n";
        }
    } while (!isUniqueID(transactionID));

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter sender account number: ";
    std::cin >> senderAccount;
    std::cout << "Enter recipient account number: ";
    std::cin >> recipientAccount;
    std::cout << "Enter purpose: ";
    std::cin.ignore();
    std::getline(std::cin, purpose);
    std::cout << "Enter amount: ";
    std::cin >> amount;
    try {
        Transaction newTransaction(transactionID, date, senderAccount, recipientAccount, purpose, amount);
        TransactionNode* newNode = new TransactionNode(newTransaction);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(transactionID);
        std::cout << "Transaction created successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void TransactionManagement::viewTransaction() {
    int transactionID;
    std::cout << "Enter transaction ID: ";
    std::cin >> transactionID;
    TransactionNode* node = findTransactionNode(transactionID);
    if (node) {
        printTransaction(node->transaction);
    } else {
        std::cout << "Transaction not found.\n";
    }
}

void TransactionManagement::updateTransaction() {
    int transactionID, senderAccount, recipientAccount;
    std::string date, purpose;
    float amount;
    std::cout << "Enter transaction ID: ";
    std::cin >> transactionID;
    TransactionNode* node = findTransactionNode(transactionID);
    if (node) {
        std::cout << "Enter new date (YYYY-MM-DD): ";
        std::cin >> date;
        std::cout << "Enter new sender account number: ";
        std::cin >> senderAccount;
        std::cout << "Enter new recipient account number: ";
        std::cin >> recipientAccount;
        std::cout << "Enter new purpose: ";
        std::cin.ignore();
        std::getline(std::cin, purpose);
        std::cout << "Enter new amount: ";
        std::cin >> amount;
        try {
            node->transaction.setDate(date);
            node->transaction.setSenderAccount(senderAccount);
            node->transaction.setRecipientAccount(recipientAccount);
            node->transaction.setPurpose(purpose);
            node->transaction.setAmount(amount);
            std::cout << "Transaction updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Transaction not found.\n";
    }
}

void TransactionManagement::cancelTransaction() {
    int transactionID;
    std::cout << "Enter transaction ID: ";
    std::cin >> transactionID;
    TransactionNode* prev = nullptr;
    TransactionNode* current = head;
    while (current != nullptr && current->transaction.getTransactionID() != transactionID) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        usedIDs.erase(transactionID);
        delete current;
        std::cout << "Transaction cancelled successfully.\n";
    } else {
        std::cout << "Transaction not found.\n";
    }
}

TransactionNode* TransactionManagement::findTransactionNode(int transactionID) {
    TransactionNode* current = head;
    while (current != nullptr) {
        if (current->transaction.getTransactionID() == transactionID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void TransactionManagement::printTransaction(const Transaction& transaction) {
    std::cout << "Transaction ID: " << transaction.getTransactionID() << "\n";
    std::cout << "Date: " << transaction.getDate() << "\n";
    std::cout << "Sender Account: " << transaction.getSenderAccount() << "\n";
    std::cout << "Recipient Account: " << transaction.getRecipientAccount() << "\n";
    std::cout << "Purpose: " << transaction.getPurpose() << "\n";
    std::cout << "Amount: " << transaction.getAmount() << "\n";
}

void TransactionManagement::saveTransactions(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        TransactionNode* current = head;
        while (current != nullptr) {
            file << current->transaction.getTransactionID() << ","
                 << current->transaction.getDate() << ","
                 << current->transaction.getSenderAccount() << ","
                 << current->transaction.getRecipientAccount() << ","
                 << current->transaction.getPurpose() << ","
                 << current->transaction.getAmount() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Transactions saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void TransactionManagement::loadTransactions(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int transactionID, senderAccount, recipientAccount;
            std::string date, purpose;
            float amount;

            std::getline(ss, item, ',');
            transactionID = std::stoi(item);
            std::getline(ss, date, ',');
            std::getline(ss, item, ',');
            senderAccount = std::stoi(item);
            std::getline(ss, item, ',');
            recipientAccount = std::stoi(item);
            std::getline(ss, purpose, ',');
            std::getline(ss, item, ',');
            amount = std::stof(item);

            Transaction newTransaction(transactionID, date, senderAccount, recipientAccount, purpose, amount);
            TransactionNode* newNode = new TransactionNode(newTransaction);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(transactionID); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Transactions loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}