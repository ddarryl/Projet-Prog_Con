#include "controlleurMaitreHotel.h"
#include <QTimer>

ControleurMaitreHotel::ControleurMaitreHotel(VueMaitreHotel *vue, MaitreHotel *maitreHotel)
    : vue(vue), maitreHotel(maitreHotel) {

    // Simulation de l'ajout de clients et attribution de tables
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ControleurMaitreHotel::attribuerTable);
    timer->start(3000); // Simulation toutes les 3 secondes
}

ControleurMaitreHotel::~ControleurMaitreHotel() {
    delete vue;        // Assurez-vous que cela est correct selon votre logique
    delete maitreHotel; // Assurez-vous que cela est correct selon votre logique
}

void ControleurMaitreHotel::ajouterClient(const std::string& client) {
    maitreHotel->ajouterClient(client);
    vue->afficherFileClients(maitreHotel->getNombreClients());
}

void ControleurMaitreHotel::attribuerTable() {
    std::string clientAttribue = maitreHotel->attribuerTable();
    if (!clientAttribue.empty()) {
        vue->afficherClientAttribue(clientAttribue);
    }
}
