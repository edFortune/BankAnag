#include "fen_transaction/fen_transaction_delegate.h"

Fen_Transaction_delegate::Fen_Transaction_delegate(QObject *parent):
    QItemDelegate(parent)
{

}


QWidget *Fen_Transaction_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==13)
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("Oui");
        editor->addItem("Non");


        return editor;
    }

    return NULL;
}

void Fen_Transaction_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column()==13)
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();
        QComboBox *editItem = (QComboBox*)editor;
        editItem->setCurrentText(value);

    }

}

void Fen_Transaction_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column()==13)
    {
        QComboBox *editItem = (QComboBox*)editor;

        QString value = editItem->currentText();
        model->setData(index,value);

    }

}

void Fen_Transaction_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==13)
        editor->setGeometry(option.rect);
}

void Fen_Transaction_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==13){
        if(index.data().toString()=="Oui")
            painter->fillRect(option.rect, Qt::green);
        else
            painter->fillRect(option.rect, Qt::red);
    }

    QItemDelegate::paint( painter, option, index );
}
