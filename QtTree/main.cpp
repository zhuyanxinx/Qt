#include "qttree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtTree w;
    w.show();
    return a.exec();
}
