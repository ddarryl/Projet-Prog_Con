#ifndef CONTROLEURCHEFDERANG_H
#define CONTROLEURCHEFDERANG_H

#include <QObject>
#include <string>
#include "../View/vueChefDeRang.h"
#include "../Model/chefDeRang.h"

class ControleurChefDeRang : public QObject {
    Q_OBJECT

public:
    ControleurChefDeRang(VueChefDeRang *vue, ChefDeRang *chefDeRang);
    ~ControleurChefDeRang();

    void prendreCommande(const std::string& client, const std::string& plat);
    void afficherCommandes();

private:
    VueChefDeRang *vue;
    ChefDeRang *chefDeRang;
};

#endif // CONTROLEURCHEFDERANG_H