#ifndef CLIENTNODE_H
#define CLIENTNODE_H

#include "Client.h"

struct ClientNode {
    Client client;
    ClientNode* next;

    ClientNode(const Client& cl) : client(cl), next(nullptr) {}
};

#endif