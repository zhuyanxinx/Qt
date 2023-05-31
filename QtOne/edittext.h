
#ifndef EDITTEXT_H
#define EDITTEXT_H

#include <QDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class EditText; }
QT_END_NAMESPACE

class EditText : public QDialog

{
    Q_OBJECT

public:
    EditText(QWidget *parent = nullptr);
    ~EditText();

private slots:
    void on_pbtnClear_clicked();

    void on_chbUnderLine_clicked(bool checked);

    void on_chbItailc_clicked(bool checked);

    void on_chbBold_clicked(bool checked);

    void set_FontColor();

private:
    Ui::EditText *ui;
};

#endif // EDITTEXT_H
