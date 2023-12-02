#include "qfiledoc.h"
#include "./ui_qfiledoc.h"

QFileDoc::QFileDoc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QFileDoc)
{
    ui->setupUi(this);
}

QFileDoc::~QFileDoc()
{
    delete ui;
}

