#ifndef CONTROLEURCUISINIER_H
#define CONTROLEURCUISINIER_H

#include <QObject>
#include <string>
#include "../View/vueCuisinier.h"
#include "../Model/cuisinier.h"

class ControleurCuisinier : public QObject {
    Q_OBJECT

public:
    ControleurCuisinier(VueCuisinier *vue, Cuisinier *cuisinier);
    ~ControleurCuisinier();

    void ajouterCommande(const std::string& commande);
    void preparerPlat();
    void afficherPlatsEnPreparation();

private:
    VueCuisinier *vue;
    Cuisinier *cuisinier;
};

#endif // CONTROLEURCUISINIER_H