#ifndef VUEMAITREHOTEL_H
#define VUEMAITREHOTEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>

class VueMaitreHotel : public QWidget {
    Q_OBJECT

public:
    explicit VueMaitreHotel(QWidget *parent = nullptr);
    ~VueMaitreHotel() override;

    public slots:
        void afficherFileClients(int nombre);
    void afficherClientAttribue(const std::string& client);

private:
    QVBoxLayout *layout; // Déclarez le layout ici
    QLabel *labelFileClients;
    QLabel *labelClientAttribue;
    QListWidget *listWidgetCommandes;
};

#endif