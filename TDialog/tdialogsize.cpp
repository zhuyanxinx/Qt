#include "tdialogsize.h"
#include "ui_tdialogsize.h"

#include <QMessageBox>

TDialogSize::TDialogSize(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TDialogSize)
{
    ui->setupUi(this);
}

TDialogSize::~TDialogSize()
{
    QMessageBox::information(this, "info", "TDialogSize deleted");
    delete ui;
}

void TDialogSize::setRowColumn(int row, int col)
{
    ui->spinRow->setValue(row);
    ui->spinCol->setValue(col);
}

int TDialogSize::rowCount()
{
    return ui->spinRow->value();
}

int TDialogSize::columnCount()
{
    return ui->spinCol->value();
}
