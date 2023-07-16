#include "qtdragevent.h"
#include "./ui_qtdragevent.h"
#include <QFileInfo>
#include <QMimeData>

QtDragEvent::QtDragEvent(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtDragEvent)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->plainTextEdit->setAcceptDrops(false);
    ui->label->setAcceptDrops(false);
    ui->label->setScaledContents(true);
}

QtDragEvent::~QtDragEvent()
{
    delete ui;
}

void QtDragEvent::resizeEvent(QResizeEvent* event)
{
    QSize txtSize = ui->plainTextEdit->size();
    ui->plainTextEdit->move(10, 10);
    ui->label->move(10, txtSize.height() + 10);
    ui->plainTextEdit->resize(this->width() - 20, txtSize.height());
    ui->label->resize(this->width() - 20, this->height() - txtSize.height() - 20);
    event->accept();
}

void QtDragEvent::dragEnterEvent(QDragEnterEvent* event)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("dragEnterEvent::mimeData::formats:");
    for (auto& item : event->mimeData()->formats()) {
        ui->plainTextEdit->appendPlainText(item);
    }
    ui->plainTextEdit->appendPlainText("dragEnterEvent::mimeData::urls:");
    for (auto& item : event->mimeData()->urls()) {
        ui->plainTextEdit->appendPlainText(item.path());
    }
    if (event->mimeData()->hasUrls()) {
        QString fileName = event->mimeData()->urls().at(0).fileName();
        QFileInfo fileIf(fileName);
        QString ex = fileIf.suffix().toUpper();
        if (ex == "PNG") {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void QtDragEvent::dropEvent(QDropEvent* event)
{
    QString path = event->mimeData()->urls().at(0).path();
    path = path.right(path.length() - 1);
    QPixmap pixmap(path);
    ui->label->setPixmap(pixmap);
    event->accept();
}
