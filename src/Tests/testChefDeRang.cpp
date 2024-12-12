#include "../Model/chefDeRang.h"
#include <gtest/gtest.h>

TEST(ChefDeRangTest, PrendreCommande) {
    ChefDeRang chef;
    chef.prendreCommande("Client 1", "Entrée");
    EXPECT_EQ(chef.getCommandes().size(), 1);
    EXPECT_EQ(chef.getCommandes().front(), "Commande de Client 1 : Entrée");
}
