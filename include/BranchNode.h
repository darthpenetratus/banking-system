#ifndef BRANCHNODE_H
#define BRANCHNODE_H

#include "Branch.h"

struct BranchNode {
    Branch branch;
    BranchNode* next;

    BranchNode(const Branch& branch) : branch(branch), next(nullptr) {}
};

#endif