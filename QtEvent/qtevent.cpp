#include "qtevent.h"
#include "./ui_qtevent.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

QtEvent::QtEvent(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtEvent)
{
    ui->setupUi(this);
    grabKeyboard();
}

QtEvent::~QtEvent()
{
    delete ui;
}

void QtEvent::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/pic/images/binge.png"));
}

void QtEvent::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    QPoint pt = event->pos();
    QPointF ptP = event->position();
    QPointF ptS = event->scenePosition();
    QPointF ptG = event->globalPosition();

    QString xy = QString::asprintf("pos:%d, %d", pt.x(), pt.y());
    xy += QString::asprintf("\nposition:%.0f, %.0f", ptP.x(), ptP.y());
    xy += QString::asprintf("\nscenePosition:%.0f, %.0f", ptS.x(), ptS.y());
    xy += QString::asprintf("\nglobalPosition:%.0f, %.0f", ptG.x(), ptG.y());

    ui->labMove->setText(xy);
    ui->labMove->adjustSize();
    ui->labMove->move(event->pos());
    QWidget::mousePressEvent(event);
}

void QtEvent::keyPressEvent(QKeyEvent* event)
{
    QPoint pt = ui->btnMove->pos();
    int key = event->key();
    if (key == Qt::Key_A || key == Qt::Key_Left) {
        ui->btnMove->move(pt.x() - 20, pt.y());
    }
    if (key == Qt::Key_D || key == Qt::Key_Right) {
        ui->btnMove->move(pt.x() + 20, pt.y());
    }
    if (key == Qt::Key_W || key == Qt::Key_Up) {
        ui->btnMove->move(pt.x(), pt.y() - 20);
    }
    if (key == Qt::Key_S || key == Qt::Key_Down) {
        ui->btnMove->move(pt.x(), pt.y() + 20);
    }
    QWidget::keyPressEvent(event);
}

void QtEvent::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton res = QMessageBox::question(
        this, "Confirm", "Quit now?",
        QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
