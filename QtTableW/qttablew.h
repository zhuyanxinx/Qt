#ifndef QTTABLEW_H
#define QTTABLEW_H

#include <QMainWindow>
class QLabel;
QT_BEGIN_NAMESPACE
namespace Ui {
class QtTableW;
}
QT_END_NAMESPACE

class QtTableW : public QMainWindow {
    Q_OBJECT
    enum ColField {
        ColName = 0,
        ColSex,
        ColBirth,
        ColHan,
        ColScore,
        ColStudent
    };
    enum CellType {
        CtName = 1000,
        CtSex,
        CtBirth,
        CtHan,
        CtScore,
        CtStudent
    };

public:
    QtTableW(QWidget* parent = nullptr);
    ~QtTableW();

private:
    void createRowItems(int rowIdx, QString name, QString sex, QDate birth, QString han, int score, bool isStudent);
private slots:
    void on_btnHheader_clicked();

    void on_btnSetRowCount_clicked();

    void on_btnInitData_clicked();

    void on_btnInsertRow_clicked();

    void on_btnAddRow_clicked();

    void on_btnDeleteRow_clicked();

    void on_btnAutoHeight_clicked();

    void on_btnAutoWidth_clicked();

    void on_btnReadData_clicked();

    void on_chkEditable_clicked(bool checked);

    void on_chkBgColor_clicked(bool checked);

    void on_chkHheader_clicked(bool checked);

    void on_chkVHeader_clicked(bool checked);

    void on_radioSelRow_clicked();

    void on_radioSelCell_clicked();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::QtTableW* ui;
    QLabel* labCellIdx;
    QLabel* labCellType;
    QLabel* labStudentId;
};
#endif // QTTABLEW_H
