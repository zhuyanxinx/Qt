#include "qtbinfile.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtBinFile w;
    w.show();
    return a.exec();
}
