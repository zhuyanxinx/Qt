#include "tcomboboxdelegate.h"
#include <QComboBox>

TComboBoxDelegate::TComboBoxDelegate(QObject* parent)
    : QStyledItemDelegate { parent }
{
}

void TComboBoxDelegate::setItems(QStringList items, bool editable)
{
    lstItem = items;
    this->editable = editable;
}

QWidget* TComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(lstItem);
    return editor;
}

void TComboBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
    QString val = index.model()->data(index, Qt::EditRole).toString();
    comboBox->setCurrentText(val);
}

void TComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
    QString val = comboBox->currentText();
    model->setData(index, val, Qt::EditRole);
}

void TComboBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}
