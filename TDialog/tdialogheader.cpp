#include "tdialogheader.h"
#include "ui_tdialogheader.h"

#include <QMessageBox>
#include <QStringListModel>

TDialogHeader::TDialogHeader(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TDialogHeader)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    ui->listView->setModel(model);
}

TDialogHeader::~TDialogHeader()
{
    QMessageBox::information(this, "info", "TDialogHeader deleted");
    delete ui;
}

void TDialogHeader::setHealderList(QStringList& list)
{
    model->setStringList(list);
}

QStringList TDialogHeader::headerList()
{
    return model->stringList();
}
