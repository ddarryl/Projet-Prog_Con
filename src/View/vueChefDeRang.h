#ifndef VUECHEFDERANG_H
#define VUECHEFDERANG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

class VueChefDeRang : public QWidget
{
    Q_OBJECT

public:
    VueChefDeRang(QWidget *parent = nullptr);
    ~VueChefDeRang();

    void afficherCommandes(const std::vector<std::string>& commandes);

private:
    QVBoxLayout *layout;
    QLabel *labelTitre;
    QListWidget *listWidgetCommandes;
};

#endif // VUECHEFDERANG_H