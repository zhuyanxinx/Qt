#include "qtspin.h"
#include "./ui_qtspin.h"

QtSpin::QtSpin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSpin)
{
    ui->setupUi(this);
    this->connect(ui->spinNum, &QSpinBox::valueChanged, this, &QtSpin::on_btnCalc_clicked);
    this->connect(ui->spinPrice, &QDoubleSpinBox::valueChanged, this, &QtSpin::on_btnCalc_clicked);

}

QtSpin::~QtSpin()
{
    delete ui;
}


void QtSpin::on_btnCalc_clicked()
{
    int num = ui->spinNum->value();
    float price = ui->spinPrice->value();
    float total = price * num;
    ui->spinTotal->setValue(total);
}


void QtSpin::on_spinBin_valueChanged(int bin)
{
    ui->spinBin->setValue(bin);
    ui->spinDec->setValue(bin);
    ui->spinHex->setValue(bin);
}


void QtSpin::on_spinDec_valueChanged(int bin)
{
    ui->spinBin->setValue(bin);
    ui->spinDec->setValue(bin);
    ui->spinHex->setValue(bin);
}


void QtSpin::on_spinHex_valueChanged(int bin)
{
    ui->spinBin->setValue(bin);
    ui->spinDec->setValue(bin);
    ui->spinHex->setValue(bin);
}

