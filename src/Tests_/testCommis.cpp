#include "../Model/commis.h"
#include "../Model/ressourceGestion.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Test de la classe Commis
class CommisTest : public ::testing::Test {
protected:
    Commis commis;
    RessourceGestion gestion;

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

TEST_F(CommisTest, PreparerIngredient) {
    std::string output = captureOutput([&]() { commis.preparerIngredient("Tomate"); });
    EXPECT_EQ(output, "Commis: Prepared ingredient - Tomate.\n");
}

TEST_F(CommisTest, PreparerIngredientVide) {
    std::string output = captureOutput([&]() { commis.preparerIngredient(""); });
    EXPECT_EQ(output, "Error: Ingredient cannot be empty.\n");
}

TEST_F(CommisTest, RangerUstensile) {
    std::string output = captureOutput([&]() { commis.rangerUstensile("Couteau"); });
    EXPECT_EQ(output, "Commis: Stored utensil - Couteau.\n");
}

TEST_F(CommisTest, RangerUstensileVide) {
    std::string output = captureOutput([&]() { commis.rangerUstensile(""); });
    EXPECT_EQ(output, "Error: Utensil cannot be empty.\n");
}

TEST_F(CommisTest, AiderChefDeRang) {
    std::string output = captureOutput([&]() { commis.aiderChefDeRang("Commande 1"); });
    EXPECT_EQ(output, "Commis: Assisted with command - Commande 1.\n");
}

TEST_F(CommisTest, AiderChefDeRangVide) {
    std::string output = captureOutput([&]() { commis.aiderChefDeRang(""); });
    EXPECT_EQ(output, "Error: Command cannot be empty.\n");
}

TEST_F(CommisTest, Reapprovisionner) {
    std::string output = captureOutput([&]() { commis.reapprovisionner(gestion, "Viande", 10); });
    EXPECT_EQ(output, "Commis: Restocked 10 of Viande.\n");
    EXPECT_EQ(gestion.obtenirStock("Viande"), 10); // Vérifie que le stock a été mis à jour
}

TEST_F(CommisTest, AfficherTaches) {
    commis.preparerIngredient("Oignon");
    commis.rangerUstensile("Fouet");
    commis.aiderChefDeRang("Commande 2");

    std::string output = captureOutput([&]() { commis.afficherTaches(); });

    EXPECT_NE(output.find("Commis: Completed tasks:"), std::string::npos);
    EXPECT_NE(output.find("Prepared ingredients:"), std::string::npos);
    EXPECT_NE(output.find("Stored utensils:"), std::string::npos);
    EXPECT_NE(output.find("Assisted commands:"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}