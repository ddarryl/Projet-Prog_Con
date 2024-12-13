#include "../Model/plongeur.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// Test de la classe Plongeur
class PlongeurTest : public ::testing::Test {
protected:
    Plongeur plongeur;

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

TEST_F(PlongeurTest, AjouterObjetSale) {
    plongeur.ajouterObjetSale("Assiette");
    EXPECT_EQ(plongeur.getObjetsSales().size(), 1);
    EXPECT_EQ(plongeur.getObjetsSales().front(), "Assiette");
}

TEST_F(PlongeurTest, NettoyerObjet) {
    plongeur.ajouterObjetSale("Assiette");
    plongeur.nettoyerObjet();
    EXPECT_EQ(plongeur.getObjetsSales().size(), 0);
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 1);
    EXPECT_EQ(plongeur.getObjetsNettoyes().front(), "Assiette");
}

TEST_F(PlongeurTest, NettoyerObjetSansObjet) {
    // Capturer la sortie de la tentative de nettoyage sans objet
    std::string output = captureOutput([&]() { plongeur.nettoyerObjet(); });
    EXPECT_EQ(output, "Plongeur: No items to clean.\n");
}

TEST_F(PlongeurTest, NettoyerObjets) {
    plongeur.ajouterObjetSale("Assiette");
    plongeur.ajouterObjetSale("Verre");
    plongeur.nettoyerObjets("Assiette", 1);
    EXPECT_EQ(plongeur.getObjetsSales().size(), 1); // Un objet reste
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 1); // Un objet nettoyé
}

TEST_F(PlongeurTest, NettoyerObjetsInexistants) {
    plongeur.ajouterObjetSale("Assiette");
    // Capturer la sortie de la tentative de nettoyage d'un objet inexistant
    std::string output = captureOutput([&]() { plongeur.nettoyerObjets("Verre", 1); });
    EXPECT_EQ(output, "Plongeur: No Verre to clean.\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}