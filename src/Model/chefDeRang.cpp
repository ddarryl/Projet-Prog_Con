#include "chefDeRang.h"
#include "../ipc/ipc_utils.h"
#include <iostream>

ChefDeRang::ChefDeRang() {}

void ChefDeRang::prendreCommande(const std::string& client, const std::string& plat) {
    if (client.empty() || plat.empty()) {
        std::cerr << "Erreur : le client et le plat doivent être non vides.\n";
        return;
    }

    std::string commande = "Commande de " + client + " : " + plat;
    commandes.push_back(commande);
    std::cout << "Commande enregistrée : " << commande << std::endl;
}

void ChefDeRang::afficherCommandes() const {
    if (commandes.empty()) {
        std::cout << "Aucune commande en cours.\n";
        return;
    }

    std::cout << "Commandes en cours :\n";
    for (const auto& commande : commandes) {
        std::cout << commande << std::endl;
    }
}

void ChefDeRang::envoyerCommande(const std::string& commande, int msgQueueId) {
    sendMessage(msgQueueId, commande, 1); // Type 1 for orders
    std::cout << "Chef de Rang: Order sent - " << commande << std::endl;
}

void chefDeRangSendOrderWithSemaphore(int msgQueueId, int semId, const std::string& order) {
    semaphoreWait(semId); // Wait for the semaphore
    ChefDeRang chef; // Créez une instance de ChefDeRang
    chef.envoyerCommande(order, msgQueueId); // Appelez la méthode sur l'instance
    semaphoreSignal(semId); // Release the semaphore
}

std::vector<std::string> ChefDeRang::getCommandes() const {
    return commandes;
}