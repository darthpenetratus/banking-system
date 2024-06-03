#ifndef BANKINGOPERATIONNODE_H
#define BANKINGOPERATIONNODE_H

#include "BankingOperation.h"

struct BankingOperationNode {
    BankingOperation operation;
    BankingOperationNode* next;

    BankingOperationNode(const BankingOperation& op) : operation(op), next(nullptr) {}
};

#endif