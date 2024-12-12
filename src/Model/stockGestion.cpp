#include "stockGestion.h"
#include <iostream>

StockGestion::StockGestion() {
    stock["Viande"] = 10;
    stock["Légumes"] = 20;
    stock["Pain"] = 15;
    stock["Desserts"] = 10;
}

void StockGestion::consommer(const std::string& item, int quantite) {
    if (stock.find(item) == stock.end()) {
        std::cout << "ERREUR : L'article " << item << " n'existe pas dans le stock.\n";
        return;
    }

    if (stock[item] >= quantite) {
        stock[item] -= quantite;
        std::cout << "Stock : Consommation de " << quantite << " " << item << ".\n";
    } else {
        std::cout << "ERREUR : Pas assez de " << item << " en stock pour consommer " << quantite << ".\n";
    }
}

void StockGestion::reapprovisionner(const std::string& item, int quantite) {
    if (stock.find(item) == stock.end()) {
        std::cout << "ERREUR : L'article " << item << " n'existe pas dans le stock.\n";
        return;
    }

    stock[item] += quantite;
    std::cout << "Stock : Réapprovisionnement de " << quantite << " " << item << ".\n";
}

int StockGestion::getStock(const std::string& item) const {
    if (stock.find(item) == stock.end()) {
        std::cout << "ERREUR : L'article " << item << " n'existe pas dans le stock.\n";
        return 0; // Retourne 0 si l'article n'existe pas
    }
    return stock.at(item);
}

bool StockGestion::alerteStock(const std::string& item) const {
    if (stock.find(item) == stock.end()) {
        std::cout << "ERREUR : L'article " << item << " n'existe pas dans le stock.\n";
        return false; // Retourne false si l'article n'existe pas
    }
    return stock.at(item) <= seuilCritique;
}

void StockGestion::afficherStock() const {
    std::cout << "État actuel du stock :\n";
    for (const auto& pair : stock) {
        std::cout << pair .first << ": " << pair.second << "\n";
    }
}