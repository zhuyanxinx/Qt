#ifndef QFILEDOC_H
#define QFILEDOC_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class QFileDoc; }
QT_END_NAMESPACE

class QFileDoc : public QDialog
{
    Q_OBJECT

public:
    QFileDoc(QWidget *parent = nullptr);
    ~QFileDoc();

private:
    Ui::QFileDoc *ui;
};
#endif // QFILEDOC_H
