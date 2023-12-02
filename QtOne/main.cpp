
#include "edittext.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditText w;
    w.show();
    return a.exec();
}
