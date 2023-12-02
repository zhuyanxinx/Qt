#ifndef QTFILESYSTEM_H
#define QTFILESYSTEM_H

#include <QMainWindow>

class QFileSystemModel;
QT_BEGIN_NAMESPACE namespace Ui { class QtFileSystem; }
QT_END_NAMESPACE

class QtFileSystem : public QMainWindow {
    Q_OBJECT
private:
    QFileSystemModel* modelFile;

public:
    QtFileSystem(QWidget* parent = nullptr);
    ~QtFileSystem();

private slots:
    void on_actionSetRoot_triggered();

    void on_radioFileDir_clicked();

    void on_radioOnlyDir_clicked();

    void on_chkFile_clicked(bool checked);

    void on_btnApply_clicked();

    void on_treeView_clicked(const QModelIndex& index);

private:
    Ui::QtFileSystem* ui;
};
#endif // QTFILESYSTEM_H
