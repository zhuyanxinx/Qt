#ifndef TDIALOGHEADER_H
#define TDIALOGHEADER_H

#include <QDialog>

class QStringListModel;

namespace Ui {
class TDialogHeader;
}

class TDialogHeader : public QDialog {
    Q_OBJECT

public:
    explicit TDialogHeader(QWidget* parent = nullptr);
    ~TDialogHeader();

private:
    QStringListModel* model;

public:
    void setHealderList(QStringList& list);
    QStringList headerList();

private:
    Ui::TDialogHeader* ui;
};

#endif // TDIALOGHEADER_H
