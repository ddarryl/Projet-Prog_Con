#include "View/mainwindow.h"
#include "../src/Controller/Controller.h"
#include "../src/View/Affichage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controleur controleur;
    Affichage affichage;

    // Création de clients
    Client client1("Jean", "Pierre");
    Client client2("Marie", "Claire");

    // Création de plats
    Plat plat1("Poulet", {Ingredient("Poulet"), Ingredient("Riz")});
    Plat plat2("Poisson", {Ingredient("Poisson"), Ingredient("Légumes")});

    // Création de commandes
    Commande commande1(client1);
    commande1.ajouterPlat(plat1);
    commande1.ajouterPlat(plat2);

    Commande commande2(client2);
    commande2.ajouterPlat(plat1);

    // Ajout des commandes et des plats au contrôleur
    controleur.ajouterCommande(commande1);
    controleur.ajouterCommande(commande2);
    controleur.ajouterPlat(plat1);
    controleur.ajouterPlat(plat2);

    // Affichage des commandes et des plats
    affichage.afficherCommandes(controleur.getCommandes());
    affichage.afficherPlats(controleur.getPlats());

    MainWindow w;
    w.show();
    return a.exec();
}
