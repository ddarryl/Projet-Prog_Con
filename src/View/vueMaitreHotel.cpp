#include "vueMaitreHotel.h"

VueMaitreHotel::VueMaitreHotel(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;
    labelFileClients = new QLabel("File d'attente : 0 clients");
    labelClientAttribue = new QLabel("Client attribué : Aucun");
    listWidgetCommandes = new QListWidget(this);

    layout->addWidget(labelFileClients);
    layout->addWidget(labelClientAttribue);
    layout->addWidget(listWidgetCommandes);
    setLayout(layout);
}

VueMaitreHotel::~VueMaitreHotel()
{
    // Pas besoin de delete ici, Qt gère la mémoire des widgets enfants
}

void VueMaitreHotel::afficherFileClients(int nombre)
{
    labelFileClients->setText(QString("File d'attente : %1 clients").arg(nombre));
}

void VueMaitreHotel::afficherClientAttribue(const std::string& client)
{
    if (client.empty()) {
        labelClientAttribue->setText("Client attribué : Aucun");
    } else {
        labelClientAttribue->setText(QString("Client attribué : %1").arg(QString::fromStdString(client)));
    }
}