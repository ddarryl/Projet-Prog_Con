#include "port_manager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int exportedPort = 0; // Port choisi et réservé
int reservedSocket = -1; // Socket réservé pour maintenir le port

int getAvailablePort(int minPort, int maxPort) {
    std::srand(std::time(nullptr)); // Initialiser la graine aléatoire

    int port = 0;
    const int maxAttempts = 100; // Limite de tentatives
    int attempts = 0;

    while (attempts < maxAttempts) {
        port = minPort + (std::rand() % (maxPort - minPort + 1));

        // Créer un socket pour tenter de lier le port
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cerr << "Erreur de création du socket." << std::endl;
            return -1;
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        // Essayer de lier le socket au port
        if (bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0) {
            // Si l'opération bind réussit, cela signifie que le port est libre
            exportedPort = port; // Sauvegarder le port
            reservedSocket = sock; // Garder le socket ouvert pour sécuriser le port
            std::cout << "Port sécurisé : " << exportedPort << std::endl;
            return port; // Retourner le port sécurisé
        }

        close(sock); // Fermer le socket si le port n'est pas libre
        attempts++;
    }

    std::cerr << "Aucun port libre trouvé après " << maxAttempts << " tentatives." << std::endl;
    return -1; // Aucun port libre trouvé
}