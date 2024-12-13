#include <QApplication>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include "../src/Model/commis.h"
#include "../src/Model/ressourceGestion.h"
#include "../src/Model/carte_restaurant.h"
#include "../src/Model/stockGestion.h"
#include "../src/Model/dressage.h"
#include "../src/Model/Recette.h"
#include "../src/Model/client.h"
#include "../src/Model/serviceManager.h"
#include "../src/Model/chefDeCuisine.h"
#include "../src/Model/chefDeRang.h"
#include "../src/Model/serveur.h"
#include "../src/Model/plongeur.h"
#include "../Pools/resourcePool.h"
#include "../src/Controller/port_manager.h"
#include "../src/Controller/controlleurMaitreHotel.h"
#include "../src/Controller/controlleurChefDeRang.h"
#include "../src/ipc/ipc_utils.h"
#include "Model/ComptoirSocket.h"
#include "Model/utils.h"
#include "View/mainwindow.h"
#include "Model/cuisinier.h"

void prepareDish(std::shared_ptr<utils> resource, const std::string& dish);
void simulateChefActions(ChefDeCuisine& chefDeCuisine, Commis& commis, Cuisinier& cuisinier, ComptoirSocket& comptoir);
void simulateClientDeparture(int tableId, RessourceGestion& gestion, Plongeur& plongeur, MaitreHotel& maitre);
void chefTask(int msgQueueId);
void cuisinierTask(int msgQueueId);
void disposerSauce();
void ajouterGarniture();
void positionnerViande();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Resource management initialization
    RessourceGestion gestion;
    ServiceManager manager;
    StockGestion gest;
    Recette recette("Soupe aux légumes");
    Dressage dressage(3);
    CarteRestaurant carte;
    ResourcePool<std::shared_ptr<utils>> resourcePool(5, createResource);

    int port = getAvailablePort();
    key_t keyMsgQueue = ftok("msgqueue", 65);
    key_t keySem = ftok("sem", 75);

    // Create IPCs (Inter-process communication)
    int msgQueueId = createMessageQueue(keyMsgQueue);
    int semId = createSemaphore(keySem);

    // Initialize key roles (Actors in the restaurant workflow)
    ChefDeCuisine chefDeCuisine;
    Commis commis;
    MaitreHotel maitre;
    ChefDeRang chefDeRang;
    Cuisinier cuisinier;
    Serveur serveur;

    // Create the ComptoirSocket for communication
    ComptoirSocket comptoir(port);

    // Simulate actions in threads (Chef de Cuisine action simulation)
    std::thread chefThread(simulateChefActions, std::ref(chefDeCuisine), std::ref(commis), std::ref(cuisinier), std::ref(comptoir));
    chefThread.join();

    // Process IPC in different forks
    Plongeur plongeur;

    if (fork() == 0) {
        // Chef de Rang sends orders
        semaphoreWait(semId);
        chefDeRang.envoyerCommande("Pasta", msgQueueId);
        chefDeRang.envoyerCommande("Soup", msgQueueId);
        semaphoreSignal(semId);
    } else if (fork() == 0) {
        // Cuisinier receives orders
        cuisinier.recevoirCommande(msgQueueId);
        sendMessage(msgQueueId, "Pasta Ready", 2);
        sendMessage(msgQueueId, "Soup Ready", 2);
    } else {
        // Serveur receives ready dishes
        serveur.recevoirPlat(msgQueueId);
        serveur.recevoirPlat(msgQueueId);
    }

    // Prepare and serve dishes
    ComptoirSocket vaisselleComptoir(port);
    ComptoirSocket repasComptoir(port);
    vaisselleComptoir.start();
    repasComptoir.start();

    // Maitre d'hotel manages clients
    maitre.ajouterClient("Client 1");
    maitre.ajouterClient("Client 2");
    maitre.ajouterClient("Client 3");
    maitre.afficherFile();
    maitre.attribuerTable();
    maitre.attribuerTable();
    maitre.afficherFile();

    // Chef de Rang takes orders and coordinates with the Cuisinier
    chefDeRang.prendreCommande("Client 1", "Entrée");
    chefDeRang.prendreCommande("Client 1", "Plat Principal");
    chefDeRang.afficherCommandes();
    for (const auto& commande : chefDeRang.getCommandes()) {
        cuisinier.ajouterCommande(commande);
    }

    // Prepare the dishes
    cuisinier.preparerPlat(comptoir);
    cuisinier.preparerPlat(comptoir);

    // Serve the dishes
    cuisinier.ajouterRepasPret("Soup", repasComptoir);
    cuisinier.ajouterRepasPret("Steak", repasComptoir);

    // Fetch items from the counters
    std::cout << "Serveur: Serving dish - " << comptoir.getItem() << std::endl;
    std::cout << "Serveur: Serving dish - " << comptoir.getItem() << std::endl;

    // Serveur serves the dishes
    for (const auto& plat : cuisinier.getPlatsEnPreparation()) {
        serveur.recevoirPlat(plat);
    }
    serveur.servirPlat();
    serveur.servirPlat();
    serveur.afficherPlats();

    // Simulate dirty dishes
    serveur.deposerVaisselleSale("Plate", vaisselleComptoir);
    serveur.deposerVaisselleSale("Glass", vaisselleComptoir);

    // Fetch and display dishes
    std::cout << "Dishes to clean:" << std::endl;
    for (const auto& dish : vaisselleComptoir.getAllItems()) {
        std::cout << "- " << dish << std::endl;
    }

    // Clients place orders
    Client client1("Alice", Client::NORMAL);
    client1.passerCommande("Entrée", &chefDeRang);
    chefDeRang.afficherCommandes();
    client1.demanderAssistance(&serveur);
    client1.afficherDetails();

    // Table management
    maitre.gererTables(gestion, 1);
    maitre.gererTables(gestion, 2);

    // Resource consumption and restocking
    serveur.utiliserConsommables(gestion, "Assiettes", 5);
    serveur.utiliserConsommables(gestion, "Verres", 10);
    commis.reapprovisionner(gestion, "Assiettes", 20);
    commis.reapprovisionner(gestion, "Nappes", 5);

    // Launch the main window for UI interaction
    MainWindow w;
    w.show();

    // Enter the application event loop
    return a.exec();
}
