#ifndef FEN_TRANSACTION_DELEGATE_H
#define FEN_TRANSACTION_DELEGATE_H


#include <QWidget>
#include <QComboBox>
#include <QObject>
#include <QItemDelegate>
#include <QDebug>
#include <QPainter>

class Fen_Transaction_delegate : public QItemDelegate
{
public:
    Fen_Transaction_delegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;




};

#endif // FEN_TRANSACTION_DELEGATE_H
