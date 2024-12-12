#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <vector>
#include "../Model/Commande.h"
#include "../Model/Plat.h"

class Controleur {
public:
    void ajouterCommande(Commande commande);
    void ajouterPlat(Plat plat);
    std::vector<Commande> getCommandes() const;
    std::vector<Plat> getPlats() const;

private:
    std::vector<Commande> commandes_;
    std::vector<Plat> plats_;
};

#endif