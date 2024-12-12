#include "Affichage.h"
#include <iostream>

void Affichage::afficherCommandes(const std::vector<Commande>& commandes) {
    for (const auto& commande : commandes) {
        std::cout << "Commande de " << commande.getClient().getNom() << " " << commande.getClient().getPrenom() << std::endl;
        for (const auto& plat : commande.getPlats()) {
            std::cout << "  - " << plat.getNom() << std::endl;
        }
    }
}

void Affichage::afficherPlats(const std::vector<Plat>& plats) {
    for (const auto& plat : plats) {
        std::cout << plat.getNom() << std::endl;
        for (const auto& ingredient : plat.getIngredients()) {
            std::cout << "  - " << ingredient.getNom() << std::endl;
        }
    }
}