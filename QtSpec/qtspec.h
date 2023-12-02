#ifndef QTSPEC_H
#define QTSPEC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtSpec; }
QT_END_NAMESPACE

class QtSpec : public QMainWindow
{
    Q_OBJECT

public:
    QtSpec(QWidget *parent = nullptr);
    ~QtSpec();

private slots:
    void on_btnStr_clicked();

    void on_btnClear_clicked();

    void on_btnChar_clicked();

    void on_btnLati_clicked();

    void on_btnUtf16_clicked();

    void on_btnQChar_clicked();

private:
    Ui::QtSpec *ui;
};
#endif // QTSPEC_H
