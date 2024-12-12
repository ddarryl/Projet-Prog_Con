#ifndef CONTROLEURSERVEUR_H
#define CONTROLEURSERVEUR_H

#include "../View/vueServeur.h"
#include "../Model/serveur.h"

class ControleurServeur : public QObject {
    Q_OBJECT

public:
    ControleurServeur(VueServeur *vue, Serveur *serveur);
    ~ControleurServeur();
    void recevoirPlat(const std::string& plat);
    void servirPlat();
    void afficherPlats();

private:
    VueServeur *vue;
    Serveur *serveur;
};

#endif
