#ifndef BANKINGOPERATIONMANAGEMENT_H
#define BANKINGOPERATIONMANAGEMENT_H

#include "BankingOperation.h"
#include "BankingOperationNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>
#include <iomanip>

class BankingOperationManagement {
public:
    BankingOperationManagement();
    ~BankingOperationManagement();

    void manage();
    void createOperation();
    void viewOperation();
    void updateOperation();
    void deleteOperation();
    void saveOperations(const std::string& filename);
    void loadOperations(const std::string& filename);

private:
    BankingOperationNode* head;
    std::set<int> usedIDs;

    BankingOperationNode* findOperationNode(int operationID);
    void printOperation(const BankingOperation& operation);
    bool isUniqueID(int operationID);
};

#endif