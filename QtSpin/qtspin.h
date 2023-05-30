#ifndef QTSPIN_H
#define QTSPIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtSpin; }
QT_END_NAMESPACE

class QtSpin : public QMainWindow
{
    Q_OBJECT

public:
    QtSpin(QWidget *parent = nullptr);
    ~QtSpin();

private slots:
    void on_btnCalc_clicked();

    void on_spinBin_valueChanged(int arg1);

    void on_spinDec_valueChanged(int arg1);

    void on_spinHex_valueChanged(int arg1);

private:
    Ui::QtSpin *ui;
};
#endif // QTSPIN_H
