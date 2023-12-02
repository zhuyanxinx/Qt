#include "mdieditor.h"
#include "./ui_mdieditor.h"
#include "teditordoc.h"
#include <QFileDialog>
#include <QMdiSubWindow>

MdiEditor::MdiEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MdiEditor)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
}

MdiEditor::~MdiEditor()
{
    delete ui;
}

void MdiEditor::on_actionNew_triggered()
{
    TEditorDoc* doc = new TEditorDoc();
    ui->mdiArea->addSubWindow(doc);
    doc->show();

    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    ui->actionFont->setEnabled(true);
}

void MdiEditor::on_actionOpen_triggered()
{
    bool needNew = true;
    TEditorDoc* doc;
    if (ui->mdiArea->subWindowList().size() > 0) {
        doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
        needNew = doc->fileOpened();
    }
    QString path = QCoreApplication::applicationDirPath();
    QString fname = QFileDialog::getOpenFileName(this, "Open file", path,
        "C/C++(*.h *.cpp);;Text(*.txt);;AllFiles(*.*)");
    if (fname.isEmpty()) {
        return;
    }
    if (needNew) {
        doc = new TEditorDoc(this);
        ui->mdiArea->addSubWindow(doc);
    }

    doc->loadFromFile(fname);
    doc->show();

    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    ui->actionFont->setEnabled(true);
}

void MdiEditor::on_actionCut_triggered()
{
    TEditorDoc* doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
    doc->textCut();
}

void MdiEditor::on_actionCopy_triggered()
{
    TEditorDoc* doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
    doc->textCopy();
}

void MdiEditor::on_actionPaste_triggered()
{
    TEditorDoc* doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
    doc->textPaste();
}

void MdiEditor::on_actionFont_triggered()
{
    TEditorDoc* doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
    doc->setEditorFont();
}

void MdiEditor::on_actionSave_triggered()
{
    TEditorDoc* doc = dynamic_cast<TEditorDoc*>(ui->mdiArea->activeSubWindow()->widget());
    doc->saveFile();
}
