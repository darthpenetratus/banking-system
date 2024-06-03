#include "../include/EmployeeManagement.h"

// Constructor
EmployeeManagement::EmployeeManagement() : head(nullptr) {}

// Destructor
EmployeeManagement::~EmployeeManagement() {
    EmployeeNode* current = head;
    while (current != nullptr) {
        EmployeeNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool EmployeeManagement::isUniqueID(int employeeID) {
    return usedIDs.find(employeeID) == usedIDs.end();
}

void EmployeeManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Employee Management Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. View Employee\n";
        std::cout << "3. Update Employee\n";
        std::cout << "4. Remove Employee\n";
        std::cout << "5. Save Employees\n";
        std::cout << "6. Load Employees\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                viewEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                removeEmployee();
                break;
            case 5:
                saveEmployees("employees.txt");
                break;
            case 6:
                loadEmployees("employees.txt");
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

void EmployeeManagement::addEmployee() {
    int employeeID, branchID;
    std::string name, position;
    do {
        std::cout << "Enter employee ID: ";
        std::cin >> employeeID;
        if (!isUniqueID(employeeID)) {
            std::cout << "Employee ID already in use. Please enter a different ID.\n";
        }
    } while (!isUniqueID(employeeID));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter position: ";
    std::getline(std::cin, position);

    std::cout << "Enter branch ID: ";
    std::cin >> branchID;

    try {
        Employee newEmployee(employeeID, name, position, branchID);
        EmployeeNode* newNode = new EmployeeNode(newEmployee);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(employeeID);
        std::cout << "Employee added successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void EmployeeManagement::viewEmployee() {
    int employeeID;
    std::cout << "Enter employee ID: ";
    std::cin >> employeeID;
    EmployeeNode* node = findEmployeeNode(employeeID);
    if (node) {
        printEmployee(node->employee);
    } else {
        std::cout << "Employee not found.\n";
    }
}

void EmployeeManagement::updateEmployee() {
    int employeeID, branchID;
    std::string name, position;
    std::cout << "Enter employee ID: ";
    std::cin >> employeeID;
    EmployeeNode* node = findEmployeeNode(employeeID);
    if (node) {
        std::cout << "Enter new name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        std::getline(std::cin, name);
        std::cout << "Enter new position: ";
        std::getline(std::cin, position);
        std::cout << "Enter new branch ID: ";
        std::cin >> branchID;
        try {
            node->employee.setName(name);
            node->employee.setPosition(position);
            node->employee.setBranchID(branchID);
            std::cout << "Employee updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Employee not found.\n";
    }
}

void EmployeeManagement::removeEmployee() {
    int employeeID;
    std::cout << "Enter employee ID: ";
    std::cin >> employeeID;
    EmployeeNode* prev = nullptr;
    EmployeeNode* current = head;
    while (current != nullptr && current->employee.getEmployeeID() != employeeID) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        usedIDs.erase(employeeID);
        delete current;
        std::cout << "Employee removed successfully.\n";
    } else {
        std::cout << "Employee not found.\n";
    }
}

EmployeeNode* EmployeeManagement::findEmployeeNode(int employeeID) {
    EmployeeNode* current = head;
    while (current != nullptr) {
        if (current->employee.getEmployeeID() == employeeID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void EmployeeManagement::printEmployee(const Employee& employee) {
    std::cout << "Employee ID: " << employee.getEmployeeID() << "\n";
    std::cout << "Name: " << employee.getName() << "\n";
    std::cout << "Position: " << employee.getPosition() << "\n";
    std::cout << "Branch ID: " << employee.getBranchID() << "\n";
}

void EmployeeManagement::saveEmployees(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        EmployeeNode* current = head;
        while (current != nullptr) {
            file << current->employee.getEmployeeID() << ","
                 << current->employee.getName() << ","
                 << current->employee.getPosition() << ","
                 << current->employee.getBranchID() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Employees saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void EmployeeManagement::loadEmployees(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int employeeID, branchID;
            std::string name, position;

            std::getline(ss, item, ',');
            employeeID = std::stoi(item);
            std::getline(ss, name, ',');
            std::getline(ss, position, ',');
            std::getline(ss, item, ',');
            branchID = std::stoi(item);

            Employee newEmployee(employeeID, name, position, branchID);
            EmployeeNode* newNode = new EmployeeNode(newEmployee);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(employeeID); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Employees loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}