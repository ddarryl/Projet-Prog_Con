#include "Controller.h"

void Controleur::ajouterCommande(Commande commande) { commandes_.push_back(commande); }
void Controleur::ajouterPlat(Plat plat) { plats_.push_back(plat); }
std::vector<Commande> Controleur::getCommandes() const { return commandes_; }
std::vector<Plat> Controleur::getPlats() const { return plats_; }