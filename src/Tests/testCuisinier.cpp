#include "../Model/cuisinier.h"
#include "../Model/ComptoirSocket.h" // Include the header for ComptoirSocket
#include <gtest/gtest.h>

TEST(CuisinierTest, AjouterCommande) {
    Cuisinier cuisinier;
    cuisinier.ajouterCommande("Plat principal");
    EXPECT_EQ(cuisinier.getPlatsEnPreparation().size(), 1);
}

TEST(CuisinierTest, PreparerPlat) {
    Cuisinier cuisinier;
    ComptoirSocket comptoir(8080); // Create an instance of ComptoirSocket
    cuisinier.ajouterCommande("Plat principal");
    cuisinier.preparerPlat(comptoir); // Pass the comptoir parameter
    EXPECT_EQ(cuisinier.getPlatsEnPreparation().size(), 0);
}