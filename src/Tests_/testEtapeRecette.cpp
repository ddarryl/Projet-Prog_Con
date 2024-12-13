#include "../Model/Recette.h"
#include "../Model/EtapeRecette.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Test de la classe Recette
class RecetteTest : public ::testing::Test {
protected:
    Recette recette{"Test Recipe"};

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

TEST_F(RecetteTest, AjouterEtape) {
    auto etape1 = std::make_shared<EtapeRecette>("Chop vegetables", 1);
    auto etape2 = std::make_shared<EtapeRecette>("Boil water", 2);
    
    recette.ajouterEtape(etape1);
    recette.ajouterEtape(etape2);

    EXPECT_EQ(recette.getEtapes().size(), 2); // Vérifie que deux étapes ont été ajoutées
}

TEST_F(RecetteTest, Executer) {
    auto etape1 = std::make_shared<EtapeRecette>("Chop vegetables", 1);
    recette.ajouterEtape(etape1);

    std::string output = captureOutput([&]() { recette.executer(); });

    EXPECT_NE(output.find("Executing recipe: Test Recipe"), std::string::npos);
    EXPECT_NE(output.find("Completed step: Chop vegetables"), std::string::npos);
    EXPECT_NE(output.find("Recipe completed: Test Recipe"), std::string::npos);
}

TEST_F(RecetteTest, ExecuterEnParallele) {
    auto etape1 = std::make_shared<EtapeRecette>("Chop vegetables", 1);
    auto etape2 = std::make_shared<EtapeRecette>("Boil water", 2);
    recette.ajouterEtape(etape1);
    recette.ajouterEtape(etape2);

    std::string output = captureOutput([&]() { recette.executerEnParallele(); });

    EXPECT_NE(output.find("Executing recipe in parallel: Test Recipe"), std::string::npos);
    EXPECT_NE(output.find("Recipe completed in parallel: Test Recipe"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}