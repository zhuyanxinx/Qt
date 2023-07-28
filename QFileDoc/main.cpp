#include "qfiledoc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFileDoc w;
    w.show();
    return a.exec();
}
