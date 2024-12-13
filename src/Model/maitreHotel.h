#ifndef MAITRE_HOTEL_H
#define MAITRE_HOTEL_H

#include <queue>
#include <string>
#include <vector>
#include "ressourceGestion.h"

class MaitreHotel {
public:
    MaitreHotel();
    void ajouterClient(const std::string& client);
    std::string attribuerTable();
    bool estFileVide() const;
    int getNombreClients() const;
    void afficherFile() const; // Declare the function here
    void gererTables(RessourceGestion& gestion, int tableId);
    void departClient(int tableId, RessourceGestion& gestion);

private:
    std::queue<std::string> fileClients; // Queue to hold clients
    std::vector<std::string> tablesDisponibles; // Vector to hold available tables
};

#endif // MAITRE_HOTEL_H