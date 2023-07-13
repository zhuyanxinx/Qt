#ifndef TCLICKEDLABEL_H
#define TCLICKEDLABEL_H

#include <QLabel>
#include <QObject>

class TClickedLabel : public QLabel {
    Q_OBJECT
public:
    TClickedLabel(QWidget* parent = nullptr);
signals:
    void doubleClicked();

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual bool event(QEvent* event) override;
};

#endif // TCLICKEDLABEL_H
