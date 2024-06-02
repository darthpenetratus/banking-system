#ifndef TRANSACTIONNODE_H
#define TRANSACTIONNODE_H

#include "Transaction.h"

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;

    TransactionNode(const Transaction& transaction) : transaction(transaction), next(nullptr) {}
};

#endif