#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(int clientID, const std::string& name, const std::string& address, const std::string& phone);
    
    // Getters
    int getClientID() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    
    // Setters
    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setPhone(const std::string& phone);
    
    // Validation
    static bool isValidClientID(int clientID);
    static bool isValidName(const std::string& name);
    static bool isValidAddress(const std::string& address);
    static bool isValidPhone(const std::string& phone);

private:
    int clientID;
    std::string name;
    std::string address;
    std::string phone;
};

#endif