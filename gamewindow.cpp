#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QTextDocument>

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

    lives = 3;

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
    counter = new QGraphicsTextItem;
    counter->setPos(117,150);
    counter->setScale(5);
    counter->setPlainText("0");
    scene->addItem(counter);

    timer = new QTimer(this);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(scene,SIGNAL(newCursorX(int)),this,SLOT(setRacquetX(int)));
    connect(scene,SIGNAL(startMove()),this,SLOT(startMove()));
    connect(this,SIGNAL(updateLabel(QString)),ui->label,SLOT(setText(QString)));
    connect(ball,SIGNAL(liveLost()),this,SLOT(liveLost()));
    connect(this,SIGNAL(updateStart()),scene,SLOT(updateStart()));
    connect(ball,SIGNAL(victory()),this,SLOT(vicrory()));
    connect(ball,SIGNAL(updateCounter(uint)),this,SLOT(updateCounter(uint)));
}

void GameWindow::setRacquetX(int x)
{
    if (scene->started()) {
        if (x < -161) racquet->setX(-161);
        else if (x > 151) racquet->setX(151);
        else racquet->setX(x);
    }
}

void GameWindow::startMove()
{
    int x = qrand() % 16 - 8;
    if (x == 0) x = 5;
    ball->setVelocityX(x);
    timer->start(100);
    emit updateLabel("Lives: " + QString::number(lives));
}

void GameWindow::liveLost()
{
    lives--;
    if (lives == 0) {
        emit updateLabel("You lost");
        this->close();
    }
    else {
        timer->stop();
        ball->setPos(150,250);
        ball->setVelocityY(15);
        emit updateStart();
        emit updateLabel("Tap to start");
    }
}

void GameWindow::vicrory()
{
    timer->stop();
    emit updateLabel("You won this game! Congratulations from Andrii!)");
}

void GameWindow::updateCounter(unsigned int rBricks)
{
    if (rBricks == 10) {
        counter->setPos(counter->scenePos().x()-22,counter->scenePos().y());
    }
    counter->setPlainText(QString::number(rBricks));
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

void GameGraphicsScene::updateStart()
{
    start = !start;
}

GameBall::GameBall()
    : QGraphicsItem()
{
    velocityY = 15;
    removedBricks = 0;
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
        QList<QGraphicsItem*> collideList = scene()->collidingItems(this);
        foreach(QGraphicsItem *i, collideList) {
            QGraphicsRectItem *item = dynamic_cast<QGraphicsRectItem*>(i);
            if (item != 0) {
                velocityY = -velocityY;
                if (!(this->scenePos().y() > 335)) { // ball did not collide with racquet
                    scene()->removeItem(item);
                    removedBricks++;
                    emit updateCounter(removedBricks);
                    if (removedBricks == 44) {
                        emit victory();
                    }
                }
                else {
                    this->setPos(this->scenePos().x(),this->scenePos().y()-3);
                }
            }
        }
    }
    else {
        if (this->scenePos().y() < 0) {
            velocityY = -velocityY;
        }
        else if (this->scenePos().y() > 370) {
            velocityY = -velocityY;
            emit liveLost();
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

void GameBall::setVelocityY(int velY)
{
    velocityY = velY;
}

void GameBall::advance(int phase)
{
    if (!phase) return;

    setPos(mapToParent(velocityX,velocityY));
}
