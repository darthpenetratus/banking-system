#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include "Account.h"

struct AccountNode {
    Account account;
    AccountNode* next;

    AccountNode(const Account& acc) : account(acc), next(nullptr) {}
};

#endif