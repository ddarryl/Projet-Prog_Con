#include "chefDeRang.h"
#include <iostream>

ChefDeRang::ChefDeRang() {}

void ChefDeRang::prendreCommande(const std::string& client, const std::string& plat) {
    // Vérification des entrées
    if (client.empty() || plat.empty()) {
        std::cerr << "Erreur : le client et le plat doivent être non vides.\n";
        return;
    }

    std::string commande = "Commande de " + client + " : " + plat;
    commandes.push_back(commande);
    std::cout << "Chef de Rang : " << commande << " enregistrée.\n";
}

std::vector<std::string> ChefDeRang::getCommandes() const {
    return commandes;
}