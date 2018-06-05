#include "fen_caisse_delegate2.h"

fen_caisse_delegate2::fen_caisse_delegate2(QObject *parent) :
    QItemDelegate(parent)
{
}


QWidget *fen_caisse_delegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(1000000.00);

    QDoubleSpinBox *editor2 = new QDoubleSpinBox(parent);
    editor2->setMinimum(0);
    editor2->setMaximum(100.00);

    if(index.column()==2 )
        return editor;


    if(index.column()==3 || index.column()==5)
        return editor2;

    return NULL;

}


void fen_caisse_delegate2::setEditorData(QWidget *editor, const QModelIndex &index) const
{


    if(index.column()== 2 || index.column()== 3 || index.column()== 5 )
    {
        double value = index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *doubleSpin = (QDoubleSpinBox*)editor;
        doubleSpin->setValue(value);

    }
}

void fen_caisse_delegate2::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    if(index.column()==2)
    {
        QDoubleSpinBox *doubleSpin = (QDoubleSpinBox*)editor;
        double montant = doubleSpin->value();
        model->setData(index,montant);


        double tauxAchat = model->data(model->index(index.row(),3),Qt::EditRole).toDouble();
        double tauxVente = model->data(model->index(index.row(),5),Qt::EditRole).toDouble();

        model->setData(model->index(index.row(),4),montant*tauxAchat);
        model->setData(model->index(index.row(),6),montant*tauxVente);
        model->setData(model->index(index.row(),7),(montant*tauxVente)-(montant*tauxAchat));

    }else if(index.column()==3){

        QDoubleSpinBox *doubleSpin = (QDoubleSpinBox*)editor;
        double tauxAchat = doubleSpin->value();
        model->setData(index,tauxAchat);

        double montant = model->data(model->index(index.row(),2),Qt::EditRole).toDouble();
        double tauxVente = model->data(model->index(index.row(),5),Qt::EditRole).toDouble();

        model->setData(model->index(index.row(),4),montant*tauxAchat);
        model->setData(model->index(index.row(),6),montant*tauxVente);
        model->setData(model->index(index.row(),7),(montant*tauxVente)-(montant*tauxAchat));

    }else if(index.column()==5){

        QDoubleSpinBox *doubleSpin = (QDoubleSpinBox*)editor;
        double tauxVente = doubleSpin->value();
        model->setData(index,tauxVente);


        double montant = model->data(model->index(index.row(),2),Qt::EditRole).toDouble();
        double tauxAchat = model->data(model->index(index.row(),3),Qt::EditRole).toDouble();

        model->setData(model->index(index.row(),4),montant*tauxAchat);
        model->setData(model->index(index.row(),6),montant*tauxVente);
        model->setData(model->index(index.row(),7),(montant*tauxVente)-(montant*tauxAchat));
    }

}


void fen_caisse_delegate2::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==2 || index.column()==3 || index.column()==5)
        editor->setGeometry(option.rect);
}
