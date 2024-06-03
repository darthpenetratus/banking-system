#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    Account(int accountNumber, const std::string& owner, const std::string& type, const std::string& currency, float balance);

    // Getters
    int getAccountNumber() const;
    std::string getOwner() const;
    std::string getType() const;
    std::string getCurrency() const;
    float getBalance() const;

    // Setters
    void setOwner(const std::string& owner);
    void setType(const std::string& type);
    void setCurrency(const std::string& currency);
    void setBalance(float balance);

    // Validation
    static bool isValidAccountNumber(int accountNumber);
    static bool isValidOwner(const std::string& owner);
    static bool isValidType(const std::string& type);
    static bool isValidCurrency(const std::string& currency);
    static bool isValidBalance(float balance);

private:
    int accountNumber;
    std::string owner;
    std::string type;
    std::string currency;
    float balance;
};

#endif