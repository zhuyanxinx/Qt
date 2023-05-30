#include "qttree.h"
#include "./ui_qttree.h"
#include <QFileDialog>
#include <QLabel>
#include <QSpinBox>

QtTree::QtTree(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtTree)
{
    ui->setupUi(this);
    ui->treeWidget->clear();

    // header
    QTreeWidgetItem* header = new QTreeWidgetItem();
    header->setText(ColItem, "Dir/File");
    header->setText(ColType, "Type");
    header->setText(ColDate, "LastModeDate");

    header->setTextAlignment(ColItem, Qt::AlignHCenter | Qt::AlignVCenter);
    header->setTextAlignment(ColType, Qt::AlignHCenter | Qt::AlignVCenter);
    header->setTextAlignment(ColDate, Qt::AlignHCenter | Qt::AlignVCenter);
    ui->treeWidget->setHeaderItem(header);

    // top node
    QIcon icon(":/icon_tree/genjiedian.svg");
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(TopItem);
    rootItem->setIcon(ColItem, icon);
    rootItem->setText(ColItem, "icon");
    rootItem->setText(ColType, "Top");

    rootItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    rootItem->setCheckState(ColItem, Qt::Checked);
    ui->treeWidget->addTopLevelItem(rootItem);

    // status bar
    labNode = new QLabel("Text", this);
    labNode->setMinimumWidth(200);
    ui->statusbar->addWidget(labNode);

    spinRatio = new QSpinBox(this);
    spinRatio->setRange(0, 2000);
    spinRatio->setValue(100);
    spinRatio->setSuffix(" %");
    spinRatio->setReadOnly(true);
    spinRatio->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->statusbar->addPermanentWidget(spinRatio);

    labFile = new QLabel("File", this);
    labFile->setText("File");
    ui->statusbar->addWidget(labFile);
}

QtTree::~QtTree()
{
    delete ui;
}

void QtTree::on_actionAddDir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory();
    if (dir.isEmpty())
        return;
    QTreeWidgetItem* parentItem = ui->treeWidget->currentItem();
    if (parentItem == nullptr)
        return;
    if (parentItem->type() != FileItem) {
        QString dirName = dir.right(dir.length() - dir.lastIndexOf("/") - 1);
        QTreeWidgetItem* item = new QTreeWidgetItem(DirItem);
        QIcon icon("://icon_tree/dodeparent.svg");
        item->setIcon(ColItem, icon);
        item->setText(ColItem, dirName);
        item->setText(ColType, "Dir");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(ColItem, Qt::Checked);
        item->setData(ColItem, Qt::UserRole, QVariant(dir));
        parentItem->addChild(item);
    }
    parentItem->setExpanded(true);
}

void QtTree::on_actionAddFile_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Choose File", "", "File(*.svg)");
    if (files.isEmpty())
        return;
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    QTreeWidgetItem* parent;
    if (item == nullptr) {
        item = ui->treeWidget->topLevelItem(0);
    }
    parent = item->type() == FileItem ? item->parent() : item;

    QIcon icon("://icon_tree/jiedian_1.svg");
    for (int i = 0; i < files.length(); ++i) {
        QString file = files.at(i);
        QFileInfo fileInfo(file);
        QString text = fileInfo.fileName();
        QDateTime dateTime = fileInfo.lastModified();

        QTreeWidgetItem* item = new QTreeWidgetItem(FileItem);
        item->setIcon(ColItem, icon);
        item->setText(ColItem, text);
        item->setText(ColType, "File");
        item->setText(ColDate, dateTime.toString("yyyy-MM-dd"));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(ColItem, Qt::Checked);
        item->setData(ColItem, Qt::UserRole, QVariant(file));
        parent->addChild(item);
    }
    parent->setExpanded(true);
}

void QtTree::on_actionDelNode_triggered()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;
    QTreeWidgetItem* parent = item->parent();
    parent->removeChild(item);
}

void QtTree::on_treeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if (current == nullptr || current == previous)
        return;

    switch (current->type()) {
    case TopItem:
        ui->actionAddDir->setEnabled(true);
        ui->actionAddFile->setEnabled(true);
        ui->actionDelNode->setEnabled(false);
        break;
    case DirItem:
        ui->actionAddDir->setEnabled(true);
        ui->actionAddFile->setEnabled(true);
        ui->actionDelNode->setEnabled(true);
        break;
    case FileItem:
        ui->actionAddDir->setEnabled(false);
        ui->actionAddFile->setEnabled(false);
        ui->actionDelNode->setEnabled(true);
        displayImage(current);
        break;
    default:
        break;
    }
}

void QtTree::changeItemCaption(QTreeWidgetItem* item)
{
    QString text = "*" + item->text(ColItem);
    item->setText(ColItem, text);
    for (int i = 0; i < item->childCount(); ++i) {
        changeItemCaption(item->child(i));
    }
}

void QtTree::displayImage(QTreeWidgetItem* item)
{
    QString fname = item->data(ColItem, Qt::UserRole).toString();
    labFile->setText(fname);
    labNode->setText(item->text(ColItem));
    pixmap.load(fname);
    ui->actionFitWidth->triggered();

    ui->actionActual->setEnabled(true);
    ui->actionFitHeight->setEnabled(true);
    ui->actionFitWidth->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
}

void QtTree::on_actionLoopNode_triggered()
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        changeItemCaption(ui->treeWidget->topLevelItem(i));
    }
}

void QtTree::on_actionFitHeight_triggered()
{
    int height = ui->scrollArea->height();
    int realh = pixmap.height();
    zoomRatio = (float)height / realh;

    spinRatio->setValue(zoomRatio * 100);
    QPixmap pix = pixmap.scaledToHeight(height - 30);
    ui->labPic->setPixmap(pix);
}

void QtTree::on_actionFitWidth_triggered()
{
    int width = ui->scrollArea->width() - 30;
    int realw = pixmap.width();
    zoomRatio = (float)width / realw;

    spinRatio->setValue(zoomRatio * 100);
    QPixmap pix = pixmap.scaledToWidth(width - 30);
    ui->labPic->setPixmap(pix);
}

void QtTree::on_actionActual_triggered()
{
    ui->labPic->setPixmap(pixmap);
    zoomRatio = 1;
    spinRatio->setValue(100);
}

void QtTree::on_actionZoomIn_triggered()
{
    zoomRatio *= 1.2;
    int w = zoomRatio * pixmap.width();
    int h = zoomRatio * pixmap.height();
    ui->labPic->setPixmap(pixmap.scaled(w, h));
    spinRatio->setValue(zoomRatio * 100);
}

void QtTree::on_actionZoomOut_triggered()
{
    zoomRatio *= 0.8;
    int w = zoomRatio * pixmap.width();
    int h = zoomRatio * pixmap.height();
    ui->labPic->setPixmap(pixmap.scaled(w, h));
    spinRatio->setValue(zoomRatio * 100);
}

void QtTree::on_actionFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

void QtTree::on_actionShow_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}

void QtTree::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actionFloat->setChecked(topLevel);
}

void QtTree::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actionShow->setChecked(visible);
}
