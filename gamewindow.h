#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <rectangle.h>
#include <QWidget>
#include <QGraphicsScene>

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
    QGraphicsScene *scene; // Defines scene
    Rectangle      *rect;  // Defines rectangle
};

#endif // GAMEWINDOW_H
