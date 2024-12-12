#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "Client.h"
#include "Plat.h"

class Commande {
public:
    Commande(Client client);
    void ajouterPlat(Plat plat);
    std::vector<Plat> getPlats() const;
    Client getClient() const;

private:
    Client client_;
    std::vector<Plat> plats_;
};

#endif