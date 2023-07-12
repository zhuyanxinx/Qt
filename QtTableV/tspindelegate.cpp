#include "tspindelegate.h"
#include <QSpinBox>

TSpinDelegate::TSpinDelegate(QObject* parent)
    : QStyledItemDelegate { parent }
{
}

QWidget* TSpinDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSpinBox* spinBox = new QSpinBox(parent);
    spinBox->setFrame(false);
    spinBox->setMinimum(0);
    spinBox->setMaximum(100);
    return spinBox;
}

void TSpinDelegate::destroyEditor(QWidget* editor, const QModelIndex& index) const
{
}

void TSpinDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor);
    int val = index.model()->data(index, Qt::EditRole).toInt();
    spinBox->setValue(val);
}

void TSpinDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor);
    int val = spinBox->value();
    model->setData(index, val, Qt::EditRole);
}

void TSpinDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}
