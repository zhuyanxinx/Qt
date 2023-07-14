#ifndef XYZHTTP_H
#define XYZHTTP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class XyzHttp; }
QT_END_NAMESPACE

class XyzHttp : public QMainWindow
{
    Q_OBJECT

public:
    XyzHttp(QWidget *parent = nullptr);
    ~XyzHttp();

private:
    Ui::XyzHttp *ui;
};
#endif // XYZHTTP_H
