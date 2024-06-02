#ifndef BANKINGOPERATION_H
#define BANKINGOPERATION_H

#include <string>

class BankingOperation {
public:
    BankingOperation(int operationID, const std::string& description, const std::string& date, int employeeID);
    
    // Getters
    int getOperationID() const;
    std::string getDescription() const;
    std::string getDate() const;
    int getEmployeeID() const;
    
    // Setters
    void setDescription(const std::string& description);
    void setDate(const std::string& date);
    void setEmployeeID(int employeeID);
    
    // Validation
    static bool isValidOperationID(int operationID);
    static bool isValidDescription(const std::string& description);
    static bool isValidDate(const std::string& date);
    static bool isValidEmployeeID(int employeeID);

private:
    int operationID;
    std::string description;
    std::string date;
    int employeeID;
};

#endif