#include "vueCuisinier.h"

VueCuisinier::VueCuisinier(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;

    labelTitre = new QLabel("Plats en préparation");
    listWidgetPlats = new QListWidget(this);

    layout->addWidget(labelTitre);
    layout->addWidget(listWidgetPlats);
    setLayout(layout);
}

VueCuisinier::~VueCuisinier()
{
    // Pas besoin de delete ici, Qt gère la mémoire des widgets enfants
}

void VueCuisinier::afficherPlatsEnPreparation(const std::vector<std::string>& plats)
{
    listWidgetPlats->clear();
    if (plats.empty()) {
        listWidgetPlats->addItem("Aucun plat en préparation.");
    } else {
        for (const auto& plat : plats) {
            listWidgetPlats->addItem(QString::fromStdString(plat));
        }
    }
}

void VueCuisinier::afficherPlatPrepare(const std::string& plat)
{
    listWidgetPlats->addItem("Plat préparé : " + QString::fromStdString(plat));
}