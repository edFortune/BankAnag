#ifndef INVESTISSEMENT_H
#define INVESTISSEMENT_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSplitter>
#include <QMdiSubWindow>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>

#include "produitinvestments.h"




class Investissement : public QWidget
{
    Q_OBJECT
public:
    explicit Investissement(QWidget *parent = 0);
    Investissement(QSqlQuery q);

    void setFenWidget(QMdiSubWindow *subWin);


signals:

private slots:


    //Private Variables
private:
    QSqlQuery query;
    QMdiSubWindow *subWindow;
};

#endif // INVESTISSEMENT_H
