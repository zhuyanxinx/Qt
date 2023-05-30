#include "qtcombo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCombo w;
    w.show();
    return a.exec();
}
