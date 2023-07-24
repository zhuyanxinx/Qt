#ifndef MDIEDITOR_H
#define MDIEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MdiEditor;
}
QT_END_NAMESPACE

class MdiEditor : public QMainWindow {
    Q_OBJECT

public:
    MdiEditor(QWidget* parent = nullptr);
    ~MdiEditor();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionFont_triggered();

    void on_actionSave_triggered();

private:
    Ui::MdiEditor* ui;
};
#endif // MDIEDITOR_H
