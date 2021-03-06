#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QPainter>
#include <QTimer>
#include <QPointF>
#include <QTime>
#include <QString>

namespace Ui {
class GameWindow;
class GameGraphicsScene;
class GameBall;
}

class GameBall : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    GameBall();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setVelocityX(int velX);
    void setVelocityY(int velY);

protected:
    void advance(int phase);

signals:
    void liveLost();
    void victory();
    void updateCounter(unsigned int rBricks);

private:
    int velocityY;
    int velocityX;
    unsigned int removedBricks;
};

class GameGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    bool start;
    bool lastTape;

public:
    explicit GameGraphicsScene(QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool started() const;
    void setLastTape(bool flag);

public slots:
    void updateStart();

signals:
    void newCursorX(int x);
    void startMove();
    void gameOver();
};

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

public slots:
    void setRacquetX(int x);
    void startMove();
    void liveLost();
    void vicrory();
    void updateCounter(unsigned int rBricks);
    void gameOver();

signals:
    void updateLabel(QString str);
    void timerStop();
    void updateStart();

private:
    Ui::GameWindow *ui;
    GameGraphicsScene *scene;      // Defines scene
    QGraphicsRectItem *bricks[44]; // Defines bricks
    QGraphicsRectItem *racquet;    // Defines racquet
    QGraphicsTextItem *counter;    // Defines counter
    GameBall *ball;                // Defines ball
    QTimer *timer;
    unsigned int lives;            // Defines lives
};

#endif // GAMEWINDOW_H
