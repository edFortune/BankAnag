#include "fen_caisse_delegate.h"

Fen_Caisse_Delegate::Fen_Caisse_Delegate(QObject *parent) :
    QItemDelegate(parent)
{

}

QWidget* Fen_Caisse_Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==5)
    {
        QLineEdit *editor = new QLineEdit(parent);

        return editor;
    }

    return NULL;

}


void Fen_Caisse_Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column()==5)
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();
        QLineEdit *editItem = (QLineEdit*)editor;
        editItem->setText(value);

    }

}

void Fen_Caisse_Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column()==5)
    {
        QLineEdit *editItem = (QLineEdit*)editor;
        double value = editItem->text().toDouble();
        model->setData(index,value);

        if(editItem->text().isEmpty())
            return;

        double total = index.model()->data(model->index(index.row(),6),Qt::EditRole).toDouble();
        model->setData(model->index(index.row(),6),value+total);

    }

}

void Fen_Caisse_Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==5)
        editor->setGeometry(option.rect);
}




