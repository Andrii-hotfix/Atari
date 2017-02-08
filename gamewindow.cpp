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
    racquet = scene->addRect(140,350,30,2,blackPen,blackBrush);
    ball = new GameBall();
    scene->addItem(ball);

    timer = new QTimer(this);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(scene,SIGNAL(newCursorX(int)),this,SLOT(setRacquetX(int)));
    connect(scene,SIGNAL(startMove()),this,SLOT(startMove()));
}

void GameWindow::setRacquetX(int x)
{
    if (scene->started()) {
        if (x < -151) racquet->setX(-151);
        else if (x > 141) racquet->setX(141);
        else racquet->setX(x);
    }
}

void GameWindow::startMove()
{
    int x = qrand() % 16 - 8;
    qDebug() << x;
    ball->setVelocityX(x);
    timer->start(100);
}

GameWindow::~GameWindow()
{
    delete ui;
}

GameGraphicsScene::GameGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    start = false;
}

void GameGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit newCursorX(event->scenePos().x()-155);
}

void GameGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!start) {
        start = true;
        emit startMove();
    }
}

bool GameGraphicsScene::started() const
{
    return start;
}

GameBall::GameBall()
    : QGraphicsItem()
{
    velocityY = 15;
    int x = 0;

    setPos(mapToParent(150,250));
}

QRectF GameBall::boundingRect() const
{
    return QRect(0,0,10,10);
}

void GameBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);

    if (!scene()->collidingItems(this).isEmpty()) {
        velocityY = -velocityY;
        QList<QGraphicsItem*> collideList = scene()->collidingItems(this);
        foreach(QGraphicsItem *i, collideList) {
            QGraphicsRectItem *item = dynamic_cast<QGraphicsRectItem*>(i);
            if (item != 0) {
                if (!(this->scenePos().y() > 335)) { // ball did not collide with racquet
                    scene()->removeItem(item);
                }
            }
        }
    }
    else {
        if (this->scenePos().y() < 0) {
            velocityY = -velocityY;
        }
        else if (this->scenePos().y() > 390) {
            velocityY = -velocityY;
            qDebug() << "-1";
        }
        else {
            if (this->scenePos().x() < -22) {
                velocityX = -velocityX;
                this->setPos(-13, this->scenePos().y());
            }
            else if (this->scenePos().x() > 315) {
                this->setPos(303, this->scenePos().y());
                velocityX = -velocityX;
            }
        }
    }

    painter->setBrush(brush);
    painter->drawEllipse(rec);
}

void GameBall::setVelocityX(int velX)
{
    velocityX = velX;
}

void GameBall::advance(int phase)
{
    if (!phase) return;

    setPos(mapToParent(velocityX,velocityY));
}
