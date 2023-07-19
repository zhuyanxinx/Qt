#include "tdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TDialog w;
    w.show();
    return a.exec();
}
