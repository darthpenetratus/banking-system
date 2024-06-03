#ifndef TRANSACTIONNODE_H
#define TRANSACTIONNODE_H

#include "Transaction.h"

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;

    TransactionNode(const Transaction& trans) : transaction(trans), next(nullptr) {}
};

#endif