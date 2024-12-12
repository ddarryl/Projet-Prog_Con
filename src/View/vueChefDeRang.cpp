#include "vueChefDeRang.h"
#include <QMessageBox>

VueChefDeRang::VueChefDeRang(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;
    labelTitre = new QLabel("Commandes en cours", this);
    listWidgetCommandes = new QListWidget(this);

    layout->addWidget(labelTitre);
    layout->addWidget(listWidgetCommandes);

    setLayout(layout);
}

VueChefDeRang::~VueChefDeRang()
{
    // Pas besoin de delete ici, Qt gère la mémoire des widgets enfants
}

void VueChefDeRang::afficherCommandes(const std::vector<std::string>& commandes)
{
    if (commandes.empty()) {
        QMessageBox::warning(this, "Erreur", "La liste des commandes est vide.");
        return;
    }

    listWidgetCommandes->clear();
    for (const auto& commande : commandes) {
        listWidgetCommandes->addItem(QString::fromStdString(commande));
    }
}