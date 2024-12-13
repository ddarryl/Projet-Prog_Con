#include "maitreHotel.h"
#include <iostream>

MaitreHotel::MaitreHotel() {
    tablesDisponibles = {"Table 1", "Table 2", "Table 3", "Table 4", "Table 5"};
}

void MaitreHotel::ajouterClient(const std::string& client) {
    fileClients.push(client);
    std::cout << "Client " << client << " ajouté à la file d'attente.\n";
}

std::string MaitreHotel::attribuerTable() {
    if (fileClients.empty()) {
        std::cout << "Aucun client dans la file d'attente.\n";
        return "";
    }

    std::string client = fileClients.front();
    fileClients.pop();

    if (!tablesDisponibles.empty()) {
        std::string tableAttribuee = tablesDisponibles.back();
        tablesDisponibles.pop_back();
        std::cout << "Table attribuée à " << client << ": " << tableAttribuee << "\n";
        return client + " a été attribué à " + tableAttribuee;
    } else {
        std::cout << "Aucune table disponible.\n";
        return "";
    }
}

bool MaitreHotel::estFileVide() const {
    return fileClients.empty();
}

int MaitreHotel::getNombreClients() const {
    return fileClients.size();
}

void MaitreHotel::afficherFile() const {
    std::queue<std::string> copy = fileClients;
    if (copy.empty()) {
        std::cout << "Aucun client dans la file d'attente.\n";
    } else {
        std::cout << "Clients dans la file d'attente:\n";
        while (!copy.empty()) {
            std::cout << copy.front() << "\n";
            copy.pop();
        }
    }
}

void MaitreHotel::gererTables(RessourceGestion& gestion, int tableId) {
    if (gestion.estTableDisponible(tableId)) {
        gestion.reserverTable(tableId);
    } else {
        gestion.libererTable(tableId);
    }
}

void MaitreHotel::departClient(int tableId, RessourceGestion& gestion) {
    // Vérifie si la table existe et est occupée
    if (!gestion.estTableDisponible(tableId)) {
        std::cout << "Client from table " << tableId << " is leaving.\n";

        // Ajout des ressources utilisées au comptoir des objets sales
        gestion.consommerRessource("Assiettes", 4); // Exemple: 4 assiettes utilisées
        gestion.consommerRessource("Verres", 4);   // Exemple: 4 verres utilisés
        gestion.consommerRessource("Nappes", 1);   // Exemple: 1 nappe utilisée

        // Libération de la table
        gestion.libererTable(tableId);

        std::cout << "Table " << tableId << " is now clean and available.\n";
    } else {
        std::cerr << "Error: Table " << tableId << " is already available.\n";
    }
}