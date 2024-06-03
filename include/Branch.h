#ifndef BRANCH_H
#define BRANCH_H

#include <string>

class Branch {
public:
    Branch(int branchID, const std::string& location, int managerID);

    // Getters
    int getBranchID() const;
    std::string getLocation() const;
    int getManagerID() const;

    // Setters
    void setLocation(const std::string& location);
    void setManagerID(int managerID);

    // Validation
    static bool isValidBranchID(int branchID);
    static bool isValidLocation(const std::string& location);
    static bool isValidManagerID(int managerID);

private:
    int branchID;
    std::string location;
    int managerID;
};

#endif