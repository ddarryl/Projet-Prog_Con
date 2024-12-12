#include "plongeur.h"
#include <iostream>

Plongeur::Plongeur() {}

void Plongeur::ajouterObjetSale(const std::string& objet) {
    // Vérification de l'objet
    if (objet.empty()) {
        std::cerr << "Erreur : l'objet ne peut pas être vide.\n";
        return;
    }

    objetsSales.push_back(objet);
    std::cout << "Plongeur : Objet " << objet << " ajouté à la pile.\n";
}

void Plongeur::nettoyerObjet() {
    if (!objetsSales.empty()) {
        std::string objet = objetsSales.front();
        objetsSales.erase(objetsSales.begin());
        objetsNettoyes.push_back(objet); // Ajout de l'objet nettoyé à la liste des objets nettoyés
        std::cout << "Plongeur : Objet " << objet << " nettoyé.\n";
    } else {
        std::cout << "Plongeur : Aucune objet à nettoyer.\n";
    }
}

std::vector<std::string> Plongeur::getObjetsSales() const {
    return objetsSales; // Retourne les objets sales
}

std::vector<std::string> Plongeur::getObjetsNettoyes() const {
    return objetsNettoyes; // Retourne les objets nettoyés
}