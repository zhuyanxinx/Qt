#ifndef QTTIMERR_H
#define QTTIMERR_H

#include <QWidget>
class QTimer;
class QElapsedTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class QtTimerr;
}
QT_END_NAMESPACE

class QtTimerr : public QWidget {
    Q_OBJECT
private:
    QTimer* mTimer;
    QElapsedTimer* mCounter;

public:
    QtTimerr(QWidget* parent = nullptr);
    ~QtTimerr();
private slots:
    void timerTimeOut();
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnDymc_clicked();

private:
    Ui::QtTimerr* ui;
};
#endif // QTTIMERR_H
