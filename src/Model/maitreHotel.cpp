#include "maitreHotel.h"
#include <iostream>

MaitreHotel::MaitreHotel() {}

void MaitreHotel::ajouterClient(const std::string& client) {
    // Vérification du client
    if (client.empty()) {
        std::cerr << "Erreur : le nom du client ne peut pas être vide.\n";
        return;
    }

    fileClients.push(client);
    std::cout << "Client " << client << " ajouté à la file d'attente.\n";
}

std::string MaitreHotel::attribuerTable() {
    if (!fileClients.empty()) {
        std::string client = fileClients.front();
        fileClients.pop();
        return client;
    }
    return ""; // Retourne une chaîne vide si la file est vide
}

int MaitreHotel::getNombreClients() const {
    return fileClients.size();
}

bool MaitreHotel::estFileVide() const {
    return fileClients.empty(); // Retourne vrai si la file est vide
}