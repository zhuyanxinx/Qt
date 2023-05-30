#include "qtslider.h"
#include "./ui_qtslider.h"

QtSlider::QtSlider(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSlider)
{
    ui->setupUi(this);
    connect(ui->hSlider, &QSlider::valueChanged, this, &QtSlider::valueChanged);
    connect(ui->hScrollBar, &QSlider::valueChanged, this, &QtSlider::valueChanged);
    connect(ui->dial, &QSlider::valueChanged, this, &QtSlider::valueChanged);
}

QtSlider::~QtSlider()
{
    delete ui;
}

void QtSlider::valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void QtSlider::on_chkTxtVisible_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void QtSlider::on_chkInvAppear_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void QtSlider::on_radioPercent_clicked()
{
    ui->progressBar->setFormat("%p%");
}


void QtSlider::on_radioCurrent_clicked()
{
    ui->progressBar->setFormat("%v");
}

