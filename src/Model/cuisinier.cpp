#include "cuisinier.h"
#include <iostream>
#include "../ipc/ipc_utils.h"
#include "ComptoirSocket.h"

Cuisinier::Cuisinier() {}

void Cuisinier::ajouterCommande(const std::string& commande) {
    if (commande.empty()) {
        std::cerr << "Error: The order cannot be empty.\n";
        return;
    }

    // Arbitrary limit: check that the cook does not have too many orders
    if (platsEnPreparation.size() >= 10) {
        std::cerr << "Error: Too many pending orders. Cannot add " << commande << ".\n";
        return;
    }

    platsEnPreparation.push_back(commande);
    std::cout << "Cook: Order added: " << commande << "\n";
}

void Cuisinier::preparerPlat(ComptoirSocket& comptoir) {
    if (!platsEnPreparation.empty()) {
        std::string plat = platsEnPreparation.front();
        platsEnPreparation.erase(platsEnPreparation.begin());
        std::cout << "Cook: Dish " << plat << " prepared.\n";

        // Send the dish to the counter
        ajouterRepasPret(plat, comptoir); // Now this function is recognized
    } else {
        std::cout << "Cook: No orders to prepare.\n";
    }
}

void Cuisinier::ajouterRepasPret(const std::string& plat, ComptoirSocket& comptoir) {
    comptoir.addItem(plat);
    std::cout << "Cook: Added ready dish - " << plat << std::endl;
}

void Cuisinier::recevoirCommande(int msgQueueId) {
    std::string commande = receiveMessage(msgQueueId, 1); // Type 1 for orders
    if (!commande.empty()) {
        ajouterCommande(commande); // Add the order to the list
        std::cout << "Cook: Order received and added - " << commande << std::endl;
    } else {
            std::cerr << "Cook: Failed to receive a valid order.\n";
        }
}

std::vector<std::string> Cuisinier::getPlatsEnPreparation() const {
    return platsEnPreparation;
}