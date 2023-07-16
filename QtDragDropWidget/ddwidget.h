#ifndef DDWIDGET_H
#define DDWIDGET_H

#include <QAbstractItemView>
#include <QMainWindow>

class QGroupBox;

QT_BEGIN_NAMESPACE
namespace Ui {
class DDWidget;
}
QT_END_NAMESPACE

class DDWidget : public QMainWindow {
    Q_OBJECT
private:
    QAbstractItemView* itemView = nullptr;
    void refreshUI(QGroupBox* group);

    int actionIndex(Qt::DropAction action);
    Qt::DropAction actionType(int index);

public:
    DDWidget(QWidget* parent = nullptr);
    ~DDWidget();

private slots:
    void on_radioSrc_clicked();

    void on_radioList_clicked();

    void on_radioTree_clicked();

    void on_radioTable_clicked();

    void on_chkAcceptDrop_clicked(bool checked);

    void on_chkDragEnable_clicked(bool checked);

    void on_comboMode_currentIndexChanged(int index);

    void on_comboAction_currentIndexChanged(int index);

private:
    void setWidgetAttr(QAbstractItemView* widget, bool acceptDrop, bool dragEnable, Qt::DropAction action, QAbstractItemView::DragDropMode mode);

private:
    Ui::DDWidget* ui;

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // DDWIDGET_H
