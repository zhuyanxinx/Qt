#include "qtstddialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtStdDialog w;
    w.show();
    return a.exec();
}
