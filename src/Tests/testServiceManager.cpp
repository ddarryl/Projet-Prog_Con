#include "../Model/serviceManager.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Test de la classe ServiceManager
class ServiceManagerTest : public ::testing::Test {
protected:
    ServiceManager serviceManager;

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

TEST_F(ServiceManagerTest, AjouterArticle) {
    serviceManager.ajouterArticle("Poisson", 10);
    EXPECT_EQ(serviceManager.getStock("Poisson"), 10); // Vérifie que l'article a été ajouté correctement
}

TEST_F(ServiceManagerTest, ConsommerArticle) {
    serviceManager.consommer("Viande", 5);
    EXPECT_EQ(serviceManager.getStock("Viande"), 5); // Vérifie que le stock est réduit correctement
}

TEST_F(ServiceManagerTest, ConsommerArticleInexistant) {
    std::string output = captureOutput([&]() { serviceManager.consommer("Inexistant", 5); });
    EXPECT_EQ(output, "ERREUR : L'article Inexistant n'existe pas.\n");
}

TEST_F(ServiceManagerTest, ReapprovisionnerArticle) {
    serviceManager.reapprovisionner("Légumes", 10);
    EXPECT_EQ(serviceManager.getStock("Légumes"), 30); // Vérifie que le stock est augmenté correctement
}

TEST_F(ServiceManagerTest, ReapprovisionnerArticleInexistant) {
    std::string output = captureOutput([&]() { serviceManager.reapprovisionner("Inexistant", 5); });
    EXPECT_EQ(output, "ERREUR : L'article Inexistant n'existe pas.\n");
}

TEST_F(ServiceManagerTest, AlerteStock) {
    serviceManager.consommer("Viande", 5); // Réduit le stock à 5
    EXPECT_TRUE(serviceManager.alerteStock("Viande")); // Vérifie que l'alerte est activée
}

TEST_F(ServiceManagerTest, AfficherStock) {
    std::string output = captureOutput([&]() { serviceManager.afficherStock(); });
    EXPECT_NE(output.find("État actuel du stock :"), std::string::npos); // Vérifie que l'en-tête est présent
    EXPECT_NE(output.find("Viande: 5"), std::string::npos); // Vérifie que le stock de viande est affiché
}

TEST_F(ServiceManagerTest, ChargerDepuisBDD) {
    // Vous pouvez créer un fichier temporaire pour tester le chargement depuis la base de données
    std::ofstream outfile("test_stock.txt");
    outfile << "Poisson 20\n";
    outfile.close();

    serviceManager.chargerDepuisBDD("test_stock.txt");
    EXPECT_EQ(serviceManager.getStock("Poisson"), 20); // Vérifie que le stock a été chargé correctement

    // Nettoyer le fichier après le test
    std::remove("test_stock.txt");
}

TEST_F(ServiceManagerTest, SauvegarderDansBDD) {
    serviceManager.sauvegarderDansBDD("test_stock_save.txt");
    std::ifstream infile("test_stock_save.txt");
    std::string line;
    bool found = false;

    while (std::getline(infile, line)) {
        if (line == "Viande 5") {
            found = true;
            break;
        }
    }
    infile.close();
    EXPECT_TRUE(found); // Vérifie que le stock de viande a été sauvegardé

    // Nettoyer le fichier après le test
    std::remove("test_stock_save.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}