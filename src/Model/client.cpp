#include "client.h"
#include <iostream>
#include "chefDeRang.h"
#include "serveur.h"

Client::Client(const std::string& nom, TypeComportement comportement)
    : nom(nom), comportement(comportement) {}

void Client::passerCommande(const std::string& plat, ChefDeRang* chef) {
    if (plat.empty()) {
        std::cerr << "Erreur : le plat ne peut pas être vide.\n";
        return;
    }

    commande = plat;
    std::cout << nom << " (Client) passe la commande : " << plat << "\n";

    switch (comportement) {
        case EXIGEANT:
            std::cout << nom << " demande : Assurez-vous que le plat soit parfait !\n";
        break;
        case INDECIS:
            std::cout << nom << " hésite avant de choisir " << plat << ".\n";
        break;
        case PRESSE:
            std::cout << nom << " demande : Faites vite, s'il vous plaît !\n";
        break;
        case NORMAL:
            default:
                std::cout << nom << " passe calmement la commande.\n";
        break;
    }

    chef->prendreCommande(nom, plat);
}

void Client::demanderAssistance(Serveur* serveur) {
    std::cout << nom << " demande de l'aide au Serveur.\n";
    serveur->servirPlat();
}

void Client::afficherDetails() const {
    std::cout << "Client : " << nom << "\n";
    std::cout << "Comportement : ";
    switch (comportement) {
        case EXIGEANT:
            std::cout << "Exigeant\n";
        break;
        case INDECIS:
            std::cout << "Indécis\n";
        break;
        case PRESSE:
            std::cout << "Pressé\n";
        break;
        case NORMAL:
            std::cout << "Normal\n";
        break;
    }
    if (!commande.empty()) {
        std::cout << "Commande passée : " << commande << "\n";
    } else {
        std::cout << "Aucune commande passée.\n";
    }
}


