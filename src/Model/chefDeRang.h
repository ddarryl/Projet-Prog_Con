#ifndef CHEF_DE_RANG_H
#define CHEF_DE_RANG_H

#include <vector>
#include <string>

class ChefDeRang {
public:
    ChefDeRang();

    void prendreCommande(const std::string& client, const std::string& plat);
    void afficherCommandes() const;
    std::vector<std::string> getCommandes() const;
    void envoyerCommande(const std::string& commande, int msgQueueId);

private:
    std::vector<std::string> commandes;
};

#endif // CHEF_DE_RANG_H