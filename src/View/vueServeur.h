#ifndef VUESERVEUR_H
#define VUESERVEUR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <vector>
#include <string>

class VueServeur : public QWidget {
    Q_OBJECT

public:
    explicit VueServeur(QWidget *parent = nullptr);
    ~VueServeur();

    void afficherPlats(const std::vector<std::string>& plats);
    void afficherService(const std::string& plat);

private:
    QVBoxLayout *layout; // Déclarez le layout ici
    QLabel *labelTitre;
    QListWidget *listWidgetPlats;
};

#endif // VUESERVEUR_H