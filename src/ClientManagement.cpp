#include "../include/ClientManagement.h"

// Constructor
ClientManagement::ClientManagement() : head(nullptr) {}

// Destructor
ClientManagement::~ClientManagement() {
    ClientNode* current = head;
    while (current != nullptr) {
        ClientNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool ClientManagement::isUniqueID(int clientID) {
    return usedIDs.find(clientID) == usedIDs.end();
}

void ClientManagement::manage() {
    int choice;
    do {
        std::cout << "-------------------------------\n";
        std::cout << "  Client Management Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Create Client\n";
        std::cout << "2. View Client\n";
        std::cout << "3. Update Client\n";
        std::cout << "4. Delete Client\n";
        std::cout << "5. Save Clients\n";
        std::cout << "6. Load Clients\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "-------------------------------\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                createClient();
                break;
            case 2:
                viewClient();
                break;
            case 3:
                updateClient();
                break;
            case 4:
                deleteClient();
                break;
            case 5:
                saveClients("clients.txt");
                break;
            case 6:
                loadClients("clients.txt");
                break;
            case 7:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);
}

void ClientManagement::createClient() {
    int clientID;
    std::string name, address, phone;
    do {
        std::cout << "Enter client ID: ";
        std::cin >> clientID;
        if (!isUniqueID(clientID)) {
            std::cout << "Client ID already in use. Please enter a different ID.\n";
        }
    } while (!isUniqueID(clientID));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);

    try {
        Client newClient(clientID, name, address, phone);
        ClientNode* newNode = new ClientNode(newClient);
        newNode->next = head;
        head = newNode;
        usedIDs.insert(clientID);
        std::cout << "Client created successfully.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid input: " << e.what() << "\n";
    }
}

void ClientManagement::viewClient() {
    int clientID;
    std::cout << "Enter client ID: ";
    std::cin >> clientID;
    ClientNode* node = findClientNode(clientID);
    if (node) {
        printClient(node->client);
    } else {
        std::cout << "Client not found.\n";
    }
}

void ClientManagement::updateClient() {
    int clientID;
    std::string name, address, phone;
    std::cout << "Enter client ID: ";
    std::cin >> clientID;
    ClientNode* node = findClientNode(clientID);
    if (node) {
        std::cout << "Enter new name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        std::getline(std::cin, name);
        std::cout << "Enter new address: ";
        std::getline(std::cin, address);
        std::cout << "Enter new phone: ";
        std::getline(std::cin, phone);
        try {
            node->client.setName(name);
            node->client.setAddress(address);
            node->client.setPhone(phone);
            std::cout << "Client updated successfully.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << "\n";
        }
    } else {
        std::cout << "Client not found.\n";
    }
}

void ClientManagement::deleteClient() {
    int clientID;
    std::cout << "Enter client ID: ";
    std::cin >> clientID;
    ClientNode* prev = nullptr;
    ClientNode* current = head;
    while (current != nullptr && current->client.getClientID() != clientID) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        usedIDs.erase(clientID);
        delete current;
        std::cout << "Client deleted successfully.\n";
    } else {
        std::cout << "Client not found.\n";
    }
}

ClientNode* ClientManagement::findClientNode(int clientID) {
    ClientNode* current = head;
    while (current != nullptr) {
        if (current->client.getClientID() == clientID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void ClientManagement::printClient(const Client& client) {
    std::cout << "Client ID: " << client.getClientID() << "\n";
    std::cout << "Name: " << client.getName() << "\n";
    std::cout << "Address: " << client.getAddress() << "\n";
    std::cout << "Phone: " << client.getPhone() << "\n";
}

void ClientManagement::saveClients(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        ClientNode* current = head;
        while (current != nullptr) {
            file << current->client.getClientID() << ","
                 << current->client.getName() << ","
                 << current->client.getAddress() << ","
                 << current->client.getPhone() << "\n";
            current = current->next;
        }
        file.close();
        std::cout << "Clients saved successfully to " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for saving.\n";
    }
}

void ClientManagement::loadClients(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            int clientID;
            std::string name, address, phone;

            std::getline(ss, item, ',');
            clientID = std::stoi(item);
            std::getline(ss, name, ',');
            std::getline(ss, address, ',');
            std::getline(ss, phone, ',');

            Client newClient(clientID, name, address, phone);
            ClientNode* newNode = new ClientNode(newClient);
            newNode->next = head;
            head = newNode;
            usedIDs.insert(clientID); // Add to the set of used IDs
        }
        file.close();
        std::cout << "Clients loaded successfully from " << filename << "\n";
    } else {
        std::cout << "Unable to open file " << filename << " for loading.\n";
    }
}