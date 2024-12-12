#include "cuisinier.h"
#include <iostream>

Cuisinier::Cuisinier() {}

void Cuisinier::ajouterCommande(const std::string& commande) {
    // Vérification de la commande
    if (commande.empty()) {
        std::cerr << "Erreur : la commande ne peut pas être vide.\n";
        return;
    }

    platsEnPreparation.push_back(commande);
    std::cout << "Cuisinier : Commande ajoutée : " << commande << "\n";
}

void Cuisinier::preparerPlat() {
    if (!platsEnPreparation.empty()) {
        std::string plat = platsEnPreparation.front();
        platsEnPreparation.erase(platsEnPreparation.begin());
        std::cout << "Cuisinier : Plat " << plat << " préparé.\n";
    } else {
        std::cout << "Cuisinier : Aucune commande à préparer.\n";
    }
}

std::vector<std::string> Cuisinier::getPlatsEnPreparation() const {
    return platsEnPreparation;
}