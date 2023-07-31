#include "qtfilestream.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtFileStream w;
    w.show();
    return a.exec();
}
