#include "qtfilesystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtFileSystem w;
    w.show();
    return a.exec();
}
