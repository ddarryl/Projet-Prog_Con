#include "controlleurChefDeRang.h"

ControleurChefDeRang::ControleurChefDeRang(VueChefDeRang *vue, ChefDeRang *chefDeRang)
    : vue(vue), chefDeRang(chefDeRang) {}

ControleurChefDeRang::~ControleurChefDeRang() {
    delete vue;
    delete chefDeRang;
}

void ControleurChefDeRang::prendreCommande(const std::string& client, const std::string& plat) {
    chefDeRang->prendreCommande(client, plat);
    afficherCommandes();
}

void ControleurChefDeRang::afficherCommandes() {
    vue->afficherCommandes(chefDeRang->getCommandes());
}