#include "controlleurCuisinier.txt"

ControleurCuisinier::ControleurCuisinier(VueCuisinier *vue, Cuisinier *cuisinier)
    : vue(vue), cuisinier(cuisinier) {}

ControleurCuisinier::~ControleurCuisinier() {
    delete vue;
    delete cuisinier;
}

void ControleurCuisinier::ajouterCommande(const std::string& commande) {
    cuisinier->ajouterCommande(commande);
    afficherPlatsEnPreparation();
}

void ControleurCuisinier::preparerPlat(ComptoirSocket& comptoir) { // Add ComptoirSocket parameter
    if (!cuisinier->getPlatsEnPreparation().empty()) {
        std::string plat = cuisinier->getPlatsEnPreparation().front();
        cuisinier->preparerPlat(comptoir); // Pass the comptoir parameter
        vue->afficherPlatPrepare(plat);
    }
}

void ControleurCuisinier::afficherPlatsEnPreparation() {
    vue->afficherPlatsEnPreparation(cuisinier->getPlatsEnPreparation());
}