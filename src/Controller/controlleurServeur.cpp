#include "controlleurServeur.h"

ControleurServeur::ControleurServeur(VueServeur *vue, Serveur *serveur)
    : vue(vue), serveur(serveur) {}

ControleurServeur::~ControleurServeur() {
    delete vue;        // Assurez-vous que cela est correct selon votre logique
    delete serveur;    // Assurez-vous que cela est correct selon votre logique
}

void ControleurServeur::recevoirPlat(const std::string& plat) {
    serveur->recevoirPlat(plat);
    afficherPlats();
}

void ControleurServeur::servirPlat() {
    if (!serveur->getPlatsServis().empty()) {
        std::string plat = serveur->getPlatsServis().front();
        serveur->servirPlat();
        vue->afficherService(plat);
    }
}

void ControleurServeur::afficherPlats() {
    vue->afficherPlats(serveur->getPlatsServis());
}