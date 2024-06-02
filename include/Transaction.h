#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    Transaction(int transactionID, const std::string& date, int senderAccount, int recipientAccount, const std::string& purpose, float amount);
    
    // Getters
    int getTransactionID() const;
    std::string getDate() const;
    int getSenderAccount() const;
    int getRecipientAccount() const;
    std::string getPurpose() const;
    float getAmount() const;
    
    // Setters
    void setDate(const std::string& date);
    void setSenderAccount(int senderAccount);
    void setRecipientAccount(int recipientAccount);
    void setPurpose(const std::string& purpose);
    void setAmount(float amount);
    
    // Validation
    static bool isValidTransactionID(int transactionID);
    static bool isValidDate(const std::string& date);
    static bool isValidAccount(int accountNumber);
    static bool isValidAmount(float amount);

private:
    int transactionID;
    std::string date;
    int senderAccount;
    int recipientAccount;
    std::string purpose;
    float amount;
};

#endif