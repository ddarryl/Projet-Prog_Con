#include "controlleurStock.h"

ControleurStock::ControleurStock(VueStock *vue, StockGestion *stockGestion)
    : vue(vue), stockGestion(stockGestion) {}

ControleurStock::~ControleurStock() {
    delete vue;          // Assurez-vous que cela est correct selon votre logique
    delete stockGestion; // Assurez-vous que cela est correct selon votre logique
}

void ControleurStock::consommerItem(const std::string& item, int quantite) {
    stockGestion->consommer(item, quantite);
    afficherStock();
}

void ControleurStock::reapprovisionnerItem(const std::string& item, int quantite) {
    stockGestion->reapprovisionner(item, quantite);
    afficherStock();
}

void ControleurStock::afficherStock() {
    vue->afficherStock("Viande", stockGestion->getStock("Viande"));
    vue->afficherStock("Légumes", stockGestion->getStock("Légumes"));
    vue->afficherStock("Pain", stockGestion->getStock("Pain"));
    vue->afficherStock("Desserts", stockGestion->getStock("Desserts"));

    if (stockGestion->alerteStock("Viande")) {
        vue->afficherAlerte("Viande");
    }
    if (stockGestion->alerteStock("Légumes")) {
        vue->afficherAlerte("Légumes");
    }
    if (stockGestion->alerteStock("Pain")) {
        vue->afficherAlerte("Pain");
    }
    if (stockGestion->alerteStock("Desserts")) {
        vue->afficherAlerte("Desserts");
    }
}