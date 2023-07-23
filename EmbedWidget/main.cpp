#include "embedwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmbedWidget w;
    w.show();
    return a.exec();
}
