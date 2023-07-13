#include "qtevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEvent w;
    w.show();
    return a.exec();
}
