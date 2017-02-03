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
        this->resize(370,480);       // sets the size of the window
        this->setFixedSize(370,480); // makes the window fixed

        scene = new QGraphicsScene(); // inits graphics scene

        ui->graphicsView->setScene(scene);                       // sets graphics scene in graphicsView
        ui->graphicsView->setRenderHint(QPainter::Antialiasing); // sets smoothing
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPen blackPen(Qt::black);
        blackPen.setWidth(1);
        scene->setSceneRect(0,0,350,450);

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
                bricks[i*11+j] = scene->addRect(10+25*j+5*j,10+10*i+5*i,25,10,blackPen,brush);
            }
        }

        QBrush blackBrush(Qt::black);
        racquet = scene->addRect(150,350,50,10,blackPen,blackBrush);
        ball = scene->addEllipse(170,340,10,10,blackPen,blackBrush);
    }

    GameWindow::~GameWindow()
    {
        delete ui;
    }
