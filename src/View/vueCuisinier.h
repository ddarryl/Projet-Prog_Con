#ifndef VUECUISINIER_H
#define VUECUISINIER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <vector>
#include <string>

class VueCuisinier : public QWidget {
    Q_OBJECT

public:
    explicit VueCuisinier(QWidget *parent = nullptr);
    ~VueCuisinier();
    void afficherPlatsEnPreparation(const std::vector<std::string>& plats);
    void afficherPlatPrepare(const std::string& plat);

private:
    QVBoxLayout *layout; // Déclarez le layout ici
    QLabel *labelTitre;
    QListWidget *listWidgetPlats;
};

#endif // VUECUISINIER_H