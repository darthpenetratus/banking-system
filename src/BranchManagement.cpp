#include "../include/BranchManagement.h"

// Constructor
BranchManagement::BranchManagement() : head(nullptr) {}

// Destructor
BranchManagement::~BranchManagement() {
    BranchNode* current = head;
    while (current != nullptr) {
        BranchNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool BranchManagement::isUniqueID(int branchID) {
    return usedIDs.find(branchID) == usedIDs.end();
}

void BranchManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Branch Management Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Create Branch\n";
        std::cout << "2. View Branch\n";
        std::cout << "3. Update Branch\n";
        std::cout << "4. Delete Branch\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                createBranch();
                break;
            case 2:
                viewBranch();
                break;
            case 3:
                updateBranch();
                break;
            case 4:
                deleteBranch();
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

void BranchManagement::createBranch() {
    int branchID, managerID;
    std::string location;
    do {
        std::cout << "Enter branch ID: ";
        std::cin >> branchID;
        if (!isUniqueID(branchID)) {
            std::cout << "Branch ID already in use. Please enter a different ID.\n";
        }
    } while (!isUniqueID(branchID));

    std::cout << "Enter location: ";
    std::cin.ignore();
    std::getline(std::cin, location);
    std::cout << "Enter manager ID: ";
    std::cin >> managerID;
    try {
        Branch newBranch(branchID, location, managerID);
        BranchNode* newNode = new BranchNode(newBranch);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(branchID);
        std::cout << "Branch created successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void BranchManagement::viewBranch() {
    int branchID;
    std::cout << "Enter branch ID: ";
    std::cin >> branchID;
    BranchNode* node = findBranchNode(branchID);
    if (node) {
        printBranch(node->branch);
    } else {
        std::cout << "Branch not found.\n";
    }
}

void BranchManagement::updateBranch() {
    int branchID, managerID;
    std::string location;
    std::cout << "Enter branch ID: ";
    std::cin >> branchID;
    BranchNode* node = findBranchNode(branchID);
    if (node) {
        std::cout << "Enter new location: ";
        std::cin.ignore();
        std::getline(std::cin, location);
        std::cout << "Enter new manager ID: ";
        std::cin >> managerID;
        try {
            node->branch.setLocation(location);
            node->branch.setManagerID(managerID);
            std::cout << "Branch updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Branch not found.\n";
    }
}

void BranchManagement::deleteBranch() {
    int branchID;
    std::cout << "Enter branch ID: ";
    std::cin >> branchID;
    BranchNode* prev = nullptr;
    BranchNode* current = head;
    while (current != nullptr && current->branch.getBranchID() != branchID) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        usedIDs.erase(branchID);
        delete current;
        std::cout << "Branch deleted successfully.\n";
    } else {
        std::cout << "Branch not found.\n";
    }
}

BranchNode* BranchManagement::findBranchNode(int branchID) {
    BranchNode* current = head;
    while (current != nullptr) {
        if (current->branch.getBranchID() == branchID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void BranchManagement::printBranch(const Branch& branch) {
    std::cout << "Branch ID: " << branch.getBranchID() << "\n";
    std::cout << "Location: " << branch.getLocation() << "\n";
    std::cout << "Manager ID: " << branch.getManagerID() << "\n";
}

void BranchManagement::saveBranches(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        BranchNode* current = head;
        while (current != nullptr) {
            file << current->branch.getBranchID() << ","
                 << current->branch.getLocation() << ","
                 << current->branch.getManagerID() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Branches saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void BranchManagement::loadBranches(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int branchID, managerID;
            std::string location;

            std::getline(ss, item, ',');
            branchID = std::stoi(item);
            std::getline(ss, location, ',');
            std::getline(ss, item, ',');
            managerID = std::stoi(item);

            Branch newBranch(branchID, location, managerID);
            BranchNode* newNode = new BranchNode(newBranch);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(branchID); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Branches loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}