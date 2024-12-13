#include "View/mainwindow.h"
#include "../src/View/vueMaitreHotel.h"
#include "../src/Controller/controlleurMaitreHotel.h"
#include "../src/Model/maitreHotel.h"
#include "../src/Controller/controlleurChefDeRang.h"
#include "../src/Model/chefDeRang.h"
#include "../src/Controller/controlleurServeur.h"
#include "../src/Model/serveur.h"
#include "../src/Model/cuisinier.h"
#include "../src/Model/plongeur.h"
#include "../src/Model/Recette.h"
#include "../src/Model/client.h"
#include <QApplication>
#include "Model/commis.h"
#include "Model/ComptoirSocket.h"
#include "../src/ipc/ipc_utils.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "Model/assiette.h"
#include "Model/ressourceGestion.h"
#include "../Pools/resourcePool.h"
#include "Model/table.h"
#include "../Pools/threadPool.h"
#include "Model/chefDeCuisine.h"
#include "../src/Model/serviceManager.h"
#include "Model/utils.h"
#include "../src/Model/dressage.h"
#include "../src/Model/carte_restaurant.h"
#include "../src/Model/stockGestion.h"


void prepareDish(std::shared_ptr<utils> resource, const std::string& dish);
void simulateChefActions(ChefDeCuisine& chefDeCuisine, Commis& commis, Cuisinier& cuisinier, ComptoirSocket& comptoir);
void simulateClientDeparture(int tableId, RessourceGestion& gestion, Plongeur& plongeur, MaitreHotel& maitre) {
    maitre.departClient(tableId, gestion);

    // Simule le nettoyage des ressources
    plongeur.nettoyerObjets("Assiettes", 4);
    plongeur.nettoyerObjets("Verres", 4);
    plongeur.nettoyerObjets("Nappes", 1);
}

void chefTask(int msgQueueId) {
    sendMessage(msgQueueId, "Order: Pasta", 1);
    sendMessage(msgQueueId, "Order: Salad", 1);
    std::cout << "Chef: Orders sent.\n";
}

void cuisinierTask(int msgQueueId) {
    std::string order1 = receiveMessage(msgQueueId, 1);
    std::string order2 = receiveMessage(msgQueueId, 1);
    std::cout << "Cuisinier: Received - " << order1 << "\n";
    std::cout << "Cuisinier: Received - " << order2 << "\n";
}

void disposerSauce() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Sauce disposed on the plate.\n";
}

void ajouterGarniture() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Garnish added to the plate.\n";
}

void positionnerViande() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Meat positioned on the plate.\n";
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RessourceGestion gestion;
    StockGestion manager;
    Recette recette("Soupe aux légumes");
    Dressage dressage(3);
    CarteRestaurant carte;
    ResourcePool<std::shared_ptr<utils>> resourcePool(5, createResource);

    key_t keyMsgQueue = ftok("msgqueue", 65);
    key_t keySem = ftok("sem", 75);

    // Create IPCs
    int msgQueueId = createMessageQueue(keyMsgQueue);
    int semId = createSemaphore(keySem);

    // Initialize key roles
    ChefDeCuisine chefDeCuisine; // Renamed variable
    Commis commis;
    MaitreHotel maitre;
    ChefDeRang chefDeRang; // Renamed variable
    Cuisinier cuisinier;
    Serveur serveur;

    ComptoirSocket comptoir(8080);
    std::thread chefThread(simulateChefActions, std::ref(chefDeCuisine), std::ref(commis), std::ref(cuisinier), std::ref(comptoir));
    chefThread.join();

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
        sendMessage(msgQueueId, "Pasta Ready", 2); // Send ready dish
        sendMessage(msgQueueId, "Soup Ready", 2);  // Send ready dish
    } else {
        // Serveur receives ready dishes
        serveur.recevoirPlat(msgQueueId);
        serveur.recevoirPlat(msgQueueId);
    }

    ComptoirSocket vaisselleComptoir(8080);
    ComptoirSocket repasComptoir(8081);
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

    cuisinier.ajouterCommande("Soupe");
    cuisinier.ajouterCommande("Steak");
    cuisinier.ajouterCommande("Salade");
    // Cuisinier prepares the dishes
    cuisinier.preparerPlat(comptoir);
    cuisinier.preparerPlat(comptoir);
    // Simulate ready dishes
    cuisinier.ajouterRepasPret("Soup", repasComptoir);
    cuisinier.ajouterRepasPret("Steak", repasComptoir);

    // Récupération des plats prêts au comptoir
    std::cout << "Serveur: Serving dish - " << comptoir.getItem() << std::endl;
    std::cout << "Serveur: Serving dish - " << comptoir.getItem() << std::endl;

    // Serveur receives and serves the dishes
    for (const auto& plat : cuisinier.getPlatsEnPreparation()) {
        serveur.recevoirPlat(plat);
    }
    serveur.servirPlat();
    serveur.servirPlat();
    serveur.afficherPlats();
    // Simulate dirty dishes
    serveur.deposerVaisselleSale("Plate", vaisselleComptoir);
    serveur.deposerVaisselleSale("Glass", vaisselleComptoir);

    // Fetch items from the counters
    std::cout << "Dishes to clean:" << std::endl;
    for (const auto& dish : vaisselleComptoir.getAllItems()) {
        std::cout << "- " << dish << std::endl;
    }

    std::cout << "Dishes ready to serve:" << std::endl;
    for (const auto& meal : repasComptoir.getAllItems()) {
        std::cout << "- " << meal << std::endl;
    }

    // Commis assists in preparation and serving
    commis.preparerIngredient("Tomates");
    commis.preparerIngredient("Oignons");
    commis.preparerIngredient("Poulet");

    cuisinier.ajouterCommande("Poulet aux Oignons");
    cuisinier.preparerPlat(comptoir);
    chefDeRang.prendreCommande("Client 1", "Poulet aux Oignons");

    commis.aiderChefDeRang("Poulet aux Oignons pour Client 1");
    commis.afficherTaches();

    // Clients place orders and interact with the system
    Client client1("Alice", Client::NORMAL);
    Client client2("Bob", Client::EXIGEANT);
    Client client3("Charlie", Client::INDECIS);
    Client client4("Diane", Client::PRESSE);
    client1.passerCommande("Entrée", &chefDeRang);
    client2.passerCommande("Plat Principal", &chefDeRang);
    client3.passerCommande("Dessert", &chefDeRang);
    client4.passerCommande("Boisson", &chefDeRang);
    chefDeRang.afficherCommandes();
    client1.demanderAssistance(&serveur);
    client2.demanderAssistance(&serveur);
    client1.afficherDetails();
    client2.afficherDetails();
    client3.afficherDetails();
    client4.afficherDetails();

    vaisselleComptoir.stop();
    repasComptoir.stop();


    // Table management
    maitre.gererTables(gestion, 1);
    maitre.gererTables(gestion, 2);

    // Resource consumption
    serveur.utiliserConsommables(gestion, "Assiettes", 5);
    serveur.utiliserConsommables(gestion, "Verres", 10);

    // Restocking
    commis.reapprovisionner(gestion, "Assiettes", 20);
    commis.reapprovisionner(gestion, "Nappes", 5);

    auto createAssiette = []() -> Assiette* {
        static int id = 1;
        return new Assiette(id++);
    };

    ResourcePool<Assiette*> assiettePool(10, createAssiette);

    Assiette* a1 = assiettePool.acquire();
    std::cout << "Using plate: " << a1->id << std::endl;

    assiettePool.release(a1);

    auto createTable = []() -> Table* {
        static int id = 1;
        return new Table(id++);
    };

    ResourcePool<Table*> tablePool(5, createTable);

    // Acquire a table
    Table* table1 = tablePool.acquire();
    std::cout << "Table reserved: " << table1->id << std::endl;
    table1->reserved = true;

    // Release the table
    table1->reserved = false;
    tablePool.release(table1);

    ThreadPool threadPool(3); // 3 threads in the pool

    // Enqueue tasks to prepare dishes
    threadPool.enqueueTask([&resourcePool] {
        auto resource = resourcePool.acquire();
        prepareDish(resource, "Pasta");
        resourcePool.release(resource);
    });
    threadPool.enqueueTask([&resourcePool] {
        auto resource = resourcePool.acquire();
        prepareDish(resource, "Soup");
        resourcePool.release(resource);
    });
    threadPool.enqueueTask([&resourcePool] {
        auto resource = resourcePool.acquire();
        prepareDish(resource, "Salad");
        resourcePool.release(resource);
    });

    // Wait for a moment to let tasks complete
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // Add dishes for table 1
    manager.ajouterPlat(1, "Soup");
    manager.ajouterPlat(1, "Steak");
    manager.ajouterPlat(1, "Salad");

    // Prepare dishes in parallel
    std::thread t1(&StockGestion::preparerPlat, std::ref(manager), 1, "Soup");
    std::thread t2(&StockGestion::preparerPlat, std::ref(manager), 1, "Steak");
    std::thread t3(&StockGestion::preparerPlat, std::ref(manager), 1, "Salad");

    // Serve table 1
    manager.servirTable(1);

    // Join threads
    t1.join();
    t2.join();
    t3.join();

    std::thread t_client_departure(simulateClientDeparture, 1, std::ref(gestion), std::ref(plongeur), std::ref(maitre));
    // Wait for the client departure thread to finish
    t_client_departure.join();

    std::thread t_chef_thread(&simulateChefActions,
                           std::ref(chefDeCuisine),
                           std::ref(commis),
                           std::ref(cuisinier),
                           std::ref(comptoir));
    t_chef_thread.join();

    // Add dirty items
    plongeur.ajouterObjetSale("Plate");
    plongeur.ajouterObjetSale("Glass");
    plongeur.ajouterObjetSale("Plate");
    plongeur.ajouterObjetSale("Napkin");

    // Clean one item
    plongeur.nettoyerObjet();

    // Clean multiple items
    plongeur.nettoyerObjets("Plate", 2);

    // Display the remaining dirty and cleaned items
    std::cout << "Remaining dirty items:\n";
    for (const auto& item : plongeur.getObjetsSales()) {
        std::cout << "- " << item << "\n";
    }

    std::cout << "Cleaned items:\n";
    for (const auto& item : plongeur.getObjetsNettoyes()) {
        std::cout << "- " << item << "\n";
    }

    comptoir.start();

    // Simulate adding items
    comptoir.addItem("Soup");
    comptoir.addItem("Steak");

    // Retrieve items
    std::cout << "Serving dish: " << comptoir.getItem() << std::endl;
    std::cout << "Serving dish: " << comptoir.getItem() << std::endl;

    comptoir.stop();

    gestion.ajouterStock("Assiettes", 10);
    gestion.ajouterStock("Casseroles", 5);
    gestion.consommerRessource("Casseroles", 2);
    gestion.consommerRessource("Fours", 1);
    gestion.consommerRessource("Assiettes", 5);
    gestion.consommerRessource("Verres", 60); // Test de limite
    gestion.ajouterStock("Plaques de cuisson", 3);
    gestion.consommerRessource("Plaques de cuisson", 1);
    if (gestion.verifierDisponibilite("Casseroles", 1) &&
    gestion.verifierDisponibilite("Plaques de cuisson", 1)) {
        gestion.consommerRessource("Casseroles", 1);
        gestion.consommerRessource("Plaques de cuisson", 1);
        std::cout << "Préparation du plat en cours...\n";
    } else {
        std::cerr << "Ressources insuffisantes pour préparer le plat !\n";
    }

    gestion.reserverTable(1);
    gestion.libererTable(1);
    gestion.libererTable(1); // Test de limite

    // Add steps
    recette.ajouterEtape(std::make_shared<EtapeRecette>(
        "Éplucher les légumes", 5, []() { std::cout << "Légumes épluchés.\n"; }));

    recette.ajouterEtape(std::make_shared<EtapeRecette>(
        "Couper les légumes", 3, []() { std::cout << "Légumes coupés.\n"; }));

    recette.ajouterEtape(std::make_shared<EtapeRecette>(
        "Faire bouillir l'eau", 4, []() { std::cout << "Eau bouillie.\n"; }));

    recette.ajouterEtape(std::make_shared<EtapeRecette>(
        "Ajouter les légumes à l'eau", 2, []() { std::cout << "Légumes ajoutés.\n"; }));
    // Execute sequentially
    recette.executer();

    dressage.ajouterTache("Disposing Sauce", disposerSauce);
    dressage.ajouterTache("Adding Garnish", ajouterGarniture);
    dressage.ajouterTache("Positioning Meat", positionnerViande);
    dressage.executerTaches();

    // Charger la carte depuis un fichier JSON
    carte.chargerCarte("menu.json");
    // Afficher la carte
    carte.afficherCarte();
    // Ajouter une nouvelle recette
    carte.ajouterRecette("Plats", "Pizza Margherita");
    // Sauvegarder la carte mise à jour
    carte.sauvegarderCarte("menu.json");

    // Launch main window
    MainWindow w;
    w.show();

    return a.exec();
}
