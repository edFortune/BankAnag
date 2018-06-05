#ifndef FEN_CLIENTPROFIL_DOCUMENT_DELEGATE_H
#define FEN_CLIENTPROFIL_DOCUMENT_DELEGATE_H

#include <QWidget>
#include <QComboBox>
#include <QObject>
#include <QItemDelegate>
#include <QDebug>
#include <QPainter>

class Fen_ClientProfil_document_delegate : public QItemDelegate
{
public:
    Fen_ClientProfil_document_delegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // FEN_CLIENTPROFIL_DOCUMENT_DELEGATE_H
