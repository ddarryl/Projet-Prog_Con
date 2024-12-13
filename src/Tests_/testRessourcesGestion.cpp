#include "../Model/ressourceGestion.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Test de la classe RessourceGestion
class RessourceGestionTest : public ::testing::Test {
protected:
    RessourceGestion ressourceGestion;

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

TEST_F(RessourceGestionTest, AjouterStock) {
    ressourceGestion.ajouterStock("Assiettes", 10);
    EXPECT_EQ(ressourceGestion.obtenirStock("Assiettes"), 60); // Vérifie que le stock est augmenté correctement
}

TEST_F(RessourceGestionTest, ConsommerRessource) {
    bool result = ressourceGestion.consommerRessource("Verres", 20);
    EXPECT_TRUE(result); // Vérifie que la consommation a réussi
    EXPECT_EQ(ressourceGestion.obtenirStock("Verres"), 30); // Vérifie que le stock est réduit correctement
}

TEST_F(RessourceGestionTest, ConsommerRessourceInsuffisante) {
    std::string output = captureOutput([&]() { ressourceGestion.consommerRessource("Assiettes", 60); });
    EXPECT_EQ(output.find("Error: Not enough Assiettes in stock."), std::string::npos); // Vérifie que l'erreur est affichée
    EXPECT_EQ(ressourceGestion.obtenirStock("Assiettes"), 50); // Vérifie que le stock reste inchangé
}

TEST_F(RessourceGestionTest, ObtenirStock) {
    EXPECT_EQ(ressourceGestion.obtenirStock("Nappes"), 20); // Vérifie que le stock est correct
    EXPECT_EQ(ressourceGestion.obtenirStock("Inexistant"), 0); // Vérifie que le stock d'un article inexistant est 0
}

TEST_F(RessourceGestionTest, VerifierDisponibilite) {
    EXPECT_TRUE(ressourceGestion.verifierDisponibilite("Corbeilles à pain", 10)); // Vérifie que la ressource est disponible
    EXPECT_FALSE(ressourceGestion.verifierDisponibilite("Corbeilles à pain", 20)); // Vérifie que la ressource n'est pas disponible
}

TEST_F(RessourceGestionTest, ReserverTable) {
    EXPECT_TRUE(ressourceGestion.reserverTable(1)); // Vérifie que la table 1 peut être réservée
    EXPECT_FALSE(ressourceGestion.reserverTable(1)); // Vérifie que la table 1 ne peut pas être réservée à nouveau
}

TEST_F(RessourceGestionTest, LibererTable) {
    ressourceGestion.reserverTable(2); // Réserve la table 2
    EXPECT_TRUE(ressourceGestion.libererTable(2)); // Vérifie que la table 2 peut être libérée
    EXPECT_FALSE(ressourceGestion.libererTable(2)); // Vérifie que la table 2 ne peut pas être libérée à nouveau
}

TEST_F(RessourceGestionTest, EstTableDisponible) {
    EXPECT_TRUE(ressourceGestion.estTableDisponible(3)); // Vérifie que la table 3 est disponible
    ressourceGestion.reserverTable(3); // Réserve la table 3
    EXPECT_FALSE(ressourceGestion.estTableDisponible(3)); // Vérifie que la table 3 n'est plus disponible
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}