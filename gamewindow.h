#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

namespace Ui {
class GameWindow;
class GameGraphicsScene;
}

class GameGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    bool start;

public:
    explicit GameGraphicsScene(QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool started();

signals:
    void newCursorX(int x);
};


class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

public slots:
    void setRacquetX(int x);

private:
    Ui::GameWindow *ui;
    GameGraphicsScene *scene;      // Defines scene
    QGraphicsRectItem *bricks[44]; // Defines bricks
    QGraphicsRectItem *racquet;    // Defines racquet
    QGraphicsEllipseItem *ball;    // Defines ball
};

#endif // GAMEWINDOW_H
