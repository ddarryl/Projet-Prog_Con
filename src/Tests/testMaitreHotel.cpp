#include "../Model/maitreHotel.h"
#include <gtest/gtest.h>

TEST(MaitreHotelTest, AjouterClient) {
    MaitreHotel maitre;
    maitre.ajouterClient("Client 1");
    EXPECT_EQ(maitre.getNombreClients(), 1);
}

TEST(MaitreHotelTest, AttribuerTable) {
    MaitreHotel maitre;
    maitre.ajouterClient("Client 1");
    std::string clientAttribue = maitre.attribuerTable();
    EXPECT_EQ(clientAttribue, "Client 1");
    EXPECT_EQ(maitre.getNombreClients(), 0);
}
