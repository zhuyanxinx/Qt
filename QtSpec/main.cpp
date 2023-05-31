#include "qtspec.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSpec w;
    w.show();
    return a.exec();
}
