#include "qttimerr.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTimerr w;
    w.show();
    return a.exec();
}
