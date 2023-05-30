#ifndef QTBTN_H
#define QTBTN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtBtn; }
QT_END_NAMESPACE

class QtBtn : public QMainWindow
{
    Q_OBJECT

public:
    QtBtn(QWidget *parent = nullptr);
    ~QtBtn();

private slots:
    void on_btnLeft_clicked();

    void on_btnCenter_clicked();

    void on_btnRight_clicked();

    void on_btnBlod_clicked(bool checked);

    void on_btnItalic_clicked(bool checked);

    void on_btnUnderline_clicked(bool checked);

    void on_btnReadOnly_clicked(bool checked);

    void on_btnClearEnable_clicked(bool checked);

    void on_btnEnable_clicked(bool checked);

    void on_radioBlack_clicked();

    void on_radioRed_clicked();

    void on_radioBlue_clicked();

private:
    Ui::QtBtn *ui;
};
#endif // QTBTN_H
