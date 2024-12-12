#include "mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("Restaurant");
    setStyleSheet("background-image: url(../Images/Background.jpg); background-repeat: no-repeat; background-position: center;");

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QGridLayout *mainLayout = new QGridLayout(central);

    // Carré 1
    int row = 0;

    // 5 tables de 2
    for (int i = 0; i < 5; ++i) {
        QLabel *table2 = new QLabel(central);
        QPixmap pixmap2("../Images/table2.png");
        QPixmap scaledPixmap2 = pixmap2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table2->setPixmap(scaledPixmap2);
        table2->setFixedSize(100, 100);
        mainLayout->addWidget(table2, row, i); // Ajout des tables de 2
    }
    row++;

    // 5 tables de 4
    for (int i = 0; i < 5; ++i) {
        QLabel *table4 = new QLabel(central);
        QPixmap pixmap4("../Images/table4.png");
        QPixmap scaledPixmap4 = pixmap4.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table4->setPixmap(scaledPixmap4);
        table4->setFixedSize(100, 100);
        mainLayout->addWidget(table4, row, i); // Ajout des tables de 4
    }
    row++;

    // 2 tables de 6
    for (int i = 0; i < 2; ++i) {
        QLabel *table6 = new QLabel(central);
        QPixmap pixmap6("../Images/table6.png");
        QPixmap scaledPixmap6 = pixmap6.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table6->setPixmap(scaledPixmap6);
        table6->setFixedSize(100, 100);
        mainLayout->addWidget(table6, row, i); // Ajout des tables de 6
    }
    row++;

    // 1 table de 10
    QLabel *table10_1 = new QLabel(central);
    QPixmap pixmap10("../Images/table10.png");
    QPixmap scaledPixmap10 = pixmap10.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    table10_1->setPixmap(scaledPixmap10);
    table10_1->setFixedSize(100, 100);
    mainLayout->addWidget(table10_1, row, 2); // Ajout de la table de 10

    // Carré 2
    row = 0; // Réinitialiser la ligne pour le carré 2

    // 5 tables de 2
    for (int i = 0; i < 5; ++i) {
        QLabel *table2 = new QLabel(central);
        QPixmap pixmap2("../Images/table2.png");
        QPixmap scaledPixmap2 = pixmap2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table2->setPixmap(scaledPixmap2);
        table2->setFixedSize(100, 100);
        mainLayout->addWidget(table2, row, i + 6); // Ajout des tables de 2 dans la colonne 6 à 10
    }
    row++;

    // 5 tables de 4
    for (int i = 0; i < 5; ++i) {
        QLabel *table4 = new QLabel(central);
        QPixmap pixmap4("../Images/table4.png");
        QPixmap scaledPixmap4 = pixmap4.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table4->setPixmap(scaledPixmap4);
        table4->setFixedSize(100, 100);
        mainLayout->addWidget(table4, row, i + 6); // Ajout des tables de 4 dans la colonne 6 à 10
    }
    row++;

    // 3 tables de 6
    for (int i = 0; i < 3; ++i) {
        QLabel *table6 = new QLabel(central);
        QPixmap pixmap6("../Images/table6.png");
        QPixmap scaledPixmap6 = pixmap6.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table6->setPixmap(scaledPixmap6);
        table6->setFixedSize(100, 100);
        mainLayout->addWidget(table6, row, i + 6); // Ajout des tables de 6 dans la colonne 6 à 10
    }
    row++;

    // 5 tables de 8
    for (int i = 0; i < 5; ++i) {
        QLabel *table8 = new QLabel(central);
        QPixmap pixmap8("../Images/table8.png");
        QPixmap scaledPixmap8 = pixmap8.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        table8->setPixmap(scaledPixmap8);
        table8->setFixedSize(100, 100);
        mainLayout->addWidget(table8, row, i + 6); // Ajout des tables de 8 dans la colonne 6 à 10
    }
    row++;

    // 1 table de 10
    QLabel *table10_2 = new QLabel(central);
    QPixmap pixmap10_2("../Images/table10.png");
    QPixmap scaledPixmap10_2 = pixmap10_2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    table10_2->setPixmap(scaledPixmap10_2);
    table10_2->setFixedSize(100, 100);
    mainLayout->addWidget(table10_2, row, 8); // Ajout de la table de 10 dans la colonne 8

    // Ajustement de la mise en page
    mainLayout->setSpacing(20);
    mainLayout->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
}