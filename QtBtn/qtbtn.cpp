#include "qtbtn.h"
#include "./ui_qtbtn.h"

QtBtn::QtBtn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtBtn)
{
    ui->setupUi(this);
}

QtBtn::~QtBtn()
{
    delete ui;
}


void QtBtn::on_btnLeft_clicked()
{
    ui->txtShow->setAlignment(Qt::AlignLeft);
}


void QtBtn::on_btnCenter_clicked()
{
    ui->txtShow->setAlignment(Qt::AlignCenter);
}


void QtBtn::on_btnRight_clicked()
{
    ui->txtShow->setAlignment(Qt::AlignRight);
}


void QtBtn::on_btnBlod_clicked(bool checked)
{
    QFont font = ui->txtShow->font();
    font.setBold(checked);
    ui->txtShow->setFont(font);
}


void QtBtn::on_btnItalic_clicked(bool checked)
{
    QFont font = ui->txtShow->font();
    font.setItalic(checked);
    ui->txtShow->setFont(font);
}


void QtBtn::on_btnUnderline_clicked(bool checked)
{
    QFont font = ui->txtShow->font();
    font.setUnderline(checked);
    ui->txtShow->setFont(font);
}


void QtBtn::on_btnReadOnly_clicked(bool checked)
{
    ui->txtShow->setReadOnly(checked);
}


void QtBtn::on_btnClearEnable_clicked(bool checked)
{
    ui->txtShow->setClearButtonEnabled(checked);
}


void QtBtn::on_btnEnable_clicked(bool checked)
{
    ui->txtShow->setEnabled(checked);
}


void QtBtn::on_radioBlack_clicked()
{
    QPalette plet =  ui->txtShow->palette();
    plet.setColor(QPalette::Text, Qt::black);
    ui->txtShow->setPalette(plet);
}


void QtBtn::on_radioRed_clicked()
{
    QPalette plet =  ui->txtShow->palette();
    plet.setColor(QPalette::Text, Qt::red);
    ui->txtShow->setPalette(plet);
}


void QtBtn::on_radioBlue_clicked()
{
    QPalette plet =  ui->txtShow->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    ui->txtShow->setPalette(plet);
}

