
#ifndef THREE_H
#define THREE_H
#include <QDialog>

class QCheckBox;
class QRadioButton;
class QPlainTextEdit;
class QPushButton;

class Three : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;

    QRadioButton *radioBlack;
    QRadioButton *radioBlue;
    QRadioButton *radioRed;

    QPlainTextEdit *txtEdit;

    QPushButton *btnClear;
    QPushButton *btnOK;
    QPushButton *btnClose;
private slots:
    void setFontUnder(bool checked);
    void setFontItalic(bool checked);
    void setFontBold(bool checked);

    void setFontColor();
    void clearText();

public:
    Three(QWidget *parent = nullptr);
    ~Three();
};

#endif // THREE_H
