#include "Commande.h"

Commande::Commande(Client client) : client_(client) {}

void Commande::ajouterPlat(Plat plat) { plats_.push_back(plat); }
std::vector<Plat> Commande::getPlats() const { return plats_; }
Client Commande::getClient() const { return client_; }