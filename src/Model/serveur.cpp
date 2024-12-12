#include "serveur.h"
#include <iostream>

Serveur::Serveur() {}

void Serveur::recevoirPlat(const std::string& plat) {
    // Vérification du plat
    if (plat.empty()) {
        std::cerr << "Erreur : le plat ne peut pas être vide.\n";
        return;
    }

    platsEnAttente.push_back(plat);
    std::cout << "Serveur : Plat " << plat << " reçu.\n";
}

void Serveur::servirPlat() {
    if (!platsEnAttente.empty()) {
        std::string plat = platsEnAttente.front();
        platsEnAttente.erase(platsEnAttente.begin());
        platsServis.push_back(plat); // Ajout du plat servi à la liste des plats servis
        std::cout << "Serveur : Plat " << plat << " servi.\n";
    } else {
        std::cout << "Serveur : Aucune plat à servir.\n";
    }
}

std::vector<std::string> Serveur::getPlatsEnAttente() const {
    return platsEnAttente; // Retourne les plats en attente
}

std::vector<std::string> Serveur::getPlatsServis() const {
    return platsServis; // Retourne les plats servis
}