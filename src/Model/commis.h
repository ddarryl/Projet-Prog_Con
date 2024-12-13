#ifndef COMMIS_H
#define COMMIS_H

#include <vector>
#include <string>

#include "ressourceGestion.h"

class Commis {
public:
    Commis();

    void preparerIngredient(const std::string& ingredient);
    void rangerUstensile(const std::string& ustensile);
    void aiderChefDeRang(const std::string& commande);
    void reapprovisionner(RessourceGestion& gestion, const std::string& item, int quantite);
    void afficherTaches() const;

private:
    std::vector<std::string> ingredientsPrepares;
    std::vector<std::string> ustensilesRanges;
    std::vector<std::string> commandesAide;
};

#endif // COMMIS_H