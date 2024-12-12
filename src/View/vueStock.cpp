#include "vueStock.h"

VueStock::VueStock(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;

    labelTitre = new QLabel("Gestion des Stocks");
    listWidgetStock = new QListWidget(this);

    layout->addWidget(labelTitre);
    layout->addWidget(listWidgetStock);
    setLayout(layout);
}

void VueStock::afficherStock(const std::string& item, int stock) {
    if (stock < 0) {
        // Gestion d'erreur : stock ne peut pas être négatif
        return; // Ou vous pouvez afficher un message d'erreur
    }
    listWidgetStock->addItem(QString::fromStdString(item) + " : " + QString::number(stock));
}

void VueStock::afficherAlerte(const std::string& item) {
    if (item.empty()) {
        // Gestion d'erreur : l'élément ne peut pas être vide
        return; // Ou vous pouvez afficher un message d'erreur
    }
    QListWidgetItem* alerteItem = new QListWidgetItem(QString::fromStdString(item) + " : Alerte stock faible !");
    alerteItem->setBackground(Qt::red);
    alerteItem->setForeground(Qt::white);
    listWidgetStock->addItem(alerteItem);
}