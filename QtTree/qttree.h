#ifndef QTTREE_H
#define QTTREE_H

#include <QMainWindow>

class QLabel;
class QSpinBox;
class QTreeWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui {
class QtTree;
}
QT_END_NAMESPACE

class QtTree : public QMainWindow {
    Q_OBJECT

public:
    QtTree(QWidget* parent = nullptr);
    ~QtTree();

private:
    Ui::QtTree* ui;

private:
    enum TreeCol {
        ColItem = 0,
        ColType,
        ColDate
    };
    enum NodeType {
        TopItem = 1001,
        DirItem,
        FileItem
    };
    QLabel* labNode;
    QLabel* labFile;
    QSpinBox* spinRatio;
    QPixmap pixmap;
    float zoomRatio;

    void changeItemCaption(QTreeWidgetItem* item);
    void displayImage(QTreeWidgetItem* item);

private slots:
    void on_actionAddDir_triggered();

    void on_actionAddFile_triggered();

    void on_actionDelNode_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);

    void on_actionLoopNode_triggered();
    void on_actionFitHeight_triggered();
    void on_actionFitWidth_triggered();
    void on_actionActual_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionFloat_triggered(bool checked);
    void on_actionShow_triggered(bool checked);
    void on_dockWidget_topLevelChanged(bool topLevel);
    void on_dockWidget_visibilityChanged(bool visible);
};
#endif // QTTREE_H
