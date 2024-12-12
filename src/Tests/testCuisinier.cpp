#include "../Model/cuisinier.h"
#include <gtest/gtest.h>

TEST(CuisinierTest, AjouterCommande) {
    Cuisinier cuisinier;
    cuisinier.ajouterCommande("Plat principal");
    EXPECT_EQ(cuisinier.getPlatsEnPreparation().size(), 1);
}

TEST(CuisinierTest, PreparerPlat) {
    Cuisinier cuisinier;
    cuisinier.ajouterCommande("Plat principal");
    cuisinier.preparerPlat();
    EXPECT_EQ(cuisinier.getPlatsEnPreparation().size(), 0);
}