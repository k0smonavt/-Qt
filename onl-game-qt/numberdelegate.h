#ifndef NUMBERDELEGATE_H
#define NUMBERDELEGATE_H


#include <QItemDelegate>
#include <QLineEdit>
#include <QRegularExpressionValidator>

class NumberDelegate : public QItemDelegate
{
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // NUMBERDELEGATE_H
