#ifndef QTDRAGEVENT_H
#define QTDRAGEVENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtDragEvent;
}
QT_END_NAMESPACE

class QtDragEvent : public QWidget {
    Q_OBJECT

public:
    QtDragEvent(QWidget* parent = nullptr);
    ~QtDragEvent();

private:
    Ui::QtDragEvent* ui;

    // QWidget interface
protected:
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;
};

#endif // QTDRAGEVENT_H
