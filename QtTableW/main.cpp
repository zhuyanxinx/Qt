#include "qttablew.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTableW w;
    w.show();
    return a.exec();
}
