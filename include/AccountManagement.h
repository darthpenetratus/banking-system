#ifndef ACCOUNTMANAGEMENT_H
#define ACCOUNTMANAGEMENT_H

#include "Account.h"
#include "AccountNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>
#include <iomanip>

class AccountManagement {
public:
    AccountManagement();
    ~AccountManagement();

    void manage();
    void createAccount();
    void viewAccount();
    void updateAccount();
    void deleteAccount();
    void searchAccounts();
    void sortAccounts();
    void calculateTotalBalance();
    void calculateAverageBalance();
    void calculateHighestBalance();
    void saveAccounts(const std::string& filename);
    void loadAccounts(const std::string& filename);

private:
    AccountNode* head;
    std::set<int> usedIDs;

    AccountNode* findAccountNode(int accountNumber);
    void printAccount(const Account& account);
    bool isUniqueID(int accountNumber);
};

#endif