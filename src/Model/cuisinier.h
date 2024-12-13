#ifndef CUISINIER_H
#define CUISINIER_H

#include <vector>
#include <string>
#include "ComptoirSocket.h"

class Cuisinier {
public:
    Cuisinier();
    void ajouterCommande(const std::string& commande);
    void preparerPlat(ComptoirSocket& comptoir);
    std::vector<std::string> getPlatsEnPreparation() const;
    void recevoirCommande(int msgQueueId);
    void ajouterRepasPret(const std::string& plat, ComptoirSocket& comptoir);

private:
    std::vector<std::string> platsEnPreparation;
};

#endif // CUISINIER_H