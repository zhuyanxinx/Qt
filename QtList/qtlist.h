
#ifndef QTLIST_H
#define QTLIST_H

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtList;
}
QT_END_NAMESPACE

class QtList : public QMainWindow

{
    Q_OBJECT

public:
    QtList(QWidget* parent = nullptr);
    ~QtList();

private slots:
    void on_actionInitList_triggered();

    void on_actionInsertItem_triggered();

    void on_actionClearList_triggered();

    void on_actionAddItem_triggered();

    void on_actionDelItem_triggered();

    void on_actionSelectItem_triggered();

    void on_actionSelectAll_triggered();

    void on_actionSelectNone_triggered();

    void on_actionSelectInvs_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    void on_chkSort_clicked(bool checked);

    void on_tbtnSortAsc_clicked();

    void on_tbtnSortDes_clicked();

    void on_tbtnClearText_clicked();

    void on_tbtnAddLine_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint& pos);

private:
    Ui::QtList* ui;
};

#endif // QTLIST_H
