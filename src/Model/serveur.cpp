#include "serveur.h"
#include <iostream>
#include "../ipc/ipc_utils.h"
#include "ComptoirSocket.h"
#include "ressourceGestion.h"

Serveur::Serveur() {}

void Serveur::recevoirPlat(const std::string& plat) {
    if (plat.empty()) {
        std::cerr << "Erreur : le plat ne peut pas être vide.\n";
        return;
    }
    platsEnAttente.push_back(plat);
    std::cout << "Serveur : Plat reçu - " << plat << ".\n";
}

void Serveur::servirPlat() {
    if (platsEnAttente.empty()) {
        std::cout << "Serveur : Aucun plat en attente à servir.\n";
        return;
    }

    std::string plat = platsEnAttente.front();
    platsEnAttente.erase(platsEnAttente.begin());  // Remove the dish from the waiting list
    platsServis.push_back(plat);                  // Add the dish to the served list
    std::cout << "Serveur : Plat servi - " << plat << ".\n";
}

void Serveur::afficherPlats() const {
    std::cout << "Plats en attente :\n";
    for (const auto& plat : platsEnAttente) {
        std::cout << "- " << plat << "\n";
    }

    std::cout << "\nPlats servis :\n";
    for (const auto& plat : platsServis) {
        std::cout << "- " << plat << "\n";
    }
}

void Serveur::deposerVaisselleSale(const std::string& plat, ComptoirSocket& comptoir) {
    comptoir.addItem(plat);
    std::cout << "Serveur: Deposited dirty dish - " << plat << std::endl;
}

void Serveur::recevoirPlat(int msgQueueId) {
    std::string plat = receiveMessage(msgQueueId, 2); // Type 2 for ready dishes
    std::cout << "Serveur: Ready dish received - " << plat << std::endl;
}

void Serveur::utiliserConsommables(RessourceGestion& gestion, const std::string& item, int quantite) {
    if (gestion.verifierDisponibilite(item, quantite)) {
        gestion.consommerRessource(item, quantite);
    } else {
        std::cerr << "Serveur: Not enough " << item << " available.\n";
    }
}

std::vector<std::string> Serveur::getPlatsEnAttente() const {
    return platsEnAttente;
}

std::vector<std::string> Serveur::getPlatsServis() const {
    return platsServis;
}