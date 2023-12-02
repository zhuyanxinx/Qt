#include "qteventfilter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEventFilter w;
    w.show();
    return a.exec();
}
