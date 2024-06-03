#include "../include/Account.h"
#include <regex>
#include <stdexcept>

// Constructor
Account::Account(int accountNumber, const std::string& owner, const std::string& type, const std::string& currency, float balance)
    : accountNumber(accountNumber), owner(owner), type(type), currency(currency), balance(balance) {
    if (!isValidAccountNumber(accountNumber) || !isValidOwner(owner) || !isValidType(type) || !isValidCurrency(currency) || !isValidBalance(balance)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getOwner() const {
    return owner;
}

std::string Account::getType() const {
    return type;
}

std::string Account::getCurrency() const {
    return currency;
}

float Account::getBalance() const {
    return balance;
}

// Setters
void Account::setOwner(const std::string& owner) {
    if (isValidOwner(owner)) {
        this->owner = owner;
    }
}

void Account::setType(const std::string& type) {
    if (isValidType(type)) {
        this->type = type;
    }
}

void Account::setCurrency(const std::string& currency) {
    if (isValidCurrency(currency)) {
        this->currency = currency;
    }
}

void Account::setBalance(float balance) {
    if (isValidBalance(balance)) {
        this->balance = balance;
    }
}

// Validation methods
bool Account::isValidAccountNumber(int accountNumber) {
    return accountNumber > 0;
}

bool Account::isValidOwner(const std::string& owner) {
    std::regex ownerRegex("^[A-Za-z\\- ]{1,100}$");
    return std::regex_match(owner, ownerRegex);
}

bool Account::isValidType(const std::string& type) {
    return type == "Savings" || type == "Checking" || type == "Business";
}

bool Account::isValidCurrency(const std::string& currency) {
    return currency == "USD" || currency == "EUR" || currency == "GBP";
}

bool Account::isValidBalance(float balance) {
    return balance >= 0.0;
}
