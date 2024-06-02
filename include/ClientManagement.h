#ifndef CLIENTMANAGEMENT_H
#define CLIENTMANAGEMENT_H

#include "Client.h"
#include "ClientNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

class ClientManagement {
public:
    ClientManagement();
    ~ClientManagement();
    
    void manage();
    void registerClient();
    void viewClient();
    void updateClient();
    void removeClient();
    void saveClients(const std::string& filename);
    void loadClients(const std::string& filename);

private:
    ClientNode* head;
    std::set<int> usedIDs;

    ClientNode* findClientNode(int clientID);
    void printClient(const Client& client);
    bool isUniqueID(int clientID);
};

#endif