
#include "three.h"
#include <QPushButton>
#include <QTimer>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Three w;
//    w.show();
//    return a.exec();
    QObject *btn = new QPushButton("IsBtn");
    qDebug()<<btn->metaObject()->className();
    if(btn->inherits("QPushButton")){
        QPushButton *tim = qobject_cast<QPushButton*>(btn);
        qDebug() << tim->text();
    }

}
