
#include "qtlist.h"
#include "./ui_qtlist.h"
#include <QMenu>

QtList::QtList(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtList)
{
    ui->setupUi(this);
    QMenu* menuSel = new QMenu(this);

    ui->tbtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tbtnSelectItem->setMenu(menuSel);

    QToolButton* tbtnMenu = new QToolButton(this);
    tbtnMenu->setPopupMode(QToolButton::InstantPopup);
    tbtnMenu->setText("选择菜单");
    tbtnMenu->setIcon(QIcon(":/icon_form/xinzeng_1.svg"));
    tbtnMenu->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tbtnMenu->setMenu(menuSel);
    ui->toolBar->addWidget(tbtnMenu);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionQuit);

    menuSel->addAction(ui->actionSelectAll);
    menuSel->addAction(ui->actionSelectNone);
    menuSel->addAction(ui->actionSelectInvs);

    ui->tbtnListInit->setDefaultAction(ui->actionInitList);
    ui->tbtnListAppend->setDefaultAction(ui->actionAddItem);
    ui->tbtnListClear->setDefaultAction(ui->actionClearList);
    ui->tbtnListInsert->setDefaultAction(ui->actionInsertItem);
    ui->tbtnListDelete->setDefaultAction(ui->actionDelItem);

    ui->tbtnSelectAll->setDefaultAction(ui->actionSelectAll);
    ui->tbtnSelectNone->setDefaultAction(ui->actionSelectNone);
    ui->tbtnSelectInvs->setDefaultAction(ui->actionSelectInvs);

    connect(ui->actionQuit, &QAction::triggered, qApp, &QCoreApplication::quit, Qt::QueuedConnection);
}

QtList::~QtList()
{
    delete ui;
}

void QtList::on_actionInitList_triggered()
{
    ui->listWidget->clear();
    bool checked = ui->chkItemEditable->isChecked();
    QIcon icon(":/icon_form/remove-role.svg");
    QListWidgetItem* item;
    for (int i = 0; i < 10; ++i) {
        item = new QListWidgetItem();
        item->setIcon(icon);
        item->setCheckState(Qt::Checked);
        item->setText("item" + QString::number(i));

        int isEditable = checked ? Qt::ItemIsEditable : Qt::NoItemFlags;
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | item->flags().fromInt(isEditable));

        ui->listWidget->addItem(item);
    }
}

void QtList::on_actionInsertItem_triggered()
{
    bool checked = ui->chkItemEditable->isChecked();
    QIcon icon(":/icon_form/remove-role.svg");
    QListWidgetItem* item = new QListWidgetItem();
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    item->setText("item inserted");

    int isEditable = checked ? Qt::ItemIsEditable : Qt::NoItemFlags;
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | item->flags().fromInt(isEditable));

    ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
}

void QtList::on_actionClearList_triggered()
{
    ui->listWidget->clear();
}

void QtList::on_actionAddItem_triggered()
{
    bool checked = ui->chkItemEditable->isChecked();
    QIcon icon(":/icon_form/remove-role.svg");
    QListWidgetItem* item = new QListWidgetItem();
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    item->setText("item append");

    int isEditable = checked ? Qt::ItemIsEditable : Qt::NoItemFlags;
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | item->flags().fromInt(isEditable));
    ui->listWidget->addItem(item);
}

void QtList::on_actionDelItem_triggered()
{
    int row = ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(row);
}

void QtList::on_actionSelectItem_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
    }
}

void QtList::on_actionSelectAll_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        item->setCheckState(Qt::Checked);
    }
}

void QtList::on_actionSelectNone_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

void QtList::on_actionSelectInvs_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        item->setCheckState(item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
    }
}

void QtList::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    QString pret = previous != NULL ? previous->text() : "";
    QString curt = current != NULL ? current->text() : "";
    QString text = QString("%1-->%2").arg(pret, curt);
    ui->txtCurrItem->setText(text);
    ui->txtInfo->appendPlainText(text);
}

void QtList::on_chkSort_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);
}

void QtList::on_tbtnSortAsc_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

void QtList::on_tbtnSortDes_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}

void QtList::on_tbtnClearText_clicked()
{
    ui->txtInfo->clear();
}

void QtList::on_tbtnAddLine_clicked()
{
    ui->txtInfo->appendPlainText("");
}

void QtList::on_listWidget_customContextMenuRequested(const QPoint& pos)
{
    QMenu* menu = new QMenu();
    menu->addAction(ui->actionInitList);
    menu->addAction(ui->actionClearList);
    menu->exec(QCursor::pos());
    delete menu;
}
