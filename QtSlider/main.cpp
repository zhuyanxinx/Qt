#include "qtslider.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSlider w;
    w.show();
    return a.exec();
}
