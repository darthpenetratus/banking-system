#ifndef BRANCHMANAGEMENT_H
#define BRANCHMANAGEMENT_H

#include "Branch.h"
#include "BranchNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

class BranchManagement {
public:
    BranchManagement();
    ~BranchManagement();
    
    void manage();
    void createBranch();
    void viewBranch();
    void updateBranch();
    void deleteBranch();
    void saveBranches(const std::string& filename);
    void loadBranches(const std::string& filename);

private:
    BranchNode* head;
    std::set<int> usedIDs;

    BranchNode* findBranchNode(int branchID);
    void printBranch(const Branch& branch);
    bool isUniqueID(int branchID);
};

#endif