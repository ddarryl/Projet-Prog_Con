#ifndef CHEFDERANG_H
#define CHEFDERANG_H

#include <vector>
#include <string>

class ChefDeRang {
public:
    ChefDeRang();
    void prendreCommande(const std::string& client, const std::string& plat);
    std::vector<std::string> getCommandes() const;

private:
    std::vector<std::string> commandes;
};

#endif // CHEFDERANG_H