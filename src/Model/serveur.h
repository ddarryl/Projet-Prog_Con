#ifndef SERVEUR_H
#define SERVEUR_H

#include <vector>
#include <string>
#include "ComptoirSocket.h" // Include the header for ComptoirSocket
#include "ressourceGestion.h" // Include the header for RessourceGestion

class Serveur {
public:
    Serveur();

    void recevoirPlat(const std::string& plat);
    void servirPlat();
    void afficherPlats() const;
    void deposerVaisselleSale(const std::string& plat, ComptoirSocket& comptoir); // Declare the function here
    void recevoirPlat(int msgQueueId);
    void utiliserConsommables(RessourceGestion& gestion, const std::string& item, int quantite); // Declare the function here

    std::vector<std::string> getPlatsEnAttente() const;
    std::vector<std::string> getPlatsServis() const;

private:
    std::vector<std::string> platsEnAttente;
    std::vector<std::string> platsServis;
};

#endif // SERVEUR_H