#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <vector>
#include "../Model/Commande.h"

class Affichage {
public:
    void afficherCommandes(const std::vector<Commande>& commandes);
    void afficherPlats(const std::vector<Plat>& plats);
};

#endif