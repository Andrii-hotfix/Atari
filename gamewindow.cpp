#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->resize(370,480);       // sets the size of the window
    this->setFixedSize(370,480); // makes the window fixed

    scene = new GameGraphicsScene(); // inits graphics scene

    ui->graphicsView->setScene(scene);                       // sets graphics scene in graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // sets smoothing
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setMouseTracking(true);

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene->setSceneRect(0,0,300,400);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 11; j++) {
            QColor color;
            switch (i) {
            case 0:
                color = Qt::red;
                break;
            case 1:
                color = Qt::yellow;
                break;
            case 2:
                color = Qt::blue;
                break;
            case 3:
                color = Qt::green;
                break;
            }
            QBrush brush(color);
            bricks[i*11+j] = scene->addRect(-13+30*j,10+15*i,25,10,blackPen,brush); // TODO: bad x-padding
        }
    }

    QBrush blackBrush(Qt::black);
    racquet = scene->addRect(150,350,50,10,blackPen,blackBrush);
    ball = scene->addEllipse(170,340,10,10,blackPen,blackBrush);

    QObject::connect(scene,SIGNAL(newCursorX(int)),this,SLOT(setRacquetX(int)));
}

void GameWindow::setRacquetX(int x)
{
    racquet->setX(x);
}

GameWindow::~GameWindow()
{
    delete ui;
}

GameGraphicsScene::GameGraphicsScene(QObject *parent)
    : QGraphicsScene(parent) {}

void GameGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit newCursorX(event->scenePos().x()-175);
//    qDebug() << event->scenePos().x();
}
