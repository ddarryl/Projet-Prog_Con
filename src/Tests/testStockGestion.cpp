#include "../Model/stockGestion.h"
#include <gtest/gtest.h>

TEST(StockGestionTest, Consommer) {
    StockGestion stock;
    stock.consommer("Viande", 5);
    EXPECT_EQ(stock.getStock("Viande"), 5);
}

TEST(StockGestionTest, Reapprovisionner) {
    StockGestion stock;
    stock.reapprovisionner("Viande", 10);
    EXPECT_EQ(stock.getStock("Viande"), 20);
}

TEST(StockGestionTest, AlerteStock) {
    StockGestion stock;
    EXPECT_TRUE(stock.alerteStock("Viande"));
}
