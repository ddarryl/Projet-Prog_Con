#include "chefDeCuisine.h"
#include <iostream>

#include "commis.h"

ChefDeCuisine::ChefDeCuisine() {}

void ChefDeCuisine::ajouterCommande(const std::string& commande) {
    std::lock_guard<std::mutex> lock(mutexCuisine);
    commandes.push(commande);
    std::cout << "Chef de Cuisine: Added order for " << commande << "\n";
    condition.notify_one();
}

void ChefDeCuisine::superviserPreparation() {
    std::unique_lock<std::mutex> lock(mutexCuisine);
    if (commandes.empty()) {
        std::cout << "Chef de Cuisine: No orders to prepare.\n";
        return;
    }

    std::string commande = commandes.front();
    commandes.pop();
    lock.unlock();

    std::cout << "Chef de Cuisine: Supervising preparation of " << commande << "\n";
    // Simulate preparation
    std::this_thread::sleep_for(std::chrono::seconds(2));
    platPret(commande);
}

bool ChefDeCuisine::tousLesPlatsPrets() const {
    std::lock_guard<std::mutex> lock(mutexCuisine);
    return commandes.empty() && !platsPrets.empty();
}

void ChefDeCuisine::platPret(const std::string& plat) {
    std::lock_guard<std::mutex> lock(mutexCuisine);
    platsPrets.push_back(plat);
    std::cout << "Chef de Cuisine: " << plat << " is ready.\n";
}

void ChefDeCuisine::preparerIngredients(Commis& commis, const std::string& ingredient) {
    commis.preparerIngredient(ingredient);
    std::cout << "Chef de Cuisine: Asked commis to prepare " << ingredient << "\n";
}


std::vector<std::string> ChefDeCuisine::getPlatsPrets() const {
    std::lock_guard<std::mutex> lock(mutexCuisine);
    return platsPrets;
}
