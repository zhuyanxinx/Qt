#include "xyzhttp.h"
#include "./ui_xyzhttp.h"

XyzHttp::XyzHttp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XyzHttp)
{
    ui->setupUi(this);
}

XyzHttp::~XyzHttp()
{
    delete ui;
}

