
#ifndef QTMETAINFO_H
#define QTMETAINFO_H

#include <QWidget>
class TPerson;


QT_BEGIN_NAMESPACE
namespace Ui { class QtMetaInfo; }
QT_END_NAMESPACE

class QtMetaInfo : public QWidget

{
    Q_OBJECT

public:
    QtMetaInfo(QWidget *parent = nullptr);
    ~QtMetaInfo();
private:
    TPerson *boy;
    TPerson *girl;
private slots:
    void ageChanged(int value);

    void spinChanged(int value);

    void on_btnBoyInc_clicked();

    void on_btnGirlInc_clicked();

    void on_btnClear_clicked();

    void on_btnQtMeta_clicked();

private:
    Ui::QtMetaInfo *ui;
};

#endif // QTMETAINFO_H
