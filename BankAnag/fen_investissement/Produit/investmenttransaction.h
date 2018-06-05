#ifndef INVESTMENTTRANSACTION_H
#define INVESTMENTTRANSACTION_H

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

#include "produittransaction.h"

class InvestmentTransaction : public QWidget
{
    Q_OBJECT
public:
    explicit InvestmentTransaction(QWidget *parent = 0);
    InvestmentTransaction(QSqlQuery q);

    void setFenWidget(QMdiSubWindow *sub);

signals:

public slots:

    //Private Variables
private:
    QSqlQuery query;
    QMdiSubWindow *subWindow;
};

#endif // INVESTMENTTRANSACTION_H
