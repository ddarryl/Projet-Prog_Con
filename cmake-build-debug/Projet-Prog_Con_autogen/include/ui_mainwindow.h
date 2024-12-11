/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QListWidget *orderListWidget;
    QTableWidget *stockTableWidget;
    QWidget *controlBar;
    QPushButton *startSimulationButton;
    QPushButton *pauseButton;
    QPushButton *speedUpButton;
    QPushButton *resetButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 780, 400));
        tableWidget->setColumnCount(3);
        tableWidget->setRowCount(0);
        orderListWidget = new QListWidget(centralwidget);
        orderListWidget->setObjectName(QString::fromUtf8("orderListWidget"));
        orderListWidget->setGeometry(QRect(10, 420, 780, 150));
        stockTableWidget = new QTableWidget(centralwidget);
        if (stockTableWidget->columnCount() < 2)
            stockTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        stockTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        stockTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        stockTableWidget->setObjectName(QString::fromUtf8("stockTableWidget"));
        stockTableWidget->setGeometry(QRect(10, 580, 780, 150));
        stockTableWidget->setColumnCount(2);
        stockTableWidget->setRowCount(0);
        controlBar = new QWidget(centralwidget);
        controlBar->setObjectName(QString::fromUtf8("controlBar"));
        controlBar->setGeometry(QRect(10, 740, 780, 50));
        startSimulationButton = new QPushButton(controlBar);
        startSimulationButton->setObjectName(QString::fromUtf8("startSimulationButton"));
        startSimulationButton->setGeometry(QRect(10, 10, 100, 30));
        pauseButton = new QPushButton(controlBar);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(120, 10, 100, 30));
        speedUpButton = new QPushButton(controlBar);
        speedUpButton->setObjectName(QString::fromUtf8("speedUpButton"));
        speedUpButton->setGeometry(QRect(230, 10, 100, 30));
        resetButton = new QPushButton(controlBar);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(340, 10, 100, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Restaurant", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Table", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Capacity", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = stockTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Ingredient", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = stockTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Quantity", nullptr));
        startSimulationButton->setText(QCoreApplication::translate("MainWindow", "Start Simulation", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        speedUpButton->setText(QCoreApplication::translate("MainWindow", "Speed Up", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
