#ifndef QTSTDDIALOG_H
#define QTSTDDIALOG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtStdDialog;
}
QT_END_NAMESPACE

class QtStdDialog : public QWidget {
    Q_OBJECT

public:
    QtStdDialog(QWidget* parent = nullptr);
    ~QtStdDialog();

private slots:
    void on_btnOpenFile_clicked();

    void on_btnOpenFileMuti_clicked();

    void on_btnSelectDir_clicked();

    void on_btnSaveFile_clicked();

    void on_btnSelectColor_clicked();

    void on_btnSelectFont_clicked();

    void on_btnProgress_clicked();

    void on_btnInputStr_clicked();

    void on_btnInputInt_clicked();

    void on_btnFloat_clicked();

    void on_btnInputSelItem_clicked();

    void on_btnQuestion_clicked();

    void on_btnInfo_clicked();

    void on_btnWarning_clicked();

    void on_btnCritical_clicked();

    void on_btnAbout_clicked();

    void on_btnAboutQt_clicked();

private:
    Ui::QtStdDialog* ui;
};
#endif // QTSTDDIALOG_H
