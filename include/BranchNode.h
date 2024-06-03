#ifndef BRANCHNODE_H
#define BRANCHNODE_H

#include "Branch.h"

struct BranchNode {
    Branch branch;
    BranchNode* next;

    BranchNode(const Branch& br) : branch(br), next(nullptr) {}
};

#endif