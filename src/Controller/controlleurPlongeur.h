#ifndef CONTROLEURPLONGEUR_H
#define CONTROLEURPLONGEUR_H

#include <QObject>
#include <string>
#include "../View/vuePlongeur.h"
#include "../Model/plongeur.h"

class ControleurPlongeur : public QObject {
    Q_OBJECT

public:
    ControleurPlongeur(VuePlongeur *vue, Plongeur *plongeur);
    ~ControleurPlongeur();

    void ajouterObjetSale(const std::string& objet);
    void nettoyerObjet();
    void afficherObjetsSales();

private:
    VuePlongeur *vue;
    Plongeur *plongeur;
};

#endif // CONTROLEURPLONGEUR_H