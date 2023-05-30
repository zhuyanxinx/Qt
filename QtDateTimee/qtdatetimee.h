#ifndef QTDATETIMEE_H
#define QTDATETIMEE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtDateTimee; }
QT_END_NAMESPACE

class QtDateTimee : public QMainWindow
{
    Q_OBJECT

public:
    QtDateTimee(QWidget *parent = nullptr);
    ~QtDateTimee();

private slots:
    void on_pushButton_clicked();

    void on_btnTime_clicked();

    void on_btnDate_clicked();

    void on_btnFormatTime_clicked();

    void on_btnFormatDate_clicked();

    void on_btnFormatDateTime_clicked();

    void on_calendar_selectionChanged();

private:
    Ui::QtDateTimee *ui;
};
#endif // QTDATETIMEE_H
