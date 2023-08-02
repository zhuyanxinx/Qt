#ifndef QTBINFILE_H
#define QTBINFILE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtBinFile;
}
QT_END_NAMESPACE

class QtBinFile : public QMainWindow {
    Q_OBJECT
private:
    QString fileName;
    template <class T>
    void writeByStream(T value);
    template <class T>
    void readByStream(T& value);

public:
    QtBinFile(QWidget* parent = nullptr);
    ~QtBinFile();

private slots:
    void on_btnBin_clicked();

    void on_btnFont_clicked();

    void on_btnColor_clicked();

    void on_btnQint8W_clicked();

    void on_btnQint8R_clicked();

    void on_btnQuint8W_clicked();

    void on_btnQuint8R_clicked();

    void on_btnQint16W_clicked();

    void on_btnQint16R_clicked();

    void on_btnQuint16W_clicked();

    void on_btnQuint16R_clicked();

    void on_btnQint32W_clicked();

    void on_btnQint32R_clicked();

    void on_btnQint64W_clicked();

    void on_btnQint64R_clicked();

    void on_btnBoolW_clicked();

    void on_btnBoolR_clicked();

    void on_btnDoubleW_clicked();

    void on_btnDoubleR_clicked();

    void on_btnFloat16W_clicked();

    void on_btnFloat16R_clicked();

    void on_btnFloatW_clicked();

    void on_btnFloatR_clicked();

    void on_btnCharW_clicked();

    void on_btnCharR_clicked();

    void on_btnQStringW_clicked();

    void on_btnQStringR_clicked();

    void on_btnFontW_clicked();

    void on_btnFontR_clicked();

    void on_btnColorW_clicked();

    void on_btnColorR_clicked();

    void on_actionClearAll_triggered();

    void on_actionWrite_triggered();

    void on_actionRead_triggered();

private:
    Ui::QtBinFile* ui;
};

#endif // QTBINFILE_H
