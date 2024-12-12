#ifndef CUISINIER_H
#define CUISINIER_H

#include <vector>
#include <string>

class Cuisinier {
public:
    Cuisinier();
    void ajouterCommande(const std::string& commande);
    void preparerPlat();
    std::vector<std::string> getPlatsEnPreparation() const; // Renommé pour plus de clarté

private:
    std::vector<std::string> platsEnPreparation;
};

#endif // CUISINIER_H