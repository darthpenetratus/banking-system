#ifndef EMPLOYEEMANAGEMENT_H
#define EMPLOYEEMANAGEMENT_H

#include "Employee.h"
#include "EmployeeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>
#include <iomanip>

class EmployeeManagement {
public:
    EmployeeManagement();
    ~EmployeeManagement();

    void manage();
    void addEmployee();
    void viewEmployee();
    void updateEmployee();
    void removeEmployee();
    void saveEmployees(const std::string& filename);
    void loadEmployees(const std::string& filename);

private:
    EmployeeNode* head;
    std::set<int> usedIDs;

    EmployeeNode* findEmployeeNode(int employeeID);
    void printEmployee(const Employee& employee);
    bool isUniqueID(int employeeID);
};

#endif