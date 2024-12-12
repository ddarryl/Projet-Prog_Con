#include "vuePlongeur.h"

VuePlongeur::VuePlongeur(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;

    labelTitre = new QLabel("Objets Sales", this);
    listWidgetObjets = new QListWidget(this);

    layout->addWidget(labelTitre);
    layout->addWidget(listWidgetObjets);
    setLayout(layout);
}

VuePlongeur::~VuePlongeur()
{
    // Pas besoin de delete ici, Qt gère la mémoire des widgets enfants
}

void VuePlongeur::afficherObjetsSales(const std::vector<std::string>& objets)
{
    listWidgetObjets->clear();
    if (objets.empty()) {
        listWidgetObjets->addItem("Aucun objet sale.");
    } else {
        for (const auto& objet : objets) {
            listWidgetObjets->addItem(QString::fromStdString(objet));
        }
    }
}

void VuePlongeur::afficherObjetNettoye(const std::string& objet)
{
    listWidgetObjets->addItem("Objet nettoyé : " + QString::fromStdString(objet));
}