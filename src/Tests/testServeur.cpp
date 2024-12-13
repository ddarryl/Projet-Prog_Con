#include "../Model/serveur.h"
#include <gtest/gtest.h>

// Test de la classe Serveur
class ServeurTest : public ::testing::Test {
protected:
    Serveur serveur;

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

TEST_F(ServeurTest, RecevoirPlat) {
    serveur.recevoirPlat("Plat principal");
    EXPECT_EQ(serveur.getPlatsEnAttente().size(), 1);
    EXPECT_EQ(serveur.getPlatsEnAttente().front(), "Plat principal");
}

TEST_F(ServeurTest, ServirPlat) {
    serveur.recevoirPlat("Plat principal");
    serveur.servirPlat();
    EXPECT_EQ(serveur.getPlatsEnAttente().size(), 0);
    EXPECT_EQ(serveur.getPlatsServis().size(), 1);
    EXPECT_EQ(serveur.getPlatsServis().front(), "Plat principal");
}

TEST_F(ServeurTest, ServirPlatSansPlat) {
    // Capturer la sortie de la tentative de servir un plat sans plat en attente
    std::string output = captureOutput([&]() { serveur.servirPlat(); });
    EXPECT_EQ(output, "Serveur : Aucun plat en attente à servir.\n");
}

TEST_F(ServeurTest, DeposerVaisselleSale) {
    ComptoirSocket comptoir; // Simuler le comptoir
    serveur.deposerVaisselleSale("Assiette", comptoir);
    // Vous pouvez ajouter des assertions pour vérifier l'état du comptoir si nécessaire
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}