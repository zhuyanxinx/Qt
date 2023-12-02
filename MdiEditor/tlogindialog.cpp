#include "tlogindialog.h"
#include "ui_tlogindialog.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QMouseEvent>
#include <QSettings>

TLoginDialog::TLoginDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TLoginDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    //    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::SplashScreen);

    QApplication::setApplicationName("mdieditor");
    QApplication::setOrganizationName("XYZ-QT");
    readSetting();
}

TLoginDialog::~TLoginDialog()
{
    delete ui;
}

QString TLoginDialog::encrypt(const QString& pwd)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(pwd.toLocal8Bit());
    return hash.result();
}

void TLoginDialog::readSetting()
{
    QSettings settings;
    msaved = settings.value("saved", false).toBool();
    muser = settings.value("user", "user").toString();
    mpswd = settings.value("pswd", encrypt("12345")).toString();
    //    mpswd = encrypt("12345");
    if (msaved) {
        ui->lineEditUser->setText(muser);
        ui->lineEditPwd->setText("12345");
        ui->chkSaved->setChecked(true);
    }
}

void TLoginDialog::writeSetting()
{
    QSettings settings;
    settings.setValue("user", muser);
    settings.setValue("pswd", mpswd);
    settings.setValue("saved", ui->chkSaved->isChecked());
}

void TLoginDialog::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mmoving = true;
        mlastPos = event->globalPosition().toPoint() - this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void TLoginDialog::mouseReleaseEvent(QMouseEvent* event)
{
    mmoving = false;
    event->accept();
}

void TLoginDialog::mouseMoveEvent(QMouseEvent* event)
{
    QPoint eventPos = event->globalPosition().toPoint();
    bool drag = (eventPos - mlastPos - this->pos()).manhattanLength() > QApplication::startDragDistance();
    if (mmoving && drag) {
        move(eventPos - mlastPos);
        mlastPos = eventPos - this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void TLoginDialog::on_btnOk_clicked()
{
    QString user = ui->lineEditUser->text().trimmed();
    QString pwd = ui->lineEditPwd->text().trimmed();
    QString epwd = encrypt(pwd);
    if (user == muser && epwd == mpswd) {
        writeSetting();
        this->accept();
    } else {
        mTryCount++;
        if (mTryCount >= MAXCOUNT) {
            QMessageBox::critical(this, "Error", "Input error 3 times");
            this->reject();
        } else {
            QMessageBox::warning(this, "Warning", "Wrong user or password");
        }
    }
}
