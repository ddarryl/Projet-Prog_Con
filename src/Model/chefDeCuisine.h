#ifndef CHEF_DE_CUISINE_H
#define CHEF_DE_CUISINE_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>

#include "commis.h"
#include "Recette.h"

class ChefDeCuisine {
public:
    ChefDeCuisine();

    // Add a new dish to be prepared
    void ajouterCommande(const std::string& commande);

    // Supervise preparation of the next dish
    void superviserPreparation();

    // Check if all dishes are ready
    bool tousLesPlatsPrets() const;

    // Notify that a dish is ready
    void platPret(const std::string& plat);

    void preparerIngredients(Commis& commis, const std::string& ingredient); // Add this line

    // Get list of ready dishes
    std::vector<std::string> getPlatsPrets() const;

private:
    std::queue<std::string> commandes; // Orders to prepare
    std::vector<std::string> platsPrets; // Ready dishes
    mutable std::mutex mutexCuisine; // Protect access
    std::condition_variable condition; // Notify when dishes are ready
};

#endif // CHEF_DE_CUISINE_H
