#include "GameDownloader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameDownloader w;
    w.show();
    return a.exec();
}
