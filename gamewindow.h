#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;         // Defines scene
    QGraphicsScene *racquetArea;   // Horizontal area
    QGraphicsRectItem* bricks[44]; // Defines bricks
    QGraphicsRectItem* racquet;    // Defines racquet
    QGraphicsEllipseItem* ball;    // Defines ball

};

#endif // GAMEWINDOW_H
