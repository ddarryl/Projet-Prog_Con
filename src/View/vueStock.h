#ifndef VUESTOCK_H
#define VUESTOCK_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <string>

class VueStock : public QWidget {
    Q_OBJECT

public:
    explicit VueStock(QWidget *parent = nullptr);
    ~VueStock() = default;

    void afficherStock(const std::string& item, int stock);
    void afficherAlerte(const std::string& item);

private:
    QVBoxLayout *layout; // Déclarez le layout ici
    QLabel *labelTitre;
    QListWidget *listWidgetStock;
};

#endif // VUESTOCK_H