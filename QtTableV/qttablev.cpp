#include "qttablev.h"
#include "./ui_qttablev.h"

#include "tcomboboxdelegate.h"
#include "tspindelegate.h"
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
    modelStand = new QStandardItemModel(0, FixedColumnCount, this);
    modelSelect = new QItemSelectionModel(modelStand, this);

    ui->tableView->setModel(modelStand);
    ui->tableView->setSelectionModel(modelSelect);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(modelSelect, &QItemSelectionModel::currentChanged, this, &QtTableV::onModelSelectCurrentChanged);

    spinDelegate = new TSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, spinDelegate);

    comboDelegate = new TComboBoxDelegate(this);
    QStringList lstOpt;
    lstOpt << "G"
           << "H"
           << "J"
           << "K"
           << "L";
    comboDelegate->setItems(lstOpt, false);

    ui->tableView->setItemDelegateForColumn(1, comboDelegate);
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
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
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
    static QRegularExpression reSpace(R"(\s+)");
    int count = lstContent.size();
    modelStand->setRowCount(count - 1);
    QString header = lstContent.at(0);
    QStringList lstHeader = header.split(reSpace, Qt::SkipEmptyParts);
    modelStand->setHorizontalHeaderLabels(lstHeader);

    QStandardItem* item;
    int j;
    for (int i = 1; i < count; ++i) {
        QString line = lstContent.at(i);
        QStringList lstRow = line.split(reSpace, Qt::SkipEmptyParts);
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

void QtTableV::on_actionPreViewData_triggered()
{
    QStandardItem* item;
    QString val;
    for (int c = 0; c < modelStand->columnCount(); ++c) {
        item = modelStand->horizontalHeaderItem(c);
        val.append(item->text()).append(" ");
    }
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(val);

    for (int r = 0; r < modelStand->rowCount(); ++r) {
        val.clear();
        for (int c = 0; c < modelStand->columnCount() - 1; ++c) {
            item = modelStand->item(r, c);
            val.append(item->text()).append(" ");
        }
        item = modelStand->item(r, modelStand->columnCount() - 1);
        val.append(item->checkState() == Qt::Checked ? "Y" : "N");
        ui->plainTextEdit->appendPlainText(val);
    }
}

void QtTableV::on_actionAppRow_triggered()
{
    QList<QStandardItem*> lstItem;
    QStandardItem* item;
    for (int c = 0; c < modelStand->columnCount() - 1; ++c) {
        item = new QStandardItem("0");
        lstItem << item;
    }
    //    QString val = modelStand->headerData(modelStand->columnCount() - 1, Qt::Horizontal).toString();
    item = new QStandardItem();
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    lstItem << item;
    modelStand->insertRow(modelStand->rowCount(), lstItem);
    modelSelect->clearSelection();
    modelSelect->setCurrentIndex(modelStand->index(modelStand->rowCount() - 1, 0), QItemSelectionModel::Select);
}

void QtTableV::on_actionInsertRow_triggered()
{
    QList<QStandardItem*> lstItem;
    QStandardItem* item;
    for (int c = 0; c < modelStand->columnCount() - 1; ++c) {
        item = new QStandardItem("0");
        lstItem << item;
    }
    item = new QStandardItem();
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    lstItem << item;
    QModelIndex curIdx = modelSelect->currentIndex();
    modelStand->insertRow(curIdx.row(), lstItem);
    modelSelect->clearSelection();
    modelSelect->setCurrentIndex(curIdx, QItemSelectionModel::Select);
}

void QtTableV::on_actionDeleteRow_triggered()
{
    QModelIndex curIdx = modelSelect->currentIndex();
    int row = curIdx.row() - 1;
    modelSelect->setCurrentIndex(modelStand->index(row, 0), QItemSelectionModel::Select);
    modelStand->removeRow(curIdx.row());
}

void QtTableV::on_actionAlignLeft_triggered()
{
    if (!modelSelect->hasSelection()) {
        return;
    }
    QModelIndexList lstIdx = modelSelect->selectedIndexes();
    for (auto idx : lstIdx) {
        modelStand->itemFromIndex(idx)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}

void QtTableV::on_actionAlignCenter_triggered()
{
    if (!modelSelect->hasSelection()) {
        return;
    }
    QModelIndexList lstIdx = modelSelect->selectedIndexes();
    for (auto idx : lstIdx) {
        modelStand->itemFromIndex(idx)->setTextAlignment(Qt::AlignCenter);
    }
}

void QtTableV::on_actionAlignRight_triggered()
{
    if (!modelSelect->hasSelection()) {
        return;
    }
    QModelIndexList lstIdx = modelSelect->selectedIndexes();
    for (auto idx : lstIdx) {
        modelStand->itemFromIndex(idx)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void QtTableV::on_actionTextBold_triggered(bool checked)
{
    if (!modelSelect->hasSelection()) {
        return;
    }
    QModelIndexList lstIdx = modelSelect->selectedIndexes();
    for (auto idx : lstIdx) {
        QStandardItem* item = modelStand->itemFromIndex(idx);
        QFont font = item->font();
        font.setBold(checked);
        item->setFont(font);
    }
}

void QtTableV::on_actionQuit_triggered()
{
    qApp->quit();
}
