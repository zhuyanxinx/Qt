#ifndef QTFILESTREAM_H
#define QTFILESTREAM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtFileStream;
}
QT_END_NAMESPACE

class QtFileStream : public QMainWindow {
    Q_OBJECT

public:
    QtFileStream(QWidget* parent = nullptr);
    ~QtFileStream();

private:
    QString getFile(bool save = false);
private slots:
    void on_actionQFileOpen_triggered();

    void on_actionQFileSaveAs_triggered();

    void on_actionQSaveFile_triggered();

    void on_actionQTextStreamOpen_triggered();

    void on_actionQTextStreamSaveAs_triggered();

private:
    Ui::QtFileStream* ui;
};
#endif // QTFILESTREAM_H
