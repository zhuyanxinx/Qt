#ifndef EMBEDWIDGET_H
#define EMBEDWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EmbedWidget;
}
QT_END_NAMESPACE

class EmbedWidget : public QMainWindow {
    Q_OBJECT

public:
    EmbedWidget(QWidget* parent = nullptr);
    ~EmbedWidget();
private slots:
    void changeTabTitle(QString title);
private slots:
    void on_actionEmbedWidget_triggered();
    void on_tabWidget_tabCloseRequested(int index);

    void on_actionWidget_triggered();

    void on_actionEmbedMainWin_triggered();

    void on_actionMainWindow_triggered();

private:
    Ui::EmbedWidget* ui;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // EMBEDWIDGET_H
