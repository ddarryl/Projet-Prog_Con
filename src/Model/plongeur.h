#ifndef PLONGEUR_H
#define PLONGEUR_H

#include <vector>
#include <string>

class Plongeur {
public:
    Plongeur();
    void ajouterObjetSale(const std::string& objet);
    void nettoyerObjet();
    std::vector<std::string> getObjetsSales() const; // Renommé pour plus de clarté
    std::vector<std::string> getObjetsNettoyes() const; // Nouvelle méthode pour obtenir les objets nettoyés

private:
    std::vector<std::string> objetsSales;
    std::vector<std::string> objetsNettoyes; // Nouveau vecteur pour les objets nettoyés
};

#endif // PLONGEUR_H