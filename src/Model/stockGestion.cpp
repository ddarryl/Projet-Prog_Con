#include "stockGestion.h"
#include <QMutexLocker>
#include <fstream>
#include <iostream>
#include <thread>

StockGestion::StockGestion() {
    stock["Viande"] = 10;
    stock["Légumes"] = 20;
    stock["Pain"] = 15;
    stock["Desserts"] = 10;
}

void StockGestion::ajouterArticle(const std::string& item, int quantiteInitiale) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) != stock.end()) {
        std::cerr << "Article " << item << " existe déjà.\n";
        return;
    }
    stock[item] = quantiteInitiale;
    notifyStockChange(item, quantiteInitiale);
    logAction("Ajouté", item, quantiteInitiale);
}

void StockGestion::consommer(const std::string& item, int quantite) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) == stock.end()) {
        std::cerr << "ERREUR : L'article " << item << " n'existe pas.\n";
        return;
    }

    if (stock[item] >= quantite) {
        stock[item] -= quantite;
        notifyStockChange(item, stock[item]);
        logAction("Consommé", item, quantite);
        if (alerteStock(item)) {
            std::cerr << "ALERTE : Stock faible pour " << item << " (" << stock[item] << ").\n";
        }
    } else {
        std::cerr << "ERREUR : Stock insuffisant pour consommer " << quantite << " " << item << ".\n";
    }
}

void StockGestion::reapprovisionner(const std::string& item, int quantite) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) == stock.end()) {
        std::cerr << "ERREUR : L'article " << item << " n'existe pas.\n";
        return;
    }
    stock[item] += quantite;
    notifyStockChange(item, stock[item]);
    logAction("Réapprovisionné", item, quantite);
}

int StockGestion::getStock(const std::string& item) const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) == stock.end()) {
        std::cerr << "ERREUR : L'article " << item << " n'existe pas.\n";
        return 0;
    }
    return stock.at(item);
}

bool StockGestion::alerteStock(const std::string& item) const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    return stock.find(item) != stock.end() && stock.at(item) <= seuilCritique;
}

void StockGestion::afficherStock() const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    std::cout << "État actuel du stock :\n";
    for (const auto& pair : stock) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

void StockGestion::chargerDepuisBDD(const std::string& fichier) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    std::ifstream infile(fichier);
    if (!infile) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << fichier << " pour charger les stocks.\n";
        return;
    }

    std::string item;
    int quantite;
    while (infile >> item >> quantite) {
        stock[item] = quantite;
    }
    infile.close();
    std::cout << "Stock chargé depuis " << fichier << ".\n";
}

void StockGestion::sauvegarderDansBDD(const std::string& fichier) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    std::ofstream outfile(fichier);
    if (!outfile) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << fichier << " pour sauvegarder les stocks.\n";
        return;
    }

    for (const auto& pair : stock) {
        outfile << pair.first << " " << pair.second << "\n";
    }
    outfile.close();
    std::cout << "Stock sauvegardé dans " << fichier << ".\n";
}

void StockGestion::onStockChange(const std::function<void(const std::string&, int)>& callback) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    callbacks.push_back(callback);
}

void StockGestion::notifyStockChange(const std::string& item, int quantite) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    for (const auto& callback : callbacks) {
        callback(item, quantite);
    }
}

void StockGestion::ajouterPlat(int tableId, const std::string& plat) {
    tablePlats[tableId].push_back(plat);
    std::cout << "Plat ajouté : " << plat << " pour la table " << tableId << std::endl;
}

void StockGestion::marquerPlatPret(int tableId, const std::string& plat) {
    std::cout << "Dish " << plat << " is ready for table " << tableId << ".\n";
}

void StockGestion::logAction(const std::string& action, const std::string& item, int quantite) const {
    std::cout << "LOG : " << action << " " << quantite << " " << item << ".\n";
}

void StockGestion::preparerPlat(int tableId, const std::string& plat) {
    std::cout << "Préparation du plat " << plat << " pour la table " << tableId << ".\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    marquerPlatPret(tableId, plat);
}

void StockGestion::servirTable(int tableId) {
    QMutexLocker locker(&mutexStock);
    if (tablePlats.find(tableId) != tablePlats.end()) {
        std::cout << "Service de la table " << tableId << " avec les plats : ";
        for (const auto& plat : tablePlats[tableId]) {
            std::cout << plat << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun plat à servir pour la table " << tableId << ".\n";
    }
}