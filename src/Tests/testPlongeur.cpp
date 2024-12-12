#include "../Model/plongeur.h"
#include <gtest/gtest.h>

TEST(PlongeurTest, AjouterObjetSale) {
    Plongeur plongeur;
    plongeur.ajouterObjetSale("Assiette");
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 1);
}

TEST(PlongeurTest, NettoyerObjet) {
    Plongeur plongeur;
    plongeur.ajouterObjetSale("Assiette");
    plongeur.nettoyerObjet();
    EXPECT_EQ(plongeur.getObjetsNettoyes().size(), 0);
}
