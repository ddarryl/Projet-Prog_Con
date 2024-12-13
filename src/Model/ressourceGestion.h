#ifndef RESSOURCE_GESTION_H
#define RESSOURCE_GESTION_H

#include <map>
#include <string>
#include <iostream>
#include <mutex>

class RessourceGestion {
public:
    RessourceGestion();

    // Manage stock
    void ajouterStock(const std::string& ressource, int quantite);
    bool consommerRessource(const std::string& ressource, int quantite);
    int obtenirStock(const std::string& ressource) const;
    bool verifierDisponibilite(const std::string& ressource, int quantite) const;

    // Table management
    bool reserverTable(int tableId);
    bool libererTable(int tableId);
    bool estTableDisponible(int tableId) const;

private:
    std::map<std::string, int> stock;      // Stock for consumables
    std::map<int, bool> tables;            // State of tables (true = available)
    mutable std::mutex mutexStock;         // Protect stock operations
    mutable std::mutex mutexTables;        // Protect table operations

    void log(const std::string& message) const; // Utility for logging
};

#endif // RESSOURCE_GESTION_H
