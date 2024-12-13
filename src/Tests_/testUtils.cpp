#include "../Model/utils.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <thread>

// Test de la classe utils
class UtilsTest : public ::testing::Test {
protected:
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

TEST_F(UtilsTest, CreateResource) {
    auto resource1 = createResource();
    auto resource2 = createResource();

    EXPECT_NE(resource1, resource2); // Vérifie que les ressources sont différentes
    EXPECT_EQ(resource1->getId(), 1); // Vérifie que l'ID de la première ressource est 1
    EXPECT_EQ(resource2->getId(), 2); // Vérifie que l'ID de la deuxième ressource est 2
}

TEST_F(UtilsTest, PrepareDish) {
    std::string output = captureOutput([&]() { prepareDish(createResource(), "Pasta"); });

    EXPECT_NE(output.find("Preparing dish: Pasta"), std::string::npos); // Vérifie que le message de préparation est affiché
    EXPECT_NE(output.find("Dish ready: Pasta"), std::string::npos); // Vérifie que le message de plat prêt est affiché
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}