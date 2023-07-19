#ifndef TDIALOG_H
#define TDIALOG_H

#include <QMainWindow>
class TDialogHeader;
class QStandardItemModel;
class QItemSelectionModel;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class TDialog;
}
QT_END_NAMESPACE

class TDialog : public QMainWindow {
    Q_OBJECT

public:
    TDialog(QWidget* parent = nullptr);
    ~TDialog();

private:
    QLabel* labCellPos;
    QLabel* labCellText;
    QStandardItemModel* model;
    QItemSelectionModel* selmodel;
    TDialogHeader* dlgHeader = nullptr;
private slots:
    void on_actionSetSize_triggered();

    void on_actionSetHeader_triggered();

    void on_actionLocate_triggered();

    void on_tableView_clicked(const QModelIndex& index);
private slots:
    void setCellText(int row, int col, QString& text);
    void modelSelectChanged(const QModelIndex& current, const QModelIndex& previous);
signals:
    void cellSelectChanged(int row, int col);

private:
    Ui::TDialog* ui;
};
#endif // TDIALOG_H
