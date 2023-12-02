#include "teditordoc.h"
#include "ui_teditordoc.h"
#include <QFile>
#include <QFileInfo>
#include <QFontDialog>

TEditorDoc::TEditorDoc(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TEditorDoc)
{
    ui->setupUi(this);
}

TEditorDoc::~TEditorDoc()
{
    delete ui;
}

void TEditorDoc::loadFromFile(QString& fname)
{
    QFile file(fname);
    bool open = file.open(QIODevice::Text | QIODevice::ReadOnly);
    if (!open) {
        return;
    }
    QTextStream stream(&file);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    QFileInfo fileIf(fname);
    QString flongName = fileIf.fileName();
    setWindowTitle(flongName + "*");
    mfileName = flongName;
    mfileOpened = true;
}

QString TEditorDoc::currentFileName()
{
    return mfileName;
}

bool TEditorDoc::fileOpened()
{
    return mfileOpened;
}

void TEditorDoc::saveFile()
{
    setWindowModified(false);
}

void TEditorDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void TEditorDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void TEditorDoc::textPaste()
{
    ui->plainTextEdit->paste();
}

void TEditorDoc::setEditorFont()
{
    QFont font = ui->plainTextEdit->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}
