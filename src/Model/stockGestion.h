#ifndef STOCKGESTION_H
#define STOCKGESTION_H

#include <map>
#include <string>

class StockGestion {
public:
    StockGestion();
    void consommer(const std::string& item, int quantite);
    void reapprovisionner(const std::string& item, int quantite);
    int getStock(const std::string& item) const;
    bool alerteStock(const std::string& item) const;
    void afficherStock() const; // Ajoutez cette ligne

private:
    std::map<std::string, int> stock;
    const int seuilCritique = 5;
};

#endif