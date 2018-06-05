#ifndef CREDITINVESTMENT_H
#define CREDITINVESTMENT_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QDialog>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QMenu>
#include <QAction>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/ddoublespinbox.h"
#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dlabel.h"

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class CreditInvestment : public QWidget
{
    Q_OBJECT
public:
    explicit CreditInvestment(QWidget *parent = 0);
    CreditInvestment(QSqlQuery q);
    void selectModelCredit();
    void loadDataVersement(QString id, double mtntDu);

signals:

public slots:

private slots:
    void onDoubleClickedTableCredit(QModelIndex);
    void onClickedAddVersement();
    void showContextMenuCredit(QPoint);
    void effacerCredit();
    void showContextMenuVersement(QPoint);
    void effacerVersement();

private:
    void setTabListeCredit(QWidget *w);

private:
    QSqlQuery query;
    QSqlRelationalTableModel *modelCreditProduit;
    QTableView *tableCreditProduit;

    DDateEdit *dateVers;
    DLineEdit *descripVers;
    DDoubleSpinBox *mtntVersement;
    QSqlRelationalTableModel *modelVersementCredit;
    QTableView *tableVersementCredit;

    double totMontantDu;

    DLabel *idInvest;
    DLabel *totVersement;
    DLabel *balance;
};

#endif // CREDITINVESTMENT_H
