#ifndef TLOGINDIALOG_H
#define TLOGINDIALOG_H

#include <QDialog>

namespace Ui {
class TLoginDialog;
}

class TLoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit TLoginDialog(QWidget* parent = nullptr);
    ~TLoginDialog();

private:
    Ui::TLoginDialog* ui;

private:
    bool mmoving = false;
    QPoint mlastPos;
    QString muser;
    QString mpswd;
    bool msaved = false;
    int mTryCount = 0;
    const int MAXCOUNT = 3;

    QString encrypt(const QString& pwd);
    void readSetting();
    void writeSetting();
    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
private slots:
    void on_btnOk_clicked();
};

#endif // TLOGINDIALOG_H
