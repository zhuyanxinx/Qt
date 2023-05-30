#include "qtdatetimee.h"
#include "./ui_qtdatetimee.h"

QtDateTimee::QtDateTimee(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtDateTimee)
{
    ui->setupUi(this);
}

QtDateTimee::~QtDateTimee()
{
    delete ui;
}


void QtDateTimee::on_pushButton_clicked()
{
   QDateTime current = QDateTime::currentDateTime();
   ui->timeEdit->setTime((current.time()));
   ui->editTime->setText(current.toString("HH:mm:ss"));

   ui->dateEdit->setDate(current.date());
   ui->editDate->setText(current.toString("yyyy-MM-dd"));

   ui->dateTimeEdit->setDateTime(current);
   ui->editDateTime->setText(current.toString("yyyy-MM-dd HH:mm:ss"));
}


void QtDateTimee::on_btnTime_clicked()
{
    QTime tm(13, 14, 5);
    QString tms = tm.toString("HH:mm:ss");
    qDebug("Original time:%s", tms.toLocal8Bit().data());

    QTime tm2 = tm.addSecs(150);
    tms = tm2.toString("HH:mm:ss");
    qDebug("150s later time:%s", tms.toLocal8Bit().data());

    tm2 = QTime::currentTime();
    tms = tm2.toString("HH:mm:ss zzz");
    qDebug("currentTime:%s", tms.toLocal8Bit().data());
    qDebug("hour:%d", tm2.hour());
    qDebug("minute:%d", tm2.minute());
    qDebug("second:%d", tm2.second());
    qDebug("msec:%d", tm2.msec());
}


void QtDateTimee::on_btnDate_clicked()
{
    QDate DT1(2023, 7, 26);
    QString tms = DT1.toString("yyyy-MM-dd");
    qDebug("DT1:%s", tms.toLocal8Bit().data());

    QDate DT2;
    DT2.setDate(2023, 8, 25);
    tms = DT2.toString("yyyy-MM-dd");
    qDebug("DT2:%s", tms.toLocal8Bit().data());
    qDebug("Days betweent:%d", DT2.daysTo(DT1));

    DT2 = QDate::currentDate();
    tms = DT2.toString("yyyy-MM-dd");
    qDebug("currentDate:%s", tms.toLocal8Bit().data());
    qDebug("year:%d", DT2.year());
    qDebug("month:%d", DT2.month());
    qDebug("day:%d", DT2.day());
    qDebug("dayOfWeek:%d", DT2.dayOfWeek());
}


void QtDateTimee::on_btnFormatTime_clicked()
{
    QString val = ui->editTime->text();
    val = val.trimmed();
    if(val.isEmpty()){
        return;
    }
    QTime dt = QTime::fromString(val, "HH:mm:ss");
    ui->timeEdit->setTime(dt);
}


void QtDateTimee::on_btnFormatDate_clicked()
{
    QString val = ui->editDate->text();
    val = val.trimmed();
    if(val.isEmpty()){
        return;
    }
    QDate dt = QDate::fromString(val, "yyyy-MM-dd");
    ui->dateEdit->setDate(dt);
}


void QtDateTimee::on_btnFormatDateTime_clicked()
{
    QString val = ui->editDateTime->text();
    val = val.trimmed();
    if(val.isEmpty()){
        return;
    }
    QDateTime dt = QDateTime::fromString(val, "yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dt);
}


void QtDateTimee::on_calendar_selectionChanged()
{
    QString sel = ui->calendar->selectedDate().toString("yyyy-MM-dd");
    ui->editCalendar->setText(sel);
}

