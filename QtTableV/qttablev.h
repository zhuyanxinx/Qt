#ifndef QTTABLEV_H
#define QTTABLEV_H

#include <QMainWindow>

class QLabel;
class QItemSelectionModel;
class QStandardItemModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class QtTableV;
}
QT_END_NAMESPACE

class QtTableV : public QMainWindow {
    Q_OBJECT
public:
    QtTableV(QWidget* parent = nullptr);
    ~QtTableV();

private slots:
    void onModelSelectCurrentChanged(const QModelIndex& current, const QModelIndex& previos);

    void on_actionOpenFile_triggered();

private:
    const int FixedColumnCount = 6;
    QLabel* labCurFile;
    QLabel* labCellPos;
    QLabel* labCellText;
    QStandardItemModel* modelStand;
    QItemSelectionModel* modelSelect;

    void initModelData(QStringList& lstContent);

private:
    Ui::QtTableV* ui;
};
#endif // QTTABLEV_H
