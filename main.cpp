#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();

    // this is specially for qt commit
}
