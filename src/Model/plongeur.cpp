#include "plongeur.h"
#include <thread>
#include <chrono>
#include <iostream>

Plongeur::Plongeur() {}

void Plongeur::ajouterObjetSale(const std::string& objet) {
    if (objet.empty()) {
        std::cerr << "Error: Item cannot be empty.\n";
        return;
    }

    objetsSales.push_back(objet);
    std::cout << "Plongeur: Added dirty item - " << objet << ".\n";
}

void Plongeur::nettoyerObjet() {
    if (!objetsSales.empty()) {
        std::string objet = objetsSales.front();
        objetsSales.erase(objetsSales.begin());
        objetsNettoyes.push_back(objet);
        std::cout << "Plongeur: Cleaned item - " << objet << ".\n";
    } else {
        std::cout << "Plongeur: No items to clean.\n";
    }
}

void Plongeur::nettoyerObjets(const std::string& objet, int quantite) {
    int count = 0;

    // Check if the requested quantity of the item exists
    for (auto it = objetsSales.begin(); it != objetsSales.end() && count < quantite;) {
        if (*it == objet) {
            it = objetsSales.erase(it);
            objetsNettoyes.push_back(objet);
            ++count;
        } else {
            ++it;
        }
    }

    if (count == 0) {
        std::cout << "Plongeur: No " << objet << " to clean.\n";
        return;
    }

    std::cout << "Plongeur: Cleaning " << count << " " << objet << "(s)...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate cleaning time
    std::cout << "Plongeur: Cleaned " << count << " " << objet << "(s).\n";
}

std::vector<std::string> Plongeur::getObjetsSales() const {
    return objetsSales;
}

std::vector<std::string> Plongeur::getObjetsNettoyes() const {
    return objetsNettoyes;
}
