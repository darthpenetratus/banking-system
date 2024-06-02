#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include "Account.h"

struct AccountNode {
    Account account;
    AccountNode* next;

    AccountNode(const Account& account) : account(account), next(nullptr) {}
};

#endif
