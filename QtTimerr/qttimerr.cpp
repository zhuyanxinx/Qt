#include "qttimerr.h"
#include "./ui_qttimerr.h"
#include <QElapsedTimer>
#include <QTime>
#include <QTimer>

QtTimerr::QtTimerr(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtTimerr)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    mTimer->stop();
    mTimer->setTimerType(Qt::PreciseTimer);
    ui->radioPrecise->setChecked(true);

    mCounter = new QElapsedTimer();

    connect(mTimer, &QTimer::timeout, this, &QtTimerr::timerTimeOut);
}

QtTimerr::~QtTimerr()
{
    delete mCounter;
    delete ui;
}

void QtTimerr::timerTimeOut()
{
    QApplication::beep();
    QTime currTime = QTime::currentTime();
    ui->lcdHour->display(currTime.hour());
    ui->lcdMin->display(currTime.minute());
    ui->lcdSec->display(currTime.second());

    if (mTimer->isSingleShot()) {
        int tmMsec = mCounter->elapsed();
        QString val = QString("流逝的时间：%1").arg(tmMsec);
        ui->labFlow->setText(val);

        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->btnDymc->setEnabled(true);
    }
}

void QtTimerr::on_btnStart_clicked()
{
    mTimer->setInterval(ui->spinIntv->value());
    mTimer->setSingleShot(!(ui->radioContinue->isChecked()));
    if (ui->radioPrecise->isChecked()) {
        mTimer->setTimerType(Qt::PreciseTimer);
    } else if (ui->radioCoarse->isChecked()) {
        mTimer->setTimerType(Qt::CoarseTimer);
    } else if (ui->radioVeryCoarse->isChecked()) {
        mTimer->setTimerType(Qt::VeryCoarseTimer);
    }

    mTimer->start();
    mCounter->start();

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnDymc->setEnabled(false);
}

void QtTimerr::on_btnStop_clicked()
{
    mTimer->stop();
    int tmMsec = mCounter->elapsed();
    int ms = tmMsec % 1000;
    int s = tmMsec / 1000;
    QString val = QString("流逝的时间：%1秒，%2毫秒").arg(s).arg(ms);
    ui->labFlow->setText(val);

    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnDymc->setEnabled(true);
}

void QtTimerr::on_btnDymc_clicked()
{
    mTimer->setSingleShot(true);
    int intv = ui->spinIntv->value();
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &QtTimerr::timerTimeOut);

    mCounter->start();
    ui->btnDymc->setEnabled(false);
}
