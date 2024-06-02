#include "Branch.h"
#include <regex>
#include <stdexcept>

// Constructor
Branch::Branch(int branchID, const std::string& location, int managerID)
    : branchID(branchID), location(location), managerID(managerID) {
    if (!isValidBranchID(branchID) || !isValidLocation(location) || !isValidManagerID(managerID)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int Branch::getBranchID() const {
    return branchID;
}

std::string Branch::getLocation() const {
    return location;
}

int Branch::getManagerID() const {
    return managerID;
}

// Setters
void Branch::setLocation(const std::string& location) {
    if (isValidLocation(location)) {
        this->location = location;
    }
}

void Branch::setManagerID(int managerID) {
    if (isValidManagerID(managerID)) {
        this->managerID = managerID;
    }
}

// Validation methods
bool Branch::isValidBranchID(int branchID) {
    return branchID > 0;
}

bool Branch::isValidLocation(const std::string& location) {
    std::regex locationRegex("^[A-Za-z\\- ]{1,150}$");
    return std::regex_match(location, locationRegex);
}

bool Branch::isValidManagerID(int managerID) {
    return managerID > 0;  // This should ideally check if the manager exists in the system
}