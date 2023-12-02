#include "qttablev.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTableV w;
    w.show();
    return a.exec();
}
