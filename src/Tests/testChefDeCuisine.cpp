#include "../Model/chefDeCuisine.h"
#include "../Model/commis.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

// Simuler la classe Commis pour les tests
class MockCommis : public Commis {
public:
    void preparerIngredient(const std::string& ingredient) {
        std::cout << "MockCommis: Prepared ingredient - " << ingredient << ".\n";
    }
};

// Test de la classe ChefDeCuisine
class ChefDeCuisineTest : public ::testing::Test {
protected:
    ChefDeCuisine chef;
    MockCommis commis;

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

TEST_F(ChefDeCuisineTest, AjouterCommande) {
    std::string output = captureOutput([&]() { chef.ajouterCommande("Pasta"); });
    EXPECT_NE(output.find("Chef de Cuisine: Added order for Pasta"), std::string::npos);
}

TEST_F(ChefDeCuisineTest, SuperviserPreparation) {
    chef.ajouterCommande("Salade");
    std::string output = captureOutput([&]() { chef.superviserPreparation(); });
    EXPECT_NE(output.find("Chef de Cuisine: Supervising preparation of Salade"), std::string::npos);
    EXPECT_NE(output.find("Chef de Cuisine: Salade is ready."), std::string::npos);
}

TEST_F(ChefDeCuisineTest, TousLesPlatsPrets) {
    EXPECT_FALSE(chef.tousLesPlatsPrets()); // Vérifie que tous les plats ne sont pas prêts
    chef.ajouterCommande("Dessert");
    chef.superviserPreparation();
    EXPECT_TRUE(chef.tousLesPlatsPrets()); // Vérifie que tous les plats sont prêts après la préparation
}

TEST_F(ChefDeCuisineTest, PreparerIngredients) {
    std::string output = captureOutput([&]() { chef.preparerIngredients(commis, "Tomate"); });
    EXPECT_NE(output.find("Chef de Cuisine: Asked commis to prepare Tomate"), std::string::npos);
}

TEST_F(ChefDeCuisineTest, GetPlatsPrets) {
    chef.ajouterCommande("Pizza");
    chef.superviserPreparation();
    auto platsPrets = chef.getPlatsPrets();
    EXPECT_EQ(platsPrets.size(), 1);
    EXPECT_EQ(platsPrets[0], "Pizza");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}