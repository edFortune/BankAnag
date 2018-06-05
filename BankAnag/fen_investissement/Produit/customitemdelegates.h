#ifndef CUSTOMITEMDELEGATES_H
#define CUSTOMITEMDELEGATES_H

#include <QItemDelegate>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPainter>

class TransactionDelegate : public QItemDelegate
{

private:


public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option);
        if(index.column()==5 || index.column()==6)
        {
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setMaximum(99999.99);
            return editor;
        }

        return NULL;
    }


    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        if(index.column()==5 || index.column()==6)
        {
            double value = index.model()->data(index,Qt::EditRole).toDouble();
            QDoubleSpinBox *editItem = (QDoubleSpinBox*)editor;
            editItem->setValue(value);

        }
    }


    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        if(index.column()==5)
        {
            QDoubleSpinBox *editItem = (QDoubleSpinBox*)editor;
            editItem->setMaximum(99999.99);
            double value = editItem->value();
            model->setData(index,value);

            double total = index.model()->data(model->index(index.row(),6),Qt::EditRole).toDouble();
            model->setData(model->index(index.row(),7),value*total);

        }else if(index.column()==6)
        {
            QDoubleSpinBox *editItem = (QDoubleSpinBox*)editor;
            editItem->setMaximum(999999.99);
            double value = editItem->value();
            model->setData(index,value);

            double qty = index.model()->data(model->index(index.row(),5),Qt::EditRole).toDouble();
            model->setData(model->index(index.row(),7),qty*value);
        }
    }


    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(index);
        Q_UNUSED(option);
        editor->setGeometry(option.rect);
    }

};



class ListVenteDelegate : public QItemDelegate
{
private:

public:

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        Q_UNUSED(editor);
        if(index.column()==7)
        {
            if(index.data().toInt()==1)
                model->setData(index,"Return",Qt::DisplayRole);
            else
                model->setData(index,"",Qt::DisplayRole);
        }
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if(index.column()==7){
            if(index.data().toInt()==1)
                painter->fillRect(option.rect, Qt::red);
        }
        QItemDelegate::paint( painter, option, index );
    }

};























#endif // CUSTOMITEMDELEGATES_H
