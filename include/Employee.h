#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
public:
    Employee(int employeeID, const std::string& name, const std::string& position, int branchID);
    
    // Getters
    int getEmployeeID() const;
    std::string getName() const;
    std::string getPosition() const;
    int getBranchID() const;
    
    // Setters
    void setName(const std::string& name);
    void setPosition(const std::string& position);
    void setBranchID(int branchID);
    
    // Validation
    static bool isValidEmployeeID(int employeeID);
    static bool isValidName(const std::string& name);
    static bool isValidPosition(const std::string& position);
    static bool isValidBranchID(int branchID);

private:
    int employeeID;
    std::string name;
    std::string position;
    int branchID;
};

#endif