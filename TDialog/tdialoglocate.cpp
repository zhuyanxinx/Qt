#include "tdialoglocate.h"
#include "ui_tdialoglocate.h"

#include <QCloseEvent>
#include <QShowEvent>

TDialogLocate::TDialogLocate(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TDialogLocate)
{
    ui->setupUi(this);
}

TDialogLocate::~TDialogLocate()
{
    delete ui;
}

void TDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinRow->setMaximum(rowCount);
    ui->spinCol->setMaximum(colCount);
}

void TDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinRow->setValue(rowNo);
    ui->spinCol->setValue(colNo);
}

void TDialogLocate::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit changeActionEnable(true);
}

void TDialogLocate::showEvent(QShowEvent* event)
{
    event->accept();
    emit changeActionEnable(false);
}

void TDialogLocate::on_btnOk_clicked()
{
    QString text = ui->lineEdit->text();
    int row = ui->spinRow->value();
    int col = ui->spinCol->value();

    if (ui->chkAddRow->isChecked()) {
        ui->spinRow->setValue(row + 1);
    }
    if (ui->chkAddCol->isChecked()) {
        ui->spinCol->setValue(col + 1);
    }
    emit changeCellText(row, col, text);
}
