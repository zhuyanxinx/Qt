#include "qtstddialog.h"
#include "./ui_qtstddialog.h"

#include <QColorDialog>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QProgressDialog>

QtStdDialog::QtStdDialog(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtStdDialog)
{
    ui->setupUi(this);
}

QtStdDialog::~QtStdDialog()
{
    delete ui;
}

void QtStdDialog::on_btnOpenFile_clicked()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString fname = QFileDialog::getOpenFileName(this,
        "选择文件", appPath, "文本文件(*.txt);;所有文件(*.*)");
    if (!fname.isEmpty()) {
        ui->plainTextEdit->appendPlainText(fname);
    }
}

void QtStdDialog::on_btnOpenFileMuti_clicked()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QStringList fnames = QFileDialog::getOpenFileNames(this,
        "选择多个文件", appPath, "文本文件(*.txt);;所有文件(*.*)");

    for (auto& fname : fnames) {
        ui->plainTextEdit->appendPlainText(fname);
    }
}

void QtStdDialog::on_btnSelectDir_clicked()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString selDir = QFileDialog::getExistingDirectory(this, "选择目录", appPath);
    if (!selDir.isEmpty()) {
        ui->plainTextEdit->appendPlainText(selDir);
    }
}

void QtStdDialog::on_btnSaveFile_clicked()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString fname = QFileDialog::getSaveFileName(this,
        "保存文件", appPath, "文本文件(*.txt);;所有文件(*.*)");
    if (!fname.isEmpty()) {
        ui->plainTextEdit->appendPlainText(fname);
    }
}

void QtStdDialog::on_btnSelectColor_clicked()
{
    QPalette plet = ui->plainTextEdit->palette();
    QColor iniColor = plet.color(QPalette::Text);
    QColor color = QColorDialog::getColor(iniColor, this, "Select Color");
    if (color.isValid()) {
        plet.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(plet);
    }
}

void QtStdDialog::on_btnSelectFont_clicked()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, iniFont);
    if (ok) {
        ui->plainTextEdit->setFont(font);
    }
}

void QtStdDialog::on_btnProgress_clicked()
{
    QProgressDialog progress("runing...", "Cancel", 0, 100, this);
    progress.setWindowTitle("Runing...");
    progress.setWindowModality(Qt::WindowModal);

    connect(&progress, &QProgressDialog::canceled, [&] { ui->plainTextEdit->appendPlainText("Canceled"); });

    QElapsedTimer timer;
    for (int i = 0; i < 100; ++i) {
        progress.setValue(i);
        progress.setLabelText(QString::asprintf("Run:%d", i));
        timer.start();
        while (true) {
            if (timer.elapsed() > 50) {
                break;
            }
        }
        if (progress.wasCanceled()) {
            break;
        }
        ui->plainTextEdit->appendPlainText(QString::asprintf("Run:%d", i));
    }
}
#include <QInputDialog>
void QtStdDialog::on_btnInputStr_clicked()
{
    QString title = "InputDialog";
    QString label = "Input char";
    QString iniInput = "input char";
    QLineEdit::EchoMode mode = QLineEdit::Normal;
    bool ok = false;
    QString text = QInputDialog::getText(this, title, label, mode, iniInput, &ok);
    if (ok && !text.isEmpty()) {
        ui->plainTextEdit->appendPlainText(text);
    }
}

void QtStdDialog::on_btnInputInt_clicked()
{
    QString title = "InputDialog";
    QString label = "Input int";
    int value = 0;
    int minv = 0;
    int maxv = 127;
    int step = 1;
    bool ok = false;
    value = QInputDialog::getInt(this, title, label, value, minv, maxv, step, &ok);
    if (ok) {
        ui->plainTextEdit->appendPlainText(QString::asprintf("%d", value));
    }
}

void QtStdDialog::on_btnFloat_clicked()
{
    QString title = "InputDialog";
    QString label = "Input float";
    float value = 0.00;
    int minv = 0;
    int maxv = 256;
    int decimals = 2;
    bool ok = false;
    value = QInputDialog::getDouble(this, title, label, value, minv, maxv, decimals, &ok);
    if (ok) {
        ui->plainTextEdit->appendPlainText(QString::asprintf("%.2f", value));
    }
}

void QtStdDialog::on_btnInputSelItem_clicked()
{
    QString title = "InputDialog";
    QString label = "Select item";
    QStringList items;
    items << "A"
          << "B"
          << "C"
          << "D";
    int current = 0;
    bool editable = true;
    bool ok = false;
    QString item = QInputDialog::getItem(this, title, label, items, current, editable, &ok);
    if (ok && !item.isEmpty()) {
        ui->plainTextEdit->appendPlainText(item);
    }
}

void QtStdDialog::on_btnQuestion_clicked()
{
    QString title = "MessageBox";
    QString label = "Are you sure?";
    int result = QMessageBox::question(this, title, label, QMessageBox::Yes | QMessageBox::No, QMessageBox::NoButton);
    ui->plainTextEdit->appendPlainText(QString::asprintf("result:%d", result));
}

void QtStdDialog::on_btnInfo_clicked()
{
    QMessageBox::information(this, "Info", "ifyou");
}

void QtStdDialog::on_btnWarning_clicked()
{
    QMessageBox::warning(this, "Warning", "has a warning");
}

void QtStdDialog::on_btnCritical_clicked()
{
    QMessageBox::critical(this, "Critical", "Critical info");
}

void QtStdDialog::on_btnAbout_clicked()
{
    QMessageBox::about(this, "About", "about xyz, how many you know ?");
}

void QtStdDialog::on_btnAboutQt_clicked()
{
    QMessageBox::aboutQt(this, "AboutQt");
}
