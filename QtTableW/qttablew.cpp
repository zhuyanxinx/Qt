#include "qttablew.h"
#include "./ui_qttablew.h"

#include <QDate>
#include <QLabel>
#include <QRandomGenerator>

QtTableW::QtTableW(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtTableW)
{
    ui->setupUi(this);
    labCellIdx = new QLabel("Cell", this);
    labCellIdx->setMinimumWidth(200);
    labCellType = new QLabel("Type", this);
    labCellType->setMinimumWidth(200);
    labStudentId = new QLabel("Id", this);
    labStudentId->setMinimumWidth(200);

    ui->statusbar->addWidget(labCellIdx);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudentId);
}

QtTableW::~QtTableW()
{
    delete ui;
}

void QtTableW::createRowItems(int rowIdx, QString name, QString sex, QDate birth, QString han, int score, bool isStudent)
{
    uint studentId = 20221000;
    QTableWidgetItem* itemName = new QTableWidgetItem(name, CtName);
    itemName->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studentId += rowIdx;
    itemName->setData(Qt::UserRole, QVariant(studentId));
    ui->tableWidget->setItem(rowIdx, ColName, itemName);

    QTableWidgetItem* itemSex = new QTableWidgetItem(sex, CtSex);
    QIcon iconSex(sex == "男" ? "://icon_person/nanhai.svg" : ":/icon_person/nvhai.svg");
    itemSex->setIcon(iconSex);
    itemSex->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    itemSex->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowIdx, ColSex, itemSex);

    QTableWidgetItem* itemBirth = new QTableWidgetItem(birth.toString("yyyy-MM-dd"), CtBirth);
    itemBirth->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowIdx, ColBirth, itemBirth);

    QTableWidgetItem* itemHan = new QTableWidgetItem(han, CtHan);
    itemHan->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowIdx, ColHan, itemHan);

    QTableWidgetItem* itemScore = new QTableWidgetItem(QString::number(score), CtScore);
    itemScore->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowIdx, ColScore, itemScore);

    QTableWidgetItem* itemStudent = new QTableWidgetItem(isStudent ? "少先队员" : "大队长", CtStudent);
    itemSex->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
    itemStudent->setCheckState(isStudent ? Qt::Checked : Qt::Unchecked);
    itemStudent->setBackground(QBrush(Qt::yellow));
    itemStudent->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowIdx, ColStudent, itemStudent);
}

void QtTableW::on_btnHheader_clicked()
{
    QStringList headerText;
    headerText << "姓名"
               << "性别"
               << "出生日期"
               << "民族"
               << "分数"
               << "是否少先队员";
    ui->tableWidget->setColumnCount(headerText.size());
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(headerText.at(i));
        QFont font = item->font();
        font.setBold(true);
        font.setPointSize(11);
        item->setFont(font);
        item->setForeground(QBrush(Qt::black));
        ui->tableWidget->setHorizontalHeaderItem(i, item);
    }
}

void QtTableW::on_btnSetRowCount_clicked()
{
    ui->tableWidget->setRowCount(ui->spinRowCount->value());
}

void QtTableW::on_btnInitData_clicked()
{
    ui->tableWidget->clear();
    QDate birth(2000, 2, 2);
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QString name = QString("学生%1").arg(i);
        QString sex = (i % 2) ? "男" : "女";
        bool isStudent = (i % 3) ? true : false;
        int score = QRandomGenerator::global()->bounded(88, 100);
        createRowItems(i, name, sex, birth, "漢", score, isStudent);
        birth = birth.addDays(27);
    }
}

void QtTableW::on_btnInsertRow_clicked()
{
    int rowIdx = ui->tableWidget->currentRow();
    qDebug("rowIdx:" + rowIdx);
    ui->tableWidget->insertRow(rowIdx);
    createRowItems(rowIdx, "新生", "男", QDate::fromString("2002-2-21", "yyyy-M-d"), "汉", 98, true);
}

void QtTableW::on_btnAddRow_clicked()
{
    int rowIdx = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowIdx);
    createRowItems(rowIdx, "新生", "女", QDate::fromString("2007-8-21", "yyyy-M-d"), "汉", 92, false);
}

void QtTableW::on_btnDeleteRow_clicked()
{
    int rowIdx = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(rowIdx);
}

void QtTableW::on_btnAutoHeight_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}

void QtTableW::on_btnAutoWidth_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}

void QtTableW::on_btnReadData_clicked()
{
    ui->plainTextEdit->clear();
    QTableWidgetItem* item;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QString sb;
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            item = ui->tableWidget->item(i, j);
            sb.append(item->text() + " ");
        }
        ui->plainTextEdit->appendPlainText(QString::number(i) + " " + sb);
    }
}

void QtTableW::on_chkEditable_clicked(bool checked)
{
    int trigger = checked ? (QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked) : QAbstractItemView::NoEditTriggers;
    ui->tableWidget->setEditTriggers(QAbstractItemView::EditTriggers::fromInt(trigger));
}

void QtTableW::on_chkBgColor_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}

void QtTableW::on_chkHheader_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void QtTableW::on_chkVHeader_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}

void QtTableW::on_radioSelRow_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void QtTableW::on_radioSelCell_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void QtTableW::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    QTableWidgetItem* item = ui->tableWidget->item(currentRow, currentColumn);
    if (item == nullptr)
        return;

    labCellIdx->setText(QString::asprintf("Cell (%d, %d)", currentRow, currentColumn));
    labCellType->setText(QString::asprintf("Type %d", item->type()));
    labStudentId->setText(QString::asprintf("Student %d", item->data(Qt::UserRole).toUInt()));
}
