#ifndef EMPLOYEENODE_H
#define EMPLOYEENODE_H

#include "Employee.h"

struct EmployeeNode {
    Employee employee;
    EmployeeNode* next;

    EmployeeNode(const Employee& emp) : employee(emp), next(nullptr) {}
};

#endif
