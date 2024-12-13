#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "chefDeRang.h" // Include the header for ChefDeRang
#include "serveur.h"    // Include the header for Serveur

class Client {
public:
    enum TypeComportement {
        EXIGEANT,
        INDECIS,
        PRESSE,
        NORMAL
    };

    Client(const std::string& nom, TypeComportement comportement);

    void passerCommande(const std::string& plat, ChefDeRang* chef);
    void demanderAssistance(Serveur* serveur);
    void afficherDetails() const;

private:
    std::string nom;
    TypeComportement comportement;
    std::string commande;
};

#endif // CLIENT_H