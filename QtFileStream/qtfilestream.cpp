#include "qtfilestream.h"
#include "ui_qtfilestream.h"
#include <QException>
#include <QFileDialog>
#include <QMessageBox>
#include <QSaveFile>
#include <QTextBlock>

QtFileStream::QtFileStream(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtFileStream)
{
    ui->setupUi(this);
}

QtFileStream::~QtFileStream()
{
    delete ui;
}

QString QtFileStream::getFile(bool save)
{
    QString path = QCoreApplication::applicationDirPath();
    QString title = "Select file";
    QString filter = "C/C++(*.h *.cpp);;Text(*.txt);;All File(*.*)";

    QString fname;
    if (save) {
        fname = QFileDialog::getSaveFileName(this, title, path, filter);
    } else {
        fname = QFileDialog::getOpenFileName(this, title, path, filter);
    }

    if (fname.isEmpty()) {
        return fname;
    }
    QFileInfo fileIf(fname);
    QDir::setCurrent(fileIf.absoluteFilePath());
    return fname;
}

void QtFileStream::on_actionQFileOpen_triggered()
{

    QFile file(getFile());
    if (!file.exists()) {
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    ui->plainFile->appendPlainText(file.readAll());
    file.close();
}

void QtFileStream::on_actionQFileSaveAs_triggered()
{
    QFile file(getFile(true));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QString txt = ui->plainFile->toPlainText();
    file.write(txt.toUtf8(), txt.toUtf8().length());
    file.close();
}

void QtFileStream::on_actionQSaveFile_triggered()
{
    QSaveFile file(getFile(true));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    file.setDirectWriteFallback(false);
    try {
        QString txt = ui->plainFile->toPlainText();
        file.write(txt.toUtf8(), txt.toUtf8().length());
        file.commit();
    } catch (...) {
        file.cancelWriting();
        QMessageBox::warning(this, "Can`t save", "Save file exception!");
    }
}

void QtFileStream::on_actionQTextStreamOpen_triggered()
{
    QFile file(getFile());
    if (!file.exists()) {
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream(&file);
    stream.setAutoDetectUnicode(true);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui->plainStream->appendPlainText(line);
    }
    file.close();
}

void QtFileStream::on_actionQTextStreamSaveAs_triggered()
{
    QSaveFile file(getFile(true));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    file.setDirectWriteFallback(false);
    try {
        QTextStream stream(&file);
        stream.setAutoDetectUnicode(true);
        QTextDocument* doc = ui->plainStream->document();
        for (int i = 0; i < doc->blockCount(); ++i) {
            stream << doc->findBlockByNumber(i).text();
            stream << "\n";
        }
        file.commit();
    } catch (...) {
        file.cancelWriting();
        QMessageBox::warning(this, "Can`t save", "Save file exception!");
    }
}
