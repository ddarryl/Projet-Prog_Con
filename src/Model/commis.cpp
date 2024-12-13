#include "commis.h"
#include <iostream>

Commis::Commis() {}

void Commis::preparerIngredient(const std::string& ingredient) {
    if (ingredient.empty()) {
        std::cerr << "Error: Ingredient cannot be empty.\n";
        return;
    }
    ingredientsPrepares.push_back(ingredient);
    std::cout << "Commis: Prepared ingredient - " << ingredient << ".\n";
}

void Commis::rangerUstensile(const std::string& ustensile) {
    if (ustensile.empty()) {
        std::cerr << "Error: Utensil cannot be empty.\n";
        return;
    }
    ustensilesRanges.push_back(ustensile);
    std::cout << "Commis: Stored utensil - " << ustensile << ".\n";
}

void Commis::aiderChefDeRang(const std::string& commande) {
    if (commande.empty()) {
        std::cerr << "Error: Command cannot be empty.\n";
        return;
    }
    commandesAide.push_back(commande);
    std::cout << "Commis: Assisted with command - " << commande << ".\n";
}

void Commis::reapprovisionner(RessourceGestion& gestion, const std::string& item, int quantite) {
    gestion.ajouterStock(item, quantite);
    std::cout << "Commis: Restocked " << quantite << " of " << item << ".\n";
}

void Commis::afficherTaches() const {
    std::cout << "Commis: Completed tasks:\n";

    std::cout << "Prepared ingredients:\n";
    for (const auto& ingredient : ingredientsPrepares) {
        std::cout << "- " << ingredient << "\n";
    }

    std::cout << "\nStored utensils:\n";
    for (const auto& ustensile : ustensilesRanges) {
        std::cout << "- " << ustensile << "\n";
    }

    std::cout << "\nAssisted commands:\n";
    for (const auto& commande : commandesAide) {
        std::cout << "- " << commande << "\n";
    }
}
