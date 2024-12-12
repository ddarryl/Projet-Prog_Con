#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setGeometry(10, 10, 600, 400);
    scene->setSceneRect(0, 0, 600, 400);

    ui->setupUi(this);

    for (int i = 0; i < 5; ++i) {
        QGraphicsRectItem *table = scene->addRect(i * 100, 50, 80, 80);
        table->setBrush(Qt::blue);
    }

    client = scene->addEllipse(10, 300, 20, 20, QPen(), QBrush(Qt::green));
    serveur = scene->addRect(10, 200, 20, 20, QPen(), QBrush(Qt::red));

    client->setPos(200, 300);

    simulationSpeed = 1000;
    simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    simulationTimer->start(simulationSpeed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSimulation() {
    client->setPos(client->x() + 10, client->y());
}

void MainWindow::on_startSimulationButton_clicked() {
    simulationTimer->start(simulationSpeed);
}

void MainWindow::on_pauseButton_clicked() {
    simulationTimer->stop();
}

void MainWindow::on_speedUpButton_clicked() {
    simulationSpeed /= 2;
    simulationTimer->setInterval(simulationSpeed);
}