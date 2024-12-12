#include "View/mainwindow.h"
#include "../src/View/vueMaitreHotel.h"
#include "../src/Controller/controlleurMaitreHotel.h"
#include "../src/Model/maitreHotel.h"
#include "../src/View/vueChefDeRang.h"
#include "../src/Controller/controlleurChefDeRang.h"
#include "../src/Model/chefDeRang.h"
#include "../src/View/vueServeur.h"
#include "../src/Controller/controlleurServeur.h"
#include "../src/Model/serveur.h"
#include "../src/View/vueCuisinier.h"
#include "../src/Controller/controlleurCuisinier.h"
#include "../src/Model/cuisinier.h"
#include "../src/View/vuePlongeur.h"
#include "../src/Controller/controlleurPlongeur.h"
#include "../src/Model/plongeur.h"
#include "../src/View/vueStock.h"
#include "../src/Controller/controlleurStock.h"
#include "../src/Model/stockGestion.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MaitreHotel maitreHotel;
    VueMaitreHotel vueMaitreHotel;
    ControleurMaitreHotel controleurMaitreHotel(&vueMaitreHotel, &maitreHotel);

    controleurMaitreHotel.ajouterClient("Client 1");
    controleurMaitreHotel.ajouterClient("Client 2");
    controleurMaitreHotel.ajouterClient("Client 3");

    ChefDeRang chefDeRang;
    VueChefDeRang vueChefDeRang;
    ControleurChefDeRang controleurChefDeRang(&vueChefDeRang, &chefDeRang);

    controleurChefDeRang.prendreCommande("Client 1", "Entrée");
    controleurChefDeRang.prendreCommande("Client 2", "Plat Principal");
    controleurChefDeRang.prendreCommande("Client 3", "Dessert");

    Serveur serveur;
    VueServeur vueServeur;
    ControleurServeur controleurServeur(&vueServeur, &serveur);

    controleurServeur.recevoirPlat("Entrée");
    controleurServeur.recevoirPlat("Plat Principal");
    controleurServeur.recevoirPlat("Dessert");
    controleurServeur.servirPlat();

    Cuisinier cuisinier;
    VueCuisinier vueCuisinier;
    ControleurCuisinier controleurCuisinier(&vueCuisinier, &cuisinier);

    controleurCuisinier.ajouterCommande("Entrée");
    controleurCuisinier.ajouterCommande("Plat Principal");
    controleurCuisinier.ajouterCommande("Dessert");
    controleurCuisinier.preparerPlat();

    Plongeur plongeur;
    VuePlongeur vuePlongeur;
    ControleurPlongeur controleurPlongeur(&vuePlongeur, &plongeur);

    controleurPlongeur.ajouterObjetSale("Assiette");
    controleurPlongeur.ajouterObjetSale("Verre");
    controleurPlongeur.ajouterObjetSale("Casserole");
    controleurPlongeur.nettoyerObjet();

    StockGestion stockGestion;
    VueStock vueStock;
    ControleurStock controleurStock(&vueStock, &stockGestion);

    controleurStock.consommerItem("Viande", 5);
    controleurStock.reapprovisionnerItem("Pain", 10);
    controleurStock.consommerItem("Légumes", 15);


    MainWindow w;
    w.show();
    return a.exec();
}
