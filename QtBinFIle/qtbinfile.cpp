#include "qtbinfile.h"
#include "ui_qtbinfile.h"
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>

QtBinFile::QtBinFile(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QtBinFile)
{
    ui->setupUi(this);
    ui->actionRead->setEnabled(false);
    ui->actionWrite->setEnabled(false);
    ui->groupOut->setEnabled(false);
}

QtBinFile::~QtBinFile()
{
    delete ui;
}

template <class T>
void QtBinFile::writeByStream(T value)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_5);
    if (ui->radioBig->isChecked()) {
        stream.setByteOrder(QDataStream::BigEndian);
    } else {
        stream.setByteOrder(QDataStream::LittleEndian);
    }
    if (ui->radioSingle->isChecked()) {
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    } else {
        stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    }
    stream << value;
    file.close();
}

template <class T>
void QtBinFile::readByStream(T& value)
{
    if (!QFile::exists(fileName)) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_5);
    if (ui->radioBig->isChecked()) {
        stream.setByteOrder(QDataStream::BigEndian);
    } else {
        stream.setByteOrder(QDataStream::LittleEndian);
    }
    if (ui->radioSingle->isChecked()) {
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    } else {
        stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    }
    stream >> value;
    file.close();
}

void QtBinFile::on_btnBin_clicked()
{
    QString title = "Select file";
    QString filter = "Stream(*.stream);;All file(*.*)";
    QString path = QApplication::applicationDirPath();
    fileName = QFileDialog::getSaveFileName(this, title, path, filter);
    if (fileName.isEmpty()) {
        return;
    }
    ui->txtBin->setText(fileName);
    ui->actionRead->setEnabled(true);
    ui->actionWrite->setEnabled(true);
    ui->groupOut->setEnabled(true);
}

void QtBinFile::on_btnFont_clicked()
{
    QFont font = ui->btnFont->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font, this);
    if (ok) {
        ui->btnFont->setFont(font);
    }
}

void QtBinFile::on_btnColor_clicked()
{
    QPalette plet = ui->btnColor->palette();
    QColor color = plet.buttonText().color();
    color = QColorDialog::getColor(color);
    if (color.isValid()) {
        plet.setColor(QPalette::ButtonText, color);
        ui->btnColor->setPalette(plet);
    }
}

void QtBinFile::on_btnQint8W_clicked()
{
    qint8 value = ui->spinQint8->value();
    writeByStream(value);
}

void QtBinFile::on_btnQint8R_clicked()
{
    qint8 value = 0;
    readByStream(value);
    ui->txtQint8->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnQuint8W_clicked()
{
    quint8 value = ui->spinQuint8->value();
    writeByStream(value);
}

void QtBinFile::on_btnQuint8R_clicked()
{
    quint8 value = 0;
    readByStream(value);
    ui->txtQuint8->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnQint16W_clicked()
{
    qint16 value = ui->spinQint16->value();
    writeByStream(value);
}

void QtBinFile::on_btnQint16R_clicked()
{
    qint16 value = 0;
    readByStream(value);
    ui->txtQint16->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnQuint16W_clicked()
{
    quint16 value = ui->spinQuint16->value();
    writeByStream(value);
}

void QtBinFile::on_btnQuint16R_clicked()
{
    quint16 value = 0;
    readByStream(value);
    ui->txtQuint16->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnQint32W_clicked()
{
    qint32 value = ui->spinQint32->value();
    writeByStream(value);
}

void QtBinFile::on_btnQint32R_clicked()
{
    qint32 value = 0;
    readByStream(value);
    ui->txtQint32->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnQint64W_clicked()
{
    qint64 value = ui->spinQint64->value();
    writeByStream(value);
}

void QtBinFile::on_btnQint64R_clicked()
{
    qint64 value = 0;
    readByStream(value);
    ui->txtQint64->setText(QString("%1").arg(value));
}

void QtBinFile::on_btnBoolW_clicked()
{
    bool value = ui->chkBool->isChecked();
    writeByStream(value);
}

void QtBinFile::on_btnBoolR_clicked()
{
    bool value = false;
    readByStream(value);
    ui->chkRbool->setChecked(value);
}

void QtBinFile::on_btnDoubleW_clicked()
{
    double value = ui->dbspinDouble->value();
    writeByStream(value);
}

void QtBinFile::on_btnDoubleR_clicked()
{
    double value = 0.0;
    readByStream(value);
    ui->txtDouble->setText(QString::asprintf("%.4f", value));
}

void QtBinFile::on_btnFloat16W_clicked()
{
    qfloat16 value = ui->dbspinFloat16->value();
    writeByStream(value);
}

void QtBinFile::on_btnFloat16R_clicked()
{
    qfloat16 value = 0.0;
    readByStream(value);
    QString res;
    QTextStream(&res) << value;
    ui->txtFloat16->setText(res);
}

void QtBinFile::on_btnFloatW_clicked()
{
    float value = ui->dbspinFloat->value();
    writeByStream(value);
}

void QtBinFile::on_btnFloatR_clicked()
{
    float value = 0.0;
    readByStream(value);
    ui->txtFloat->setText(QString::asprintf("%.4f", value));
}

void QtBinFile::on_btnCharW_clicked()
{
    QString value = ui->txtChar->text();
    char* chav = value.toLocal8Bit().data();
    writeByStream(chav);
}

void QtBinFile::on_btnCharR_clicked()
{
    char* value = 0;
    readByStream(value);
    QString val(value);
    ui->txtCharR->setText(val);
}

void QtBinFile::on_btnQStringW_clicked()
{
    QString value = ui->txtQString->text();
    writeByStream(value);
}

void QtBinFile::on_btnQStringR_clicked()
{
    QString value;
    readByStream(value);
    ui->txtQStringR->setText(value);
}

void QtBinFile::on_btnFontW_clicked()
{
    QFont font = ui->btnFont->font();
    writeByStream(font);
}

void QtBinFile::on_btnFontR_clicked()
{
    QFont font;
    readByStream(font);
    ui->txtFont->setFont(font);
}

void QtBinFile::on_btnColorW_clicked()
{
    QPalette plet = ui->btnColor->palette();
    QColor color = plet.buttonText().color();
    writeByStream(color);
}

void QtBinFile::on_btnColorR_clicked()
{
    QColor color;
    readByStream(color);
    QPalette plet = ui->txtColor->palette();
    plet.setColor(QPalette::Text, color);
    ui->txtColor->setPalette(plet);
}

void QtBinFile::on_actionClearAll_triggered()
{
    ui->txtChar->clear();
    //...
}

void QtBinFile::on_actionWrite_triggered()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_5);
    if (ui->radioBig->isChecked()) {
        stream.setByteOrder(QDataStream::BigEndian);
    } else {
        stream.setByteOrder(QDataStream::LittleEndian);
    }
    if (ui->radioSingle->isChecked()) {
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    } else {
        stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    }
    qint8 vint8 = ui->spinQint8->value();
    stream << vint8;

    QString vqstr = ui->txtQString->text();
    stream << vqstr;
    file.close();
}

void QtBinFile::on_actionRead_triggered()
{
    if (!QFile::exists(fileName)) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_5);
    if (ui->radioBig->isChecked()) {
        stream.setByteOrder(QDataStream::BigEndian);
    } else {
        stream.setByteOrder(QDataStream::LittleEndian);
    }
    if (ui->radioSingle->isChecked()) {
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    } else {
        stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    }

    stream.startTransaction();

    qint8 vint8 = 0;
    stream >> vint8;
    ui->txtQint8->setText(QString("%1").arg(vint8));

    QString vqstr;
    stream >> vqstr;
    ui->txtQStringR->setText(vqstr);

    if (stream.commitTransaction()) {
        QMessageBox::information(this, "Success", "read success!");
    } else {
        QMessageBox::critical(this, "Critical", "read has error!");
    }
    file.close();
}
