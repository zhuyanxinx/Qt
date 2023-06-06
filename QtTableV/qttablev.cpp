#include "qttablev.h"
#include "./ui_qttablev.h"

#include <QFileDialog>
#include <QItemSelectionModel>
#include <QLabel>
#include <QModelIndex>
#include <QStandardItemModel>

QtTableV::QtTableV(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtTableV)
{
    ui->setupUi(this);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    labCurFile = new QLabel("File:", this);
    labCurFile->setMinimumWidth(200);
    labCellPos = new QLabel("Pos:", this);
    labCellPos->setMinimumWidth(200);
    labCellText = new QLabel("Text:", this);
    labCellText->setMinimumWidth(200);
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);
    modelStand = new QStandardItemModel(2, FixedColumnCount, this);
    modelSelect = new QItemSelectionModel(modelStand, this);

    ui->tableView->setModel(modelStand);
    ui->tableView->setSelectionModel(modelSelect);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(modelSelect, &QItemSelectionModel::currentChanged, this, &QtTableV::onModelSelectCurrentChanged);
}

QtTableV::~QtTableV()
{
    delete ui;
}

void QtTableV::onModelSelectCurrentChanged(const QModelIndex& current, const QModelIndex& previos)
{
    if (current.isValid()) {
        labCellPos->setText(QString::asprintf("postion: %d row, %d column", current.row(), current.column()));

        QStandardItem* item = modelStand->itemFromIndex(current);
        labCellText->setText("text: " + item->text());
        ui->actionTextBold->setChecked(item->font().bold());
    }
}

void QtTableV::on_actionOpenFile_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", path, "文本文件(*.txt);;所有文件(*.*)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QStringList lstContent;
    ui->plainTextEdit->clear();
    QTextStream txtStream(&file);
    while (!txtStream.atEnd()) {
        QString line = txtStream.readLine();
        ui->plainTextEdit->appendPlainText(line);
        lstContent.append(line);
    }
    file.close();

    labCurFile->setText("file: " + fileName);
    ui->actionAppRow->setEnabled(true);
    ui->actionInsertRow->setEnabled(true);
    ui->actionDeleteRow->setEnabled(true);

    initModelData(lstContent);
}

void QtTableV::initModelData(QStringList& lstContent)
{
    int count = lstContent.size();
    modelStand->setRowCount(count - 1);
    QString header = lstContent.at(0);
    QStringList lstHeader = header.split(QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);
    modelStand->setHorizontalHeaderLabels(lstHeader);

    QStandardItem* item;
    int j;
    for (int i = 1; i < count; ++i) {
        QString line = lstContent.at(i);
        QStringList lstRow = line.split(QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);
        for (j = 0; j < FixedColumnCount; ++j) {
            item = new QStandardItem(lstRow.at(j));
            modelStand->setItem(i - 1, j, item);
        }
        item = new QStandardItem(lstRow.at(j));
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));
        item->setCheckState(lstRow.at(j) == "g" ? Qt::Unchecked : Qt::Checked);
        modelStand->setItem(i - 1, j, item);
    }
}
