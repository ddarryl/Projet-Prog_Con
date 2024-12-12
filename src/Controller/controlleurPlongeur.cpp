#include "controlleurPlongeur.h"

ControleurPlongeur::ControleurPlongeur(VuePlongeur *vue, Plongeur *plongeur)
    : vue(vue), plongeur(plongeur) {}

ControleurPlongeur::~ControleurPlongeur() {
    delete vue;        // Assurez-vous que cela est correct selon votre logique
    delete plongeur;   // Assurez-vous que cela est correct selon votre logique
}

void ControleurPlongeur::ajouterObjetSale(const std::string& objet) {
    plongeur->ajouterObjetSale(objet);
    afficherObjetsSales();
}

void ControleurPlongeur::nettoyerObjet() {
    if (!plongeur->getObjetsNettoyes().empty()) {
        std::string objet = plongeur->getObjetsNettoyes().front();
        plongeur->nettoyerObjet();
        vue->afficherObjetNettoye(objet);
    }
}

void ControleurPlongeur::afficherObjetsSales() {
    vue->afficherObjetsSales(plongeur->getObjetsNettoyes());
}