#include "../include/BankingOperation.h"
#include <regex>
#include <stdexcept>

// Constructor
BankingOperation::BankingOperation(int operationID, const std::string& description, const std::string& date, int employeeID)
    : operationID(operationID), description(description), date(date), employeeID(employeeID) {
    if (!isValidOperationID(operationID) || !isValidDescription(description) || !isValidDate(date) || !isValidEmployeeID(employeeID)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int BankingOperation::getOperationID() const {
    return operationID;
}

std::string BankingOperation::getDescription() const {
    return description;
}

std::string BankingOperation::getDate() const {
    return date;
}

int BankingOperation::getEmployeeID() const {
    return employeeID;
}

// Setters
void BankingOperation::setDescription(const std::string& description) {
    if (isValidDescription(description)) {
        this->description = description;
    }
}

void BankingOperation::setDate(const std::string& date) {
    if (isValidDate(date)) {
        this->date = date;
    }
}

void BankingOperation::setEmployeeID(int employeeID) {
    if (isValidEmployeeID(employeeID)) {
        this->employeeID = employeeID;
    }
}

// Validation methods
bool BankingOperation::isValidOperationID(int operationID) {
    return operationID > 0;
}

bool BankingOperation::isValidDescription(const std::string& description) {
    return description.size() <= 255;
}

bool BankingOperation::isValidDate(const std::string& date) {
    std::regex dateRegex("^\\d{4}-\\d{2}-\\d{2}$");
    return std::regex_match(date, dateRegex);
}

bool BankingOperation::isValidEmployeeID(int employeeID) {
    return employeeID > 0;
}