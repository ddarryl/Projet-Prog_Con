#ifndef SERVEUR_H
#define SERVEUR_H

#include <vector>
#include <string>

class Serveur {
public:
    Serveur();
    void recevoirPlat(const std::string& plat);
    void servirPlat();
    std::vector<std::string> getPlatsEnAttente() const; // Renommé pour plus de clarté
    std::vector<std::string> getPlatsServis() const; // Nouvelle méthode pour obtenir les plats servis

private:
    std::vector<std::string> platsEnAttente; // Nouveau vecteur pour les plats en attente
    std::vector<std::string> platsServis; // Nouveau vecteur pour les plats servis
};

#endif // SERVEUR_H