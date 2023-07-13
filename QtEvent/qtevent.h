#ifndef QTEVENT_H
#define QTEVENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtEvent;
}
QT_END_NAMESPACE

class QtEvent : public QWidget {
    Q_OBJECT

public:
    QtEvent(QWidget* parent = nullptr);
    ~QtEvent();

private:
    Ui::QtEvent* ui;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void closeEvent(QCloseEvent* event) override;
};

#endif // QTEVENT_H
