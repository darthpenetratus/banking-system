#include "../include/BankingOperationManagement.h"

// Constructor
BankingOperationManagement::BankingOperationManagement() : head(nullptr) {}

// Destructor
BankingOperationManagement::~BankingOperationManagement() {
    BankingOperationNode* current = head;
    while (current != nullptr) {
        BankingOperationNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool BankingOperationManagement::isUniqueID(int operationID) {
    return usedIDs.find(operationID) == usedIDs.end();
}

void BankingOperationManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Banking Operation Management Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Create Operation\n";
        std::cout << "2. View Operation\n";
        std::cout << "3. Update Operation\n";
        std::cout << "4. Delete Operation\n";
        std::cout << "5. Save Operations\n";
        std::cout << "6. Load Operations\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                createOperation();
                break;
            case 2:
                viewOperation();
                break;
            case 3:
                updateOperation();
                break;
            case 4:
                deleteOperation();
                break;
            case 5:
                saveOperations("operations.txt");
                break;
            case 6:
                loadOperations("operations.txt");
                break;
            case 7:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);
}

void BankingOperationManagement::createOperation() {
    int operationID, employeeID;
    std::string description, date;
    do {
        std::cout << "Enter operation ID: ";
        std::cin >> operationID;
        if (!isUniqueID(operationID)) {
            std::cout << "Operation ID already in use. Please enter a different ID.\n";
        }
    } while (!isUniqueID(operationID));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Enter employee ID: ";
    std::cin >> employeeID;

    try {
        BankingOperation newOperation(operationID, description, date, employeeID);
        BankingOperationNode* newNode = new BankingOperationNode(newOperation);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(operationID);
        std::cout << "Operation created successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void BankingOperationManagement::viewOperation() {
    int operationID;
    std::cout << "Enter operation ID: ";
    std::cin >> operationID;
    BankingOperationNode* node = findOperationNode(operationID);
    if (node) {
        printOperation(node->operation);
    } else {
        std::cout << "Operation not found.\n";
    }
}

void BankingOperationManagement::updateOperation() {
    int operationID, employeeID;
    std::string description, date;
    std::cout << "Enter operation ID: ";
    std::cin >> operationID;
    BankingOperationNode* node = findOperationNode(operationID);
    if (node) {
        std::cout << "Enter new description: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        std::getline(std::cin, description);
        std::cout << "Enter new date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        std::cout << "Enter new employee ID: ";
        std::cin >> employeeID;
        try {
            node->operation.setDescription(description);
            node->operation.setDate(date);
            node->operation.setEmployeeID(employeeID);
            std::cout << "Operation updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Operation not found.\n";
    }
}

void BankingOperationManagement::deleteOperation() {
    int operationID;
    std::cout << "Enter operation ID: ";
    std::cin >> operationID;
    BankingOperationNode* prev = nullptr;
    BankingOperationNode* current = head;
    while (current != nullptr && current->operation.getOperationID() != operationID) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        usedIDs.erase(operationID);
        delete current;
        std::cout << "Operation deleted successfully.\n";
    } else {
        std::cout << "Operation not found.\n";
    }
}

BankingOperationNode* BankingOperationManagement::findOperationNode(int operationID) {
    BankingOperationNode* current = head;
    while (current != nullptr) {
        if (current->operation.getOperationID() == operationID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void BankingOperationManagement::printOperation(const BankingOperation& operation) {
    std::cout << "Operation ID: " << operation.getOperationID() << "\n";
    std::cout << "Description: " << operation.getDescription() << "\n";
    std::cout << "Date: " << operation.getDate() << "\n";
    std::cout << "Employee ID: " << operation.getEmployeeID() << "\n";
}

void BankingOperationManagement::saveOperations(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        BankingOperationNode* current = head;
        while (current != nullptr) {
            file << current->operation.getOperationID() << ","
                 << current->operation.getDescription() << ","
                 << current->operation.getDate() << ","
                 << current->operation.getEmployeeID() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Operations saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void BankingOperationManagement::loadOperations(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int operationID, employeeID;
            std::string description, date;

            std::getline(ss, item, ',');
            operationID = std::stoi(item);
            std::getline(ss, description, ',');
            std::getline(ss, date, ',');
            std::getline(ss, item, ',');
            employeeID = std::stoi(item);

            BankingOperation newOperation(operationID, description, date, employeeID);
            BankingOperationNode* newNode = new BankingOperationNode(newOperation);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(operationID); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Operations loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}