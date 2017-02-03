#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QRectF>
#include <QDebug>
#include <time.h>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->resize(350,450);       // sets the size of the window
    this->setFixedSize(350,450); // makes the window fixed

    scene = new QGraphicsScene(); // inits graphics scene

    ui->graphicsView->setScene(scene);                       // sets graphics scene in graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // sets smoothing
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    scene->setSceneRect(0,0,350,450);                      // sets rectangle scene area
    brick = scene->addRect(10,10,20,10,blackPen,redBrush); // sets the brick on the scene

    qDebug() << brick->pos();

}

GameWindow::~GameWindow()
{
    delete ui;
}
