#ifndef TRANSACTIONMANAGEMENT_H
#define TRANSACTIONMANAGEMENT_H

#include "Transaction.h"
#include "TransactionNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>
#include <iomanip>

class TransactionManagement {
public:
    TransactionManagement();
    ~TransactionManagement();

    void manage();
    void createTransaction();
    void viewTransaction();
    void updateTransaction();
    void deleteTransaction();
    void saveTransactions(const std::string& filename);
    void loadTransactions(const std::string& filename);

private:
    TransactionNode* head;
    std::set<int> usedIDs;

    TransactionNode* findTransactionNode(int transactionID);
    void printTransaction(const Transaction& transaction);
    bool isUniqueID(int transactionID);
};

#endif