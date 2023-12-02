#include "qtcustevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCustEvent w;
    w.show();
    return a.exec();
}
