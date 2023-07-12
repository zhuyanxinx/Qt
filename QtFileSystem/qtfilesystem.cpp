#include "qtfilesystem.h"
#include "./ui_qtfilesystem.h"

#include <QFileDialog>
#include <QFileSystemModel>

QtFileSystem::QtFileSystem(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtFileSystem)
{
    ui->setupUi(this);
    modelFile = new QFileSystemModel(this);
    modelFile->setRootPath("");
    ui->treeView->setModel(modelFile);
    ui->listView->setModel(modelFile);
    ui->tableView->setModel(modelFile);
    connect(ui->treeView, &QTreeView::clicked, ui->listView, &QListView::setRootIndex);
    connect(ui->treeView, &QTreeView::clicked, ui->tableView, &QTableView::setRootIndex);
}

QtFileSystem::~QtFileSystem()
{
    delete ui;
}

void QtFileSystem::on_actionSetRoot_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose dir", QDir::currentPath());
    if (dir.isEmpty()) {
        return;
    }
    ui->treeView->setRootIndex(modelFile->index(dir));
    ui->listView->setRootIndex(modelFile->index(dir));
    ui->tableView->setRootIndex(modelFile->index(dir));
}

void QtFileSystem::on_radioFileDir_clicked()
{
    ui->groupFilter->setEnabled(true);
    modelFile->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
}

void QtFileSystem::on_radioOnlyDir_clicked()
{
    ui->groupFilter->setEnabled(false);
    modelFile->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}

void QtFileSystem::on_chkFile_clicked(bool checked)
{
    ui->comboType->setEnabled(checked);
    ui->btnApply->setEnabled(checked);
    modelFile->setNameFilterDisables(!checked);
}

void QtFileSystem::on_btnApply_clicked()
{
    QStringList filter = ui->comboType->currentText().trimmed().split(";", Qt::SkipEmptyParts);
    modelFile->setNameFilters(filter);
}

void QtFileSystem::on_treeView_clicked(const QModelIndex& index)
{
    ui->labFileName->setText(modelFile->fileName(index));
    ui->labFileType->setText(modelFile->type(index));
    ui->labFilePath->setText(modelFile->filePath(index));
    ui->chkFileIsDir->setChecked(modelFile->isDir(index));
    int size = modelFile->size(index);
    QString sizes = size < 1024 ? QString("%1 KB").arg(size) : QString::asprintf("%.1f MB", size / 1024.0);
    ui->labFileSize->setText(sizes);
}
