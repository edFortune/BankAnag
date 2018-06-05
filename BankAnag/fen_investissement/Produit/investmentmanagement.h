#ifndef INVESTMENTMANAGEMENT_H
#define INVESTMENTMANAGEMENT_H

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

#include "produit.h"
#include "creditinvestment.h"
#include "client.h"

class InvestmentManagement : public QWidget
{
    Q_OBJECT
public:
    explicit InvestmentManagement(QWidget *parent = 0);
    InvestmentManagement(QSqlQuery q);

    void setFenWidget(QMdiSubWindow *sub);


signals:

private slots:
    void onActivatedListWidget(QModelIndex);

    void fermerFen();
private:
    QMdiSubWindow *subWind;
    QSqlQuery query;

    QStackedWidget *pageStack;

    CreditInvestment *creditInvestmentPage;
};

#endif // INVESTMENTMANAGEMENT_H
