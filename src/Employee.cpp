#include "Employee.h"
#include <regex>
#include <stdexcept>

// Constructor
Employee::Employee(int employeeID, const std::string& name, const std::string& position, int branchID)
    : employeeID(employeeID), name(name), position(position), branchID(branchID) {
    if (!isValidEmployeeID(employeeID) || !isValidName(name) || !isValidPosition(position) || !isValidBranchID(branchID)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int Employee::getEmployeeID() const {
    return employeeID;
}

std::string Employee::getName() const {
    return name;
}

std::string Employee::getPosition() const {
    return position;
}

int Employee::getBranchID() const {
    return branchID;
}

// Setters
void Employee::setName(const std::string& name) {
    if (isValidName(name)) {
        this->name = name;
    }
}

void Employee::setPosition(const std::string& position) {
    if (isValidPosition(position)) {
        this->position = position;
    }
}

void Employee::setBranchID(int branchID) {
    if (isValidBranchID(branchID)) {
        this->branchID = branchID;
    }
}

// Validation methods
bool Employee::isValidEmployeeID(int employeeID) {
    return employeeID > 0;
}

bool Employee::isValidName(const std::string& name) {
    std::regex nameRegex("^[A-Za-z\\- ]{1,100}$");
    return std::regex_match(name, nameRegex);
}

bool Employee::isValidPosition(const std::string& position) {
    std::regex positionRegex("^[A-Za-z\\- ]{1,50}$");
    return std::regex_match(position, positionRegex);
}

bool Employee::isValidBranchID(int branchID) {
    return branchID > 0;
}