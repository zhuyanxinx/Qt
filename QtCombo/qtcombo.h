#ifndef QTCOMBO_H
#define QTCOMBO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QtCombo; }
QT_END_NAMESPACE

class QtCombo : public QWidget
{
    Q_OBJECT

public:
    QtCombo(QWidget *parent = nullptr);
    ~QtCombo();

private slots:
    void on_btnClear_clicked();

    void on_btnInitCity_clicked();

    void on_btnCityEditable_clicked(bool checked);

    void on_btnClearCity_clicked();

    void on_btnInitCityNum_clicked();

    void on_comboCity_currentTextChanged(const QString &arg1);

    void on_comboCItyNum_currentIndexChanged(int index);

private:
    Ui::QtCombo *ui;
};
#endif // QTCOMBO_H
