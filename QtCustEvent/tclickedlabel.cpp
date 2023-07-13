#include "tclickedlabel.h"
#include <QEvent>

TClickedLabel::TClickedLabel(QWidget* parent)
    : QLabel(parent)
{
    setAttribute(Qt::WA_Hover);
}

void TClickedLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit doubleClicked();
}

bool TClickedLabel::event(QEvent* event)
{
    QPalette plet = this->palette();
    if (event->type() == QEvent::HoverEnter) {
        plet.setColor(QPalette::WindowText, Qt::red);
    } else if (event->type() == QEvent::HoverEnter) {
        plet.setColor(QPalette::WindowText, Qt::black);
    }
    setPalette(plet);
    return QLabel::event(event);
}
