#ifndef FEN_CAISSE_DELEGATE2_H
#define FEN_CAISSE_DELEGATE2_H

//#include <widgetStyleHeader.h>
#include <QWidget>
#include <QDoubleSpinBox>
#include <QObject>
#include <QItemDelegate>

class fen_caisse_delegate2 : public QItemDelegate
{
    Q_OBJECT
public:
    explicit fen_caisse_delegate2(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
signals:
    
public slots:
    
};

#endif // FEN_CAISSE_DELEGATE2_H
