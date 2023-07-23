#include "embedwidget.h"
#include "./ui_embedwidget.h"
#include "tdialog.h"
#include "tformdoc.h"
#include <QPainter>

EmbedWidget::EmbedWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::EmbedWidget)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
}

EmbedWidget::~EmbedWidget()
{
    delete ui;
}

void EmbedWidget::on_actionEmbedWidget_triggered()
{
    TFormDoc* formDoc = new TFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int idx = ui->tabWidget->addTab(formDoc, QString::asprintf("doc%d", ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(idx);
    ui->tabWidget->setVisible(true);
    connect(formDoc, &TFormDoc::titleChanged, this, &EmbedWidget::changeTabTitle);
}

void EmbedWidget::changeTabTitle(QString title)
{
    int idx = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(idx, title);
}

void EmbedWidget::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->close();
}

void EmbedWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int height = this->height() - ui->toolBar->height() - ui->statusbar->height();
    QPixmap pixmap(":/pic/icons/pic/binge.png");
    painter.drawPixmap(0, ui->toolBar->height(), this->width(), height, pixmap);
}

void EmbedWidget::on_actionWidget_triggered()
{
    TFormDoc* formDoc = new TFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("Qt Window");
    formDoc->setWindowOpacity(1);
    formDoc->show();
}

void EmbedWidget::on_actionEmbedMainWin_triggered()
{
    TDialog* formTable = new TDialog();
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int idx = ui->tabWidget->addTab(formTable, QString::asprintf("table%d", ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(idx);
    ui->tabWidget->setVisible(true);
}

void EmbedWidget::on_actionMainWindow_triggered()
{
    TDialog* formTable = new TDialog(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("Qt Window");
    formTable->setWindowOpacity(0.9);
    formTable->show();
}
