#include "ddwidget.h"
#include "./ui_ddwidget.h"

#include <QGroupBox>
#include <QKeyEvent>

DDWidget::DDWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DDWidget)
{
    ui->setupUi(this);
    itemView = ui->listWidgetSrc;
    refreshUI(ui->groupSrc);

    setWidgetAttr(ui->listWidgetSrc, false, true, Qt::MoveAction, QAbstractItemView::DragOnly);
    setWidgetAttr(ui->listWidget, true, true, Qt::MoveAction, QAbstractItemView::DragDrop);
    setWidgetAttr(ui->treeWidget, true, true, Qt::MoveAction, QAbstractItemView::DragDrop);
    setWidgetAttr(ui->tableWidget, true, true, Qt::MoveAction, QAbstractItemView::DragDrop);

    ui->listWidgetSrc->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);
}

DDWidget::~DDWidget()
{
    delete ui;
}

void DDWidget::refreshUI(QGroupBox* group)
{
    ui->chkAcceptDrop->setChecked(itemView->acceptDrops());
    ui->chkDragEnable->setChecked(itemView->dragEnabled());
    ui->comboMode->setCurrentIndex(itemView->dragDropMode());
    int idx = actionIndex(itemView->defaultDropAction());
    ui->comboAction->setCurrentIndex(idx);

    QFont font = ui->groupSrc->font();
    font.setBold(false);
    ui->groupSrc->setFont(font);
    ui->groupList->setFont(font);
    ui->groupTree->setFont(font);
    ui->groupTable->setFont(font);

    font.setBold(true);
    group->setFont(font);
}
bool DDWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() != QEvent::KeyPress) {
        return QWidget::eventFilter(watched, event);
    }
    QKeyEvent* keyE = static_cast<QKeyEvent*>(event);
    if (keyE->key() != Qt::Key_Delete) {
        return QWidget::eventFilter(watched, event);
    }
    if (watched == ui->listWidgetSrc) {
        delete ui->listWidgetSrc->takeItem(ui->listWidgetSrc->currentRow());
    } else if (watched == ui->listWidget) {
        delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    } else if (watched == ui->treeWidget) {
        QTreeWidgetItem* item = ui->treeWidget->currentItem();
        if (item->parent() != nullptr) {
            item->parent()->removeChild(item);
        }
        //        else {
        //            int idx = ui->treeWidget->indexOfTopLevelItem(item);
        //            ui->treeWidget->takeTopLevelItem(idx);
        //        }
        delete item;
    } else if (watched == ui->tableWidget) {
        delete ui->tableWidget->takeItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn());
    }
    return true;
}
int DDWidget::actionIndex(Qt::DropAction action)
{
    switch (action) {
    case Qt::CopyAction:
        return 0;
    case Qt::MoveAction:
        return 2;
    case Qt::LinkAction:
        return 4;
    case Qt::IgnoreAction:
        return 0;
    default:
        return 0;
    }
}

Qt::DropAction DDWidget::actionType(int index)
{
    switch (index) {
    case 1:
        return Qt::CopyAction;
    case 2:
        return Qt::MoveAction;
    case 4:
        return Qt::LinkAction;
    case 0:
        return Qt::IgnoreAction;
    default:
        return Qt::IgnoreAction;
    }
}

void DDWidget::setWidgetAttr(QAbstractItemView* widget, bool acceptDrop, bool dragEnable, Qt::DropAction action, QAbstractItemView::DragDropMode mode)
{
    widget->setAcceptDrops(false);
    widget->setDragEnabled(true);
    widget->setDefaultDropAction(Qt::CopyAction);
    widget->setDragDropMode(QAbstractItemView::DragDrop);
}

void DDWidget::on_radioSrc_clicked()
{
    itemView = ui->listWidgetSrc;
    refreshUI(ui->groupSrc);
}

void DDWidget::on_radioList_clicked()
{
    itemView = ui->listWidget;
    refreshUI(ui->groupList);
}

void DDWidget::on_radioTree_clicked()
{
    itemView = ui->treeWidget;
    refreshUI(ui->groupTree);
}

void DDWidget::on_radioTable_clicked()
{
    itemView = ui->tableWidget;
    refreshUI(ui->groupTable);
}

void DDWidget::on_chkAcceptDrop_clicked(bool checked)
{
    itemView->setAcceptDrops(checked);
}

void DDWidget::on_chkDragEnable_clicked(bool checked)
{
    itemView->setDragEnabled(checked);
}

void DDWidget::on_comboMode_currentIndexChanged(int index)
{
    itemView->setDragDropMode((QAbstractItemView::DragDropMode)index);
}

void DDWidget::on_comboAction_currentIndexChanged(int index)
{
    itemView->setDefaultDropAction(actionType(index));
}
