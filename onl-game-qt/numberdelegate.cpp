#include "numberdelegate.h"

QWidget* NumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[0-9]+"), editor);
    editor->setValidator(validator);
    return editor;
}
