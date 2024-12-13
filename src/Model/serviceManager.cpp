#include "serviceManager.h"
#include <fstream>
#include <iostream>
#include <QMutexLocker>

ServiceManager::ServiceManager() {
    stock["Viande"] = 10;
    stock["Légumes"] = 20;
    stock["Pain"] = 15;
    stock["Desserts"] = 10;
}

void ServiceManager::ajouterArticle(const std::string& item, int quantiteInitiale) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) != stock.end()) {
        std::cerr << "Article " << item << " existe déjà.\n";
        return;
    }
    stock[item] = quantiteInitiale;
    notifyStockChange(item, quantiteInitiale);
    logAction("Ajouté", item, quantiteInitiale);
}

void ServiceManager::consommer(const std::string& item, int quantite) {
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

void ServiceManager::reapprovisionner(const std::string& item, int quantite) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) == stock.end()) {
        std::cerr << "ERREUR : L'article " << item << " n'existe pas.\n";
        return;
    }
    stock[item] += quantite;
    notifyStockChange(item, stock[item]);
    logAction("Réapprovisionné", item, quantite);
}

int ServiceManager::getStock(const std::string& item) const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    if (stock.find(item) == stock.end()) {
        std::cerr << "ERREUR : L'article " << item << " n'existe pas.\n";
        return 0;
    }
    return stock.at(item);
}

bool ServiceManager::alerteStock(const std::string& item) const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    return stock.find(item) != stock.end() && stock.at(item) <= seuilCritique;
}

void ServiceManager::afficherStock() const {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    std::cout << "État actuel du stock :\n";
    for (const auto& pair : stock) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

void ServiceManager::chargerDepuisBDD(const std::string& fichier) {
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

void ServiceManager::sauvegarderDansBDD(const std::string& fichier) {
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

void ServiceManager::onStockChange(const std::function<void(const std::string&, int)>& callback) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    callbacks.push_back(callback);
}

void ServiceManager::notifyStockChange(const std::string& item, int quantite) {
    QMutexLocker locker(&mutexStock); // Automatically locks and unlocks
    for (const auto& callback : callbacks) {
        callback(item, quantite);
    }
}

void ServiceManager::marquerPlatPret(int tableId, const std::string& plat) {
    std::cout << "Dish " << plat << " is ready for table " << tableId << ".\n";
}

void ServiceManager::ajouterPlat(int tableId, const std::string& plat) {
    tablePlats[tableId].push_back(plat);
    std::cout << "Plat ajouté : " << plat << " pour la table " << tableId << std::endl;
}

void ServiceManager::logAction(const std::string& action, const std::string& item, int quantite) const {
    std::cout << "LOG : " << action << " " << quantite << " " << item << ".\n";
}