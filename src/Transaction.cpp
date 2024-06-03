#include "../include/Transaction.h"
#include <regex>
#include <stdexcept>

// Constructor
Transaction::Transaction(int transactionID, const std::string& date, int senderAccount, int recipientAccount, const std::string& purpose, float amount)
    : transactionID(transactionID), date(date), senderAccount(senderAccount), recipientAccount(recipientAccount), purpose(purpose), amount(amount) {
    if (!isValidTransactionID(transactionID) || !isValidDate(date) || !isValidAccount(senderAccount) || !isValidAccount(recipientAccount) || !isValidAmount(amount)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int Transaction::getTransactionID() const {
    return transactionID;
}

std::string Transaction::getDate() const {
    return date;
}

int Transaction::getSenderAccount() const {
    return senderAccount;
}

int Transaction::getRecipientAccount() const {
    return recipientAccount;
}

std::string Transaction::getPurpose() const {
    return purpose;
}

float Transaction::getAmount() const {
    return amount;
}

// Setters
void Transaction::setDate(const std::string& date) {
    if (isValidDate(date)) {
        this->date = date;
    }
}

void Transaction::setSenderAccount(int senderAccount) {
    if (isValidAccount(senderAccount)) {
        this->senderAccount = senderAccount;
    }
}

void Transaction::setRecipientAccount(int recipientAccount) {
    if (isValidAccount(recipientAccount)) {
        this->recipientAccount = recipientAccount;
    }
}

void Transaction::setPurpose(const std::string& purpose) {
    this->purpose = purpose;
}

void Transaction::setAmount(float amount) {
    if (isValidAmount(amount)) {
        this->amount = amount;
    }
}

// Validation methods
bool Transaction::isValidTransactionID(int transactionID) {
    return transactionID > 0;
}

bool Transaction::isValidDate(const std::string& date) {
    std::regex dateRegex("^\\d{4}-\\d{2}-\\d{2}$");
    return std::regex_match(date, dateRegex);
}

bool Transaction::isValidAccount(int accountNumber) {
    return accountNumber > 0;
}

bool Transaction::isValidAmount(float amount) {
    return amount > 0.0;
}