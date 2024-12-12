#ifndef CONTROLEURMAITREHOTEL_H
#define CONTROLEURMAITREHOTEL_H

#include <QObject>
#include <string>
#include "../View/vueMaitreHotel.h"
#include "../Model/maitreHotel.h"

class ControleurMaitreHotel : public QObject {
    Q_OBJECT

public:
    ControleurMaitreHotel(VueMaitreHotel *vue, MaitreHotel *maitreHotel);
    ~ControleurMaitreHotel();

    void demarrerSimulation();
    void mettreEnPause();
    void accelerer();
    void reinitialiser();

    void ajouterClient(const std::string& client);
    void attribuerTable();

private:
    VueMaitreHotel *vue;
    MaitreHotel *maitreHotel;
};

#endif // CONTROLEURMAITREHOTEL_H