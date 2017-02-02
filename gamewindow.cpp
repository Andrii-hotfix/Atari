#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->resize(350,450);       // sets the size of the window
    this->setFixedSize(350,450); // makes the window fixed

    scene = new QGraphicsScene(); // inits graphics scene
    rect = new Rectangle();       // inits rectangle

    ui->graphicsView->setScene(scene);                       // sets graphics scene in graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // sets smoothing
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->addItem(rect); // adds rectangle on the scene
}

GameWindow::~GameWindow()
{
    delete ui;
}
