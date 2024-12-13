#ifndef PLONGEUR_H
#define PLONGEUR_H

#include <vector>
#include <string>

class Plongeur {
public:
    Plongeur();

    // Add a dirty item
    void ajouterObjetSale(const std::string& objet);

    // Clean a single item
    void nettoyerObjet();

    // Clean multiple items of the same type
    void nettoyerObjets(const std::string& objet, int quantite);

    // Get list of dirty items
    std::vector<std::string> getObjetsSales() const;

    // Get list of cleaned items
    std::vector<std::string> getObjetsNettoyes() const;

private:
    std::vector<std::string> objetsSales;    // Dirty items
    std::vector<std::string> objetsNettoyes; // Cleaned items
};

#endif // PLONGEUR_H
