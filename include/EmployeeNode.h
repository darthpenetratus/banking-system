#ifndef EMPLOYEENODE_H
#define EMPLOYEENODE_H

#include "Employee.h"

struct EmployeeNode {
    Employee employee;
    EmployeeNode* next;

    EmployeeNode(const Employee& employee) : employee(employee), next(nullptr) {}
};

#endif