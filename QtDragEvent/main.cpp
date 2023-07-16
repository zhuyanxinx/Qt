#include "qtdragevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDragEvent w;
    w.show();
    return a.exec();
}
