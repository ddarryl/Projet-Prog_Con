#include "ComptoirSocket.h"
#include <iostream>
#include <thread>
#include <cstring>

#include "chefDeCuisine.h"
#include "commis.h"
#include "cuisinier.h"

ComptoirSocket::ComptoirSocket(int port) : port(port), running(false), serverSocket(-1) {}

ComptoirSocket::~ComptoirSocket() {
    stop();
}

void ComptoirSocket::start() {
    struct sockaddr_in serverAddr{};
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Socket bind failed");
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) < 0) {
        perror("Socket listen failed");
        close(serverSocket);
        return;
    }

    running = true;
    std::thread(&ComptoirSocket::processRequests, this).detach();
    std::cout << "ComptoirSocket running on port " << port << std::endl;
}

void ComptoirSocket::stop() {
    running = false;
    if (serverSocket >= 0) {
        close(serverSocket);
    }
}

void ComptoirSocket::processRequests() {
    while (running) {
        struct sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            if (running) perror("Socket accept failed");
            continue;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string item(buffer);
            if (!item.empty()) {
                addItem(item);
                std::cout << "Received item: " << item << std::endl;
            } else {
                std::cerr << "Error: Received empty item.\n";
            }
        } else {
            std::cerr << "Error: Failed to read from client socket.\n";
        }

        close(clientSocket);
    }
}

void ComptoirSocket::addItem(const std::string& item) {
    std::lock_guard<std::mutex> lock(mutexComptoir);
    platsPrets.push(item);
    std::cout << "Comptoir: Added dish - " << item << std::endl;
}

std::string ComptoirSocket::getItem() {
    std::lock_guard<std::mutex> lock(mutexComptoir);
    if (!platsPrets.empty()) {
        std::string item = platsPrets.front();
        platsPrets.pop();
        return item;
    }
    return "";
}

std::vector<std::string> ComptoirSocket::getAllItems() {
    std::lock_guard<std::mutex> lock(mutexComptoir);
    std::vector<std::string> items;
    while (!platsPrets.empty()) {
        items.push_back(platsPrets.front());
        platsPrets.pop();
    }
    return items;
}

void simulateChefActions(ChefDeCuisine& chefDeCuisine, Commis& commis, Cuisinier& cuisinier, ComptoirSocket& comptoir) {
    chefDeCuisine.ajouterCommande("Steak");
    chefDeCuisine.ajouterCommande("Salad");
    chefDeCuisine.ajouterCommande("Soup");

    chefDeCuisine.preparerIngredients(commis, "Tomatoes");
    chefDeCuisine.preparerIngredients(commis, "Onions");

    for (int i = 0; i < 3; ++i) {
        chefDeCuisine.superviserPreparation();
    }

    for (const auto& plat : chefDeCuisine.getPlatsPrets()) {
        cuisinier.ajouterCommande(plat);
        cuisinier.preparerPlat(comptoir); // Pass the comptoir object here
    }
}