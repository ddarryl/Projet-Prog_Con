#include "../Model/maitreHotel.h"
#include "../Model/chefDeRang.h"
#include "../Model/serveur.h"
#include "../Model/cuisinier.h"
#include "../Model/plongeur.h"
#include "../Model/stockGestion.h"
#include <gtest/gtest.h>

TEST(SimulationTest, ScenarioComplet) {
    // Création des objets
    MaitreHotel maitre;
    ChefDeRang chef;
    Serveur serveur;
    Cuisinier cuisinier;
    Plongeur plongeur;
    StockGestion stock;

    // Scénario
    maitre.ajouterClient("Client 1");
    EXPECT_EQ(maitre.getNombreClients(), 1);
    std::string clientAttribue = maitre.attribuerTable();
    EXPECT_EQ(clientAttribue, "Client 1");

    chef.prendreCommande("Client 1", "Entrée");
    chef.prendreCommande("Client 1", "Plat Principal");
    EXPECT_EQ(chef.getCommandes().size(), 2);

    serveur.recevoirPlat("Entrée");
    serveur.recevoirPlat("Plat Principal");
    EXPECT_EQ(serveur.getPlatsServis().size(), 2);

    cuisinier.ajouterCommande("Entrée");
    cuisinier.ajouterCommande("Plat Principal");
    cuisinier.preparerPlat();
    cuisinier.preparerPlat();

    plongeur.ajouterObjetSale("Assiette");
    plongeur.nettoyerObjet();
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 0);

    stock.consommer("Viande", 5);
    EXPECT_EQ(stock.getStock("Viande"), 5);
    EXPECT_TRUE(stock.alerteStock("Viande"));
}
