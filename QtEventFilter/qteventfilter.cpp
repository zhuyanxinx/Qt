#include "qteventfilter.h"
#include "./ui_qteventfilter.h"

QtEventFilter::QtEventFilter(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtEventFilter)
{
    ui->setupUi(this);
    ui->labDC->installEventFilter(this);
    ui->labSC->installEventFilter(this);
}

QtEventFilter::~QtEventFilter()
{
    delete ui;
}

bool QtEventFilter::eventFilter(QObject* watched, QEvent* event)
{
    QEvent::Type eType = event->type();
    if (watched == ui->labSC) {
        if (eType == QEvent::Enter) {
            ui->labSC->setStyleSheet("background-color:rgb(110, 255, 255);");
        } else if (eType == QEvent::Leave) {
            ui->labSC->setText("Single Click");
            ui->labSC->setStyleSheet("");
        } else if (eType == QEvent::MouseButtonPress) {
            ui->labSC->setText("MouseButtonPress");
        } else if (eType == QEvent::MouseButtonRelease) {
            ui->labSC->setText("MouseButtonRelease");
        }
    }

    if (watched == ui->labDC) {
        if (eType == QEvent::Enter) {
            ui->labDC->setStyleSheet("background-color:rgb(80, 255, 120);");
        } else if (eType == QEvent::Leave) {
            ui->labDC->setText("Double Click");
            ui->labDC->setStyleSheet("");
        } else if (eType == QEvent::MouseButtonDblClick) {
            ui->labDC->setText("MouseButtonDblClick");
        }
    }
    return QWidget::eventFilter(watched, event);
}
