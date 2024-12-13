#include "../Model/maitreHotel.h"
#include <gtest/gtest.h>

class MaitreHotelTest : public ::testing::Test {
protected:
    MaitreHotel maitre;

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

TEST_F(MaitreHotelTest, AjouterClient) {
    maitre.ajouterClient("Client 1");
    EXPECT_EQ(maitre.getNombreClients(), 1);
}

TEST_F(MaitreHotelTest, AttribuerTable) {
    maitre.ajouterClient("Client 1");
    std::string result = maitre.attribuerTable();
    EXPECT_NE(result.find("Client 1"), std::string::npos);
    EXPECT_EQ(maitre.getNombreClients(), 0);
}

TEST_F(MaitreHotelTest, AttribuerTableSansClient) {
    std::string result = maitre.attribuerTable();
    EXPECT_EQ(result, ""); // Aucun client à attribuer
}

TEST_F(MaitreHotelTest, AfficherFile) {
    maitre.ajouterClient("Client 1");
    maitre.ajouterClient("Client 2");

    // Capturer la sortie de l'affichage de la file
    std::string output = captureOutput([&]() { maitre.afficherFile(); });

    EXPECT_NE(output.find("Client 1"), std::string::npos);
    EXPECT_NE(output.find("Client 2"), std::string::npos);
}

TEST_F(MaitreHotelTest, DepartClient) {
    RessourceGestion gestion; // Simuler la gestion des ressources
    maitre.ajouterClient("Client 1");
    maitre.attribuerTable(); // Attribuer une table au client

    // Simuler le départ du client
    maitre.departClient(1, gestion); // Supposons que la table 1 est occupée

    // Vérifier que la table est maintenant disponible
    EXPECT_TRUE(gestion.estTableDisponible(1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}