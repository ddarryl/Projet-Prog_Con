#include "../Model/client.h"
#include "../Model/chefDeRang.h"
#include "../Model/serveur.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Simuler la classe ChefDeRang pour les tests
class MockChefDeRang : public ChefDeRang {
public:
    void prendreCommande(const std::string& nomClient, const std::string& plat) {
        std::cout << "ChefDeRang: Commande prise de " << nomClient << " pour " << plat << ".\n";
    }
};

// Simuler la classe Serveur pour les tests
class MockServeur : public Serveur {
public:
    void servirPlat() {
        std::cout << "Serveur: Plat servi.\n";
    }
};

// Test de la classe Client
class ClientTest : public ::testing::Test {
protected:
    MockChefDeRang chef;
    MockServeur serveur;
    Client client{"Alice", Client::NORMAL};

    // Fonction d'aide pour capturer la sortie de la console
    std::string captureOutput(std::function<void()> func) {
        std::streambuf* oldCoutBuffer = std::cout.rdbuf();
        std::ostringstream oss;
        std::cout.rdbuf(oss.rdbuf()); // Rediriger std::cout vers oss

        func(); // Exécuter la fonction

        std::cout.rdbuf(oldCoutBuffer); // Rétablir std::cout
        return oss.str(); // Retourner la sortie capturée
    }
};

TEST_F(ClientTest, PasserCommande) {
    std::string output = captureOutput([&]() { client.passerCommande("Pasta", &chef); });
    EXPECT_NE(output.find("Alice (Client) passe la commande : Pasta"), std::string::npos);
    EXPECT_NE(output.find("ChefDeRang: Commande prise de Alice pour Pasta."), std::string::npos);
}

TEST_F(ClientTest, PasserCommandeVide) {
    std::string output = captureOutput([&]() { client.passerCommande("", &chef); });
    EXPECT_EQ(output, "Erreur : le plat ne peut pas être vide.\n");
}

TEST_F(ClientTest, DemanderAssistance) {
    std::string output = captureOutput([&]() { client.demanderAssistance(&serveur); });
    EXPECT_NE(output.find("Alice demande de l'aide au Serveur."), std::string::npos);
    EXPECT_NE(output.find("Serveur: Plat servi."), std::string::npos);
}

TEST_F(ClientTest, AfficherDetails) {
    client.passerCommande("Salade", &chef);
    std::string output = captureOutput([&]() { client.afficherDetails(); });

    EXPECT_NE(output.find("Client : Alice"), std::string::npos);
    EXPECT_NE(output.find("Comportement : Normal"), std::string::npos);
    EXPECT_NE(output.find("Commande passée : Salade"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}