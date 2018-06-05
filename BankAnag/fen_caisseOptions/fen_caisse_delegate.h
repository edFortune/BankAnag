#ifndef FEN_CAISSE_DELEGATE_H
#define FEN_CAISSE_DELEGATE_H

//#include <widgetStyleHeader.h>
#include <QWidget>
#include <QLineEdit>
#include <QObject>
#include <QItemDelegate>

class Fen_Caisse_Delegate : public QItemDelegate
{

public:
    explicit Fen_Caisse_Delegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;



signals:


public slots:

private:


};

#endif // FEN_CAISSE_DELEGATE_H
