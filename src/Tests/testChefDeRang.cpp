#include "../Model/chefDeRang.h"
#include <gtest/gtest.h>
#include <sstream>

// Test de la classe ChefDeRang
class ChefDeRangTest : public ::testing::Test {
protected:
    ChefDeRang chef;

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

TEST_F(ChefDeRangTest, PrendreCommande) {
    chef.prendreCommande("Client 1", "Entrée");
    EXPECT_EQ(chef.getCommandes().size(), 1);
    EXPECT_EQ(chef.getCommandes().front(), "Commande de Client 1 : Entrée");
}

TEST_F(ChefDeRangTest, PrendreCommandeVide) {
    // Tester la prise de commande avec des paramètres vides
    testing::internal::CaptureStdout(); // Capturer la sortie standard
    chef.prendreCommande("", "Entrée");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Erreur : le client et le plat doivent être non vides.\n");
}

TEST_F(ChefDeRangTest, AfficherCommandes) {
    chef.prendreCommande("Client 1", "Entrée");
    chef.prendreCommande("Client 2", "Plat Principal");

    // Capturer la sortie de l'affichage des commandes
    std::string output = captureOutput([&]() { chef.afficherCommandes(); });

    EXPECT_NE(output.find("Commandes en cours"), std::string::npos);
    EXPECT_NE(output.find("Commande de Client 1 : Entrée"), std::string::npos);
    EXPECT_NE(output.find("Commande de Client 2 : Plat Principal"), std::string::npos);
}

TEST_F(ChefDeRangTest, AfficherCommandesAucune) {
    // Tester l'affichage des commandes lorsqu'il n'y en a aucune
    std::string output = captureOutput([&]() { chef.afficherCommandes(); });
    EXPECT_EQ(output, "Aucune commande en cours.\n");
}

TEST_F(ChefDeRangTest, EnvoyerCommande) {
    // Simuler l'envoi d'une commande
    int msgQueueId = 1; // ID fictif pour le test
    std::string commande = "Commande de Client 1 : Entrée";

    // Capturer la sortie de l'envoi de commande
    std::string output = captureOutput([&]() { chef.envoyerCommande(commande, msgQueueId); });

    EXPECT_NE(output.find("Chef de Rang: Order sent - " + commande), std::string::npos);
}

TEST_F(ChefDeRangTest, EnvoyerCommandeErreur) {
    // Simuler une erreur lors de l'envoi de commande
    int msgQueueId = -1; // ID de file de messages invalide
    std::string commande = "Commande de Client 1 : Entrée";

    // Capturer la sortie de l'envoi de commande
    std::string output = captureOutput([&]() { chef.envoyerCommande(commande, msgQueueId); });

    EXPECT_NE(output.find("Erreur lors de l'envoi de la commande : " + commande), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}