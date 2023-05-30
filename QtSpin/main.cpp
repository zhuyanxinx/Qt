#include "qtspin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSpin w;
    w.show();
    return a.exec();
}
