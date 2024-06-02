#include "../include/Client.h"
#include <regex>
#include <stdexcept>

// Constructor
Client::Client(int clientID, const std::string& name, const std::string& address, const std::string& phone)
    : clientID(clientID), name(name), address(address), phone(phone) {
    if (!isValidClientID(clientID) || !isValidName(name) || !isValidAddress(address) || !isValidPhone(phone)) {
        throw std::invalid_argument("Invalid argument");
    }
}

// Getters
int Client::getClientID() const {
    return clientID;
}

std::string Client::getName() const {
    return name;
}

std::string Client::getAddress() const {
    return address;
}

std::string Client::getPhone() const {
    return phone;
}

// Setters
void Client::setName(const std::string& name) {
    if (isValidName(name)) {
        this->name = name;
    }
}

void Client::setAddress(const std::string& address) {
    if (isValidAddress(address)) {
        this->address = address;
    }
}

void Client::setPhone(const std::string& phone) {
    if (isValidPhone(phone)) {
        this->phone = phone;
    }
}

// Validation methods
bool Client::isValidClientID(int clientID) {
    return clientID > 0;
}

bool Client::isValidName(const std::string& name) {
    std::regex nameRegex("^[A-Za-z\\- ]{1,100}$");
    return std::regex_match(name, nameRegex);
}

bool Client::isValidAddress(const std::string& address) {
    std::regex addressRegex("^[A-Za-z0-9\\- ]{1,255}$");
    return std::regex_match(address, addressRegex);
}

bool Client::isValidPhone(const std::string& phone) {
    std::regex phoneRegex("^[0-9\\- ]{1,15}$");
    return std::regex_match(phone, phoneRegex);
}