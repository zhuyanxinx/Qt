#include "qtspec.h"
#include "./ui_qtspec.h"

QtSpec::QtSpec(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSpec)
{
    ui->setupUi(this);
}

QtSpec::~QtSpec()
{
    delete ui;
}

void QtSpec::on_btnStr_clicked()
{
    QString val = ui->editStr->text();
    if (val.isEmpty()) {
        return;
    }
    for (int var = 0; var < val.size(); ++var) {
        QChar ch = val.at(var);
        char16_t unicode  =  ch.unicode();
        QString chStr(ch);
        QString info = chStr + QString::asprintf("\t, Unicode:0x%X", unicode);
        ui->txtShow->appendPlainText(info);
    }
}

void QtSpec::on_btnClear_clicked()
{
     ui->txtShow->clear();
}

void QtSpec::on_btnChar_clicked()
{
    QString val = ui->editChar->text();
    if (val.isEmpty()) {
        return;
    }
    QChar ch = val.at(0);
    char16_t unicode  =  ch.unicode();
    QString info = val + QString::asprintf("\t, Unicode:0x%X", unicode);
    ui->txtShow->appendPlainText(info);

    ui->chkDigit->setChecked(ch.isDigit());
    ui->chkLetter->setChecked(ch.isLetter());
    ui->chkUpper->setChecked(ch.isUpper());
    ui->chkLower->setChecked(ch.isLower());
    ui->chkLetOrNum->setChecked(ch.isLetterOrNumber());
    ui->chkSymbol->setChecked(ch.isSymbol());
    ui->chkMark->setChecked(ch.isMark());
    ui->chkSpace->setChecked(ch.isSpace());
    ui->chkPunct->setChecked(ch.isPunct());
}

void QtSpec::on_btnLati_clicked()
{
    QString val = ui->editChar->text();
    if (val.isEmpty()) {
        return;
    }
    QChar ch = QChar::fromLatin1('P');
    val[0] = ch;
    ui->txtShow->appendPlainText(val);
}

void QtSpec::on_btnUtf16_clicked()
{
    QString val = ui->editChar->text();
    if (val.isEmpty()) {
        return;
    }
    QString zh = "中文";
    val[0] = zh.at(0);
    ui->txtShow->appendPlainText(val);
}

void QtSpec::on_btnQChar_clicked()
{
    QString src = "湖，河";
    QString val = "湖北，湖北";
    QChar hu = QChar::fromUcs2(src.at(0).unicode());
    QChar he = QChar(src.at(2).unicode());

    ui->txtShow->appendPlainText(val);

    for (int i = 0; i < val.size(); ++i) {
        if (val[i] == hu) {
            val[i] = he;
        }
    }
    ui->txtShow->appendPlainText(val);
}
