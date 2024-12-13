#include "../Model/stockGestion.h"
#include <gtest/gtest.h>

class StockGestionTest : public ::testing::Test {
protected:
    StockGestion stock;

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

TEST_F(StockGestionTest, Consommer) {
    stock.consommer("Viande", 5);
    EXPECT_EQ(stock.getStock("Viande"), 5); // Vérifie que le stock est réduit correctement
}

TEST_F(StockGestionTest, Reapprovisionner) {
    stock.reapprovisionner("Viande", 10);
    EXPECT_EQ(stock.getStock("Viande"), 20); // Vérifie que le stock est augmenté correctement
}

TEST_F(StockGestionTest, AlerteStock) {
    // Consommer jusqu'à atteindre le seuil critique
    stock.consommer("Viande", 5);
    EXPECT_TRUE(stock.alerteStock("Viande")); // Vérifie que l'alerte est activée
}

TEST_F(StockGestionTest, AjouterArticle) {
    stock.ajouterArticle("Poisson", 10);
    EXPECT_EQ(stock.getStock("Poisson"), 10); // Vérifie que l'article a été ajouté correctement
}

TEST_F(StockGestionTest, ConsommerArticleInexistant) {
    std::string output = captureOutput([&]() { stock.consommer("Inexistant", 5); });
    EXPECT_EQ(output, "ERREUR : L'article Inexistant n'existe pas.\n");
}

TEST_F(StockGestionTest, ReapprovisionnerArticleInexistant) {
    std::string output = captureOutput([&]() { stock.reapprovisionner("Inexistant", 5); });
    EXPECT_EQ(output, "ERREUR : L'article Inexistant n'existe pas.\n");
}

TEST_F(StockGestionTest, AlerteStockArticleInexistant) {
    EXPECT_FALSE(stock.alerteStock("Inexistant")); // Vérifie que l'alerte ne s'active pas pour un article inexistant
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}