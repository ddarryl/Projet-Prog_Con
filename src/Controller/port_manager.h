#ifndef PORT_MANAGER_H
#define PORT_MANAGER_H

extern int exportedPort; // Déclaration de la variable globale
extern int reservedSocket; // Déclaration de la variable pour le socket réservé
int getAvailablePort(int minPort = 1024, int maxPort = 65535);

#endif // PORT_MANAGER_H
