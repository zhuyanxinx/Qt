#include "qtbtn.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtBtn w;
    w.show();
    return a.exec();
}
