#ifndef QTCUSTEVENT_H
#define QTCUSTEVENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtCustEvent;
}
QT_END_NAMESPACE

class QtCustEvent : public QWidget {
    Q_OBJECT

public:
    QtCustEvent(QWidget* parent = nullptr);
    ~QtCustEvent();
private slots:
    void doubleClick();

private:
    Ui::QtCustEvent* ui;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // QTCUSTEVENT_H
