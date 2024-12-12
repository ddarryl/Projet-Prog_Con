#ifndef VUEPLONGEUR_H
#define VUEPLONGEUR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <vector>
#include <string>

class VuePlongeur : public QWidget {
    Q_OBJECT

public:
    explicit VuePlongeur(QWidget *parent = nullptr);
    ~VuePlongeur();

    void afficherObjetsSales(const std::vector<std::string>& objets);
    void afficherObjetNettoye(const std::string& objet);

private:
    QVBoxLayout *layout; // Déclarez le layout ici
    QLabel *labelTitre;
    QListWidget *listWidgetObjets;
};

#endif // VUEPLONGEUR_H