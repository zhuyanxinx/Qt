#include "qtcustevent.h"
#include "./ui_qtcustevent.h"

QtCustEvent::QtCustEvent(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtCustEvent)
{
    ui->setupUi(this);
    connect(ui->label, &TClickedLabel::doubleClicked, this, QtCustEvent::doubleClick());
}

QtCustEvent::~QtCustEvent()
{
    delete ui;
}

void QtCustEvent::doubleClick()
{
    ui->label->setText("Double clicked lable, slots");
    ui->label->adjustSize();
}

void QtCustEvent::mouseDoubleClickEvent(QMouseEvent* event)
{
    ui->label->setText("Double clicked widget");
    ui->label->adjustSize();
}
