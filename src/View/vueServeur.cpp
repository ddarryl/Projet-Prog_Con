#include "vueServeur.h"

VueServeur::VueServeur(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;

    labelTitre = new QLabel("Plats à Servir");
    listWidgetPlats = new QListWidget(this);

    layout->addWidget(labelTitre);
    layout->addWidget(listWidgetPlats);
    setLayout(layout);
}

VueServeur::~VueServeur()
{
    // Pas besoin de delete ici, Qt gère la mémoire des widgets enfants
}

void VueServeur::afficherPlats(const std::vector<std::string>& plats)
{
    listWidgetPlats->clear();
    if (plats.empty()) {
        listWidgetPlats->addItem("Aucun plat à servir.");
    } else {
        for (const auto& plat : plats) {
            listWidgetPlats->addItem(QString::fromStdString(plat));
        }
    }
}

void VueServeur::afficherService(const std::string& plat)
{
    listWidgetPlats->addItem("Plat servi : " + QString::fromStdString(plat));
}