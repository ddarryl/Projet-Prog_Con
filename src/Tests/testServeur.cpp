#include "../Model/serveur.h"
#include <gtest/gtest.h>

TEST(ServeurTest, RecevoirPlat) {
    Serveur serveur;
    serveur.recevoirPlat("Plat principal");
    EXPECT_EQ(serveur.getPlatsServis().size(), 1);
}

TEST(ServeurTest, ServirPlat) {
    Serveur serveur;
    serveur.recevoirPlat("Plat principal");
    serveur.servirPlat();
    EXPECT_EQ(serveur.getPlatsServis().size(), 0);
}
