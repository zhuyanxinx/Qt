#include "tdialog.h"
#include "./ui_tdialog.h"
#include "tdialogheader.h"
#include "tdialoglocate.h"
#include "tdialogsize.h"

#include <QItemSelectionModel>
#include <QLabel>
#include <QStandardItemModel>

TDialog::TDialog(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::TDialog)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableView);
    labCellPos = new QLabel("Cell:", this);
    labCellPos->setMinimumWidth(200);
    labCellText = new QLabel("Text:", this);
    labCellText->setMinimumWidth(200);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);

    model = new QStandardItemModel(4, 4, this);
    QStringList header;
    header << "A"
           << "B"
           << "C"
           << "D";
    model->setHorizontalHeaderLabels(header);
    selmodel = new QItemSelectionModel(model);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(selmodel);

    connect(selmodel, &QItemSelectionModel::currentChanged, this, &TDialog::modelSelectChanged);
}

TDialog::~TDialog()
{
    delete ui;
}

void TDialog::on_actionSetSize_triggered()
{
    TDialogSize* dlgSize = new TDialogSize();
    dlgSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dlgSize->setRowColumn(model->rowCount(), model->columnCount());

    int ret = dlgSize->exec();
    if (ret == QDialog::Accepted) {
        model->setColumnCount(dlgSize->columnCount());
        model->setRowCount(dlgSize->rowCount());
    }
    delete dlgSize;
}

void TDialog::on_actionSetHeader_triggered()
{
    if (dlgHeader == nullptr) {
        dlgHeader = new TDialogHeader(this);
    }

    QStringList list;
    for (int i = 0; i < model->columnCount(); ++i) {
        list.append(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    }
    dlgHeader->setHealderList(list);
    int ret = dlgHeader->exec();
    if (ret == QDialog::Accepted) {
        model->setHorizontalHeaderLabels(dlgHeader->headerList());
    }
}

void TDialog::on_actionLocate_triggered()
{
    TDialogLocate* dlgLocate = new TDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    dlgLocate->setWindowFlag(Qt::WindowStaysOnTopHint);
    dlgLocate->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    dlgLocate->setSpinRange(model->rowCount(), model->columnCount());
    QModelIndex curIdx = selmodel->currentIndex();
    if (curIdx.isValid()) {
        dlgLocate->setSpinValue(curIdx.row(), curIdx.column());
    }
    connect(dlgLocate, &TDialogLocate::changeCellText, this, &TDialog::setCellText);
    connect(dlgLocate, &TDialogLocate::changeActionEnable, ui->actionLocate, &QAction::setEnabled);
    connect(this, &TDialog::cellSelectChanged, dlgLocate, &TDialogLocate::setSpinValue);
    dlgLocate->show();
    dlgLocate->setModal(false);
}

void TDialog::setCellText(int row, int col, QString& text)
{
    QModelIndex idx = model->index(row, col);
    selmodel->clearSelection();
    selmodel->setCurrentIndex(idx, QItemSelectionModel::Select);
    model->setData(idx, text, Qt::DisplayRole);
}

void TDialog::modelSelectChanged(const QModelIndex& current, const QModelIndex& previous)
{
    if (current.isValid()) {
        QString pos = QString::asprintf("Cell: %d, %d", current.row(), current.column());
        labCellPos->setText(pos);
        QStandardItem* item = model->itemFromIndex(current);
        labCellText->setText("Text: " + item->text());
    }
}

void TDialog::on_tableView_clicked(const QModelIndex& index)
{
    emit cellSelectChanged(index.row(), index.column());
}
