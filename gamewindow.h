#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QPainter>
#include <QTimer>
#include <QPointF>
#include <QTime>

namespace Ui {
class GameWindow;
class GameGraphicsScene;
class GameBall;
}

class GameBall : public QGraphicsItem
{
public:
    GameBall();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setVelocityX(int velX);

protected:
    void advance(int phase);

private:
    int velocityY;
    int velocityX;
};

class GameGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    bool start;

public:
    explicit GameGraphicsScene(QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool started() const;

signals:
    void newCursorX(int x);
    void startMove();
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

private:
    Ui::GameWindow *ui;
    GameGraphicsScene *scene;      // Defines scene
    QGraphicsRectItem *bricks[44]; // Defines bricks
    QGraphicsRectItem *racquet;    // Defines racquet
    GameBall *ball;                // Defines ball
    QTimer *timer;
};

#endif // GAMEWINDOW_H
