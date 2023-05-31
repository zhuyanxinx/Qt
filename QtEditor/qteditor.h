
#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QFontComboBox;
class QSpinBox;
class QToolButton;
class QProgressBar;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class QtEditor;
}
QT_END_NAMESPACE

class QtEditor : public QMainWindow {
    Q_OBJECT

public:
    QtEditor(QWidget* parent = nullptr);
    ~QtEditor();
private:
    QFontComboBox* comboFont;
    QSpinBox* spinFontSize;
    QToolButton* langZhEn;
    QLabel* labStatus;
    QLabel* labInfo;
    QProgressBar* progress;
private slots:
    void onSpinFontSizeChanged(int fontSize);

    void onComboFontChanged(const QFont& font);

    void on_actionNewFile_triggered();

    void on_actionEdit_triggered();

    void on_actionSave_triggered();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void on_actionBold_triggered(bool checked);

    void on_actionItalic_triggered(bool checked);

    void on_actionUnderline_toggled(bool checked);

    void on_actionQuit_triggered();

    void on_actionZhEn_triggered(bool checked);

private:
    Ui::QtEditor* ui;
};

#endif // QTEDITOR_H
