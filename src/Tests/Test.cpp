#include "../Model/maitreHotel.h"
#include "../Model/chefDeRang.h"
#include "../Model/serveur.h"
#include "../Model/cuisinier.h"
#include "../Model/plongeur.h"
#include "../Model/stockGestion.h"
#include "../Model/commis.h"
#include "../Model/chefDeCuisine.h"
#include "../Model/client.h"
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include "../../src/Controller/port_manager.h"

// Function to write logs
void logTest(const std::string& message) {
    std::ofstream logFile("test_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << "\n";
        logFile.close();
    } else {
        std::cerr << "Error: Unable to open log file.\n";
    }
}

// Complete simulation test
TEST(SimulationTest, ScenarioComplet) {
    logTest("Starting test: Complete scenario simulation");
    int port = getAvailablePort();

    // Initialize entities
    MaitreHotel maitre;
    ChefDeRang chef;
    Serveur serveur;
    Cuisinier cuisinier;
    Plongeur plongeur;
    StockGestion stock;
    Commis commis;
    ChefDeCuisine chefDeCuisine;
    ComptoirSocket comptoir(port); // Create an instance of ComptoirSocket

    // Step 1: Add client
    maitre.ajouterClient("Client 1");
    EXPECT_EQ(maitre.getNombreClients(), 1);
    logTest("Step 1: Client added to the waiting list.");

    // Step 2: Table assignment
    std::string clientAttribue = maitre.attribuerTable();
    EXPECT_EQ(clientAttribue, "Client 1");
    logTest("Step 2: Table assigned to the client.");

    // Step 3: Order taking by the Chef de Rang
    chef.prendreCommande("Client 1", "Entrée");
    chef.prendreCommande("Client 1", "Plat Principal");
    EXPECT_EQ(chef.getCommandes().size(), 2);
    logTest("Step 3: Orders taken by the Chef de Rang.");

    // Step 4: Service by the Server
    serveur.recevoirPlat("Entrée");
    serveur.recevoirPlat("Plat Principal");
    EXPECT_EQ(serveur.getPlatsEnAttente().size(), 2);
    serveur.servirPlat();
    serveur.servirPlat();
    EXPECT_EQ(serveur.getPlatsServis().size(), 2);
    logTest("Step 4: Dishes served by the Server.");

    // Step 5: Preparation by the Cook
    cuisinier.ajouterCommande("Entrée");
    cuisinier.ajouterCommande("Plat Principal");
    cuisinier.preparerPlat(comptoir); // Pass the comptoir parameter
    cuisinier.preparerPlat(comptoir); // Pass the comptoir parameter
    EXPECT_EQ(cuisinier.getPlatsEnPreparation().size(), 0);
    logTest("Step 5: Dishes prepared by the Cook.");

    // Step 6: Cleaning by the Dishwasher
    plongeur.ajouterObjetSale("Assiette");
    plongeur.nettoyerObjet();
    EXPECT_EQ(plongeur.getObjetsSales().size(), 0);
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 1);
    logTest("Step 6: Plate cleaned by the Dishwasher.");

    // Step 7: Stock management
    stock.consommer("Viande", 5);
    EXPECT_EQ(stock.getStock("Viande"), 5);
    EXPECT_TRUE(stock.alerteStock("Viande"));
    stock.reapprovisionner("Viande", 10);
    EXPECT_EQ(stock.getStock("Viande"), 15);
    logTest("Step 7: Stock management completed.");

    // Step 8: Test Commis
    commis.preparerIngredient("Tomate");
    EXPECT_EQ(commis.getIngredientsPrepares().size(), 1);
    logTest("Step 8: Ingredient prepared by Commis.");

    // Step 9: Test ChefDeCuisine
    chefDeCuisine.ajouterCommande("Pizza");
    EXPECT_EQ(chefDeCuisine.getPlatsPrets().size(), 0);
    chefDeCuisine.superviserPreparation();
    EXPECT_EQ(chefDeCuisine.getPlats