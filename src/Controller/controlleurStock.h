#ifndef CONTROLEURSTOCK_H
#define CONTROLEURSTOCK_H

#include "../View/vueStock.h"
#include "../Model/stockGestion.h"

class ControleurStock : public QObject {
    Q_OBJECT

public:
    ~ControleurStock();
    ControleurStock(VueStock *vue, StockGestion *stockGestion);
    void consommerItem(const std::string& item, int quantite);
    void reapprovisionnerItem(const std::string& item, int quantite);
    void afficherStock();

private:
    VueStock *vue;
    StockGestion *stockGestion;
};

#endif
