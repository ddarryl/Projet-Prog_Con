#include "../Model/chefDeCuisine.h"
#include "../Model/commis.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// Test de la classe ChefDeCuisine
class ChefDeCuisineTest : public ::testing::Test {
protected:
    ChefDeCuisine chef;
    Commis commis; // Instance de Commis pour les tests

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
    chef.ajouterCommande("Plat principal");
    EXPECT_EQ(chef.getPlatsPrets().size(), 0); // Aucune plat prêt au départ
}

TEST_F(ChefDeCuisineTest, SuperviserPreparation) {
    chef.ajouterCommande("Plat principal");

    // Capturer la sortie de la supervision de la préparation
    std::string output = captureOutput([&]() { chef.superviserPreparation(); });

    EXPECT_NE(output.find("Chef de Cuisine: Supervising preparation of Plat principal"), std::string::npos);
    EXPECT_EQ(chef.getPlatsPrets().size(), 1); // Un plat prêt après la préparation
}

TEST_F(ChefDeCuisineTest, TousLesPlatsPrets) {
    EXPECT_FALSE(chef.tousLesPlatsPrets()); // Aucun plat prêt au départ
    chef.ajouterCommande("Plat principal");
    chef.superviserPreparation(); // Préparer le plat
    EXPECT_TRUE(chef.tousLesPlatsPrets()); // Tous les plats sont prêts après la préparation
}

TEST_F(ChefDeCuisineTest, PreparerIngredients) {
    // Capturer la sortie de la préparation des ingrédients
    std::string output = captureOutput([&]() { chef.preparerIngredients(commis, "Tomates"); });

    EXPECT_NE(output.find("Chef de Cuisine: Asked commis to prepare Tomates"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}