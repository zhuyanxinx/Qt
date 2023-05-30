#ifndef QTSLIDER_H
#define QTSLIDER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtSlider; }
QT_END_NAMESPACE

class QtSlider : public QMainWindow
{
    Q_OBJECT

public:
    QtSlider(QWidget *parent = nullptr);
    ~QtSlider();
private slots:
    void valueChanged(int value);
    void on_chkTxtVisible_clicked(bool checked);

    void on_chkInvAppear_clicked(bool checked);

    void on_radioPercent_clicked();

    void on_radioCurrent_clicked();

private:
    Ui::QtSlider *ui;
};
#endif // QTSLIDER_H
