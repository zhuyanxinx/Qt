#include "tformdoc.h"
#include "ui_tformdoc.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDialog>
#include <QToolBar>
#include <QVBoxLayout>

TFormDoc::TFormDoc(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TFormDoc)
{
    ui->setupUi(this);
    QToolBar* toolBar = new QToolBar("Doc", this);
    toolBar->addAction(ui->actionOpen);
    toolBar->addAction(ui->actionFont);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionCopy);
    toolBar->addAction(ui->actionCut);
    toolBar->addAction(ui->actionPaste);
    toolBar->addAction(ui->actionUndo);
    toolBar->addAction(ui->actionRedo);
    toolBar->addAction(ui->actionClear);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionClose);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QVBoxLayout* vlayout = new QVBoxLayout();
    this->setLayout(vlayout);
    vlayout->addWidget(toolBar);
    vlayout->addWidget(ui->plainTextEdit);
}

TFormDoc::~TFormDoc()
{
    delete ui;
}

void TFormDoc::on_actionOpen_triggered()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString fname = QFileDialog::getOpenFileName(this, "Open file", appPath,
        "C/C++(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    if (fname.isEmpty()) {
        return;
    }
    QFile file(fname);
    bool opend = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!opend) {
        return;
    }
    ui->plainTextEdit->clear();
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui->plainTextEdit->appendPlainText(line);
    }
    file.close();
    QFileInfo fileIf(fname);
    QString fshortName = fileIf.fileName();
    setWindowTitle(fshortName);
    emit titleChanged(fshortName);
}

void TFormDoc::on_actionFont_triggered()
{
    QFont font = ui->plainTextEdit->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    if (ok) {
        ui->plainTextEdit->setFont(font);
    }
}

void TFormDoc::on_actionSave_triggered()
{
}
