#ifndef CARTE_RESTAURANT_H
#define CARTE_RESTAURANT_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CarteRestaurant {
public:
    CarteRestaurant() {}

    void chargerCarte(const std::string& fichier) {
        std::ifstream fichierEntree(fichier);
        if (fichierEntree.is_open()) {
            fichierEntree >> carteJson;
            fichierEntree.close();
            std::cout << "Menu loaded successfully from " << fichier << "\n";
        } else {
            std::cerr << "Error: Could not open menu file." << std::endl;
        }
    }

    void sauvegarderCarte(const std::string& fichier) const {
        std::ofstream fichierSortie(fichier);
        if (fichierSortie.is_open()) {
            fichierSortie << carteJson.dump(4);
            fichierSortie.close();
            std::cout << "Menu saved successfully to " << fichier << "\n";
        } else {
            std::cerr << "Error: Could not save menu file." << std::endl;
        }
    }

    void ajouterRecette(const std::string& categorie, const std::string& recette) {
        carteJson[categorie].push_back(recette);
        std::cout << "Added recipe '" << recette << "' to category '" << categorie << "'.\n";
    }

    void afficherCarte() const {
        for (const auto& [categorie, recettes] : carteJson.items()) {
            std::cout << categorie << ":\n";
            for (const auto& recette : recettes) {
                std::cout << "  - " << recette << "\n";
            }
        }
    }

    std::vector<std::string> obtenirRecettes(const std::string& categorie) const {
        if (carteJson.contains(categorie)) {
            return carteJson[categorie].get<std::vector<std::string>>();
        } else {
            std::cerr << "Error: Category '" << categorie << "' not found." << std::endl;
            return {};
        }
    }

private:
    json carteJson {
        {"Entrées", {"Salade César", "Soupe à l'oignon", "Tartare de saumon", "Bruschetta", "Foie gras", "Carpaccio", "Velouté de légumes", "Quiche lorraine", "Oeufs mayonnaise", "Assiette de charcuterie"}},
        {"Plats", {"Boeuf bourguignon", "Coq au vin", "Filet de poisson", "Poulet rôti", "Côte de porc", "Ratatouille", "Lasagnes", "Curry de légumes", "Magret de canard", "Entrecôte"}},
        {"Desserts", {"Tarte aux pommes", "Mousse au chocolat", "Crème brûlée", "Tiramisu", "Fondant au chocolat", "Île flottante", "Panna cotta", "Cheesecake", "Sorbet", "Profiteroles"}}
    };
};

#endif
