#ifndef MAITREHOTEL_H
#define MAITREHOTEL_H

#include <queue>
#include <string>

class MaitreHotel {
public:
    MaitreHotel();
    void ajouterClient(const std::string& client);
    std::string attribuerTable();
    int getNombreClients() const;
    bool estFileVide() const; // Nouvelle méthode pour vérifier si la file est vide

private:
    std::queue<std::string> fileClients;
};

#endif // MAITREHOTEL_H