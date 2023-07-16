#ifndef QTEVENTFILTER_H
#define QTEVENTFILTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class QtEventFilter;
}
QT_END_NAMESPACE

class QtEventFilter : public QWidget {
    Q_OBJECT

public:
    QtEventFilter(QWidget* parent = nullptr);
    ~QtEventFilter();

private:
    Ui::QtEventFilter* ui;

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // QTEVENTFILTER_H
