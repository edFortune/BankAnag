#ifndef INVESTMENTS_H
#define INVESTMENTS_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QDialog>
#include <QMessageBox>
#include <QDoubleSpinBox>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QMenu>
#include <QAction>

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/ddoublespinbox.h"
#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dlabel.h"

#include "creditinvestment.h"

class Investments : public QWidget
{
    Q_OBJECT
public:
    explicit Investments(QWidget *parent = 0);
    Investments(QSqlQuery);

    void refreshModels();

signals:

private slots:
    void onDoubleClickedTableInvest(QModelIndex);
    void onClickedAddCredit();
    void showContextMenuInvestment(QPoint);
    void effacerInvestment();


    void onClickedTabBar();
private:
    void setTabListeInvestment(QWidget *w);
    void updateQteProduitEnStock(double qteEnStock, double qteInvestment, int idProduit);
    void ajusterAffichage();

private:
    QSqlQuery query;

    QSqlRelationalTableModel *modelInvestment;
    QTableView *tableInvestment;

    //Dialog credit investment
    QDialog *diagCredit;
    DLabel *idInvestment;
    DDateEdit *dateCredit;
    DLineEdit *descriptionVers;
    DLabel *mtntCredit;
    DDoubleSpinBox *fversement;
    DLabel *balanceCredit;
    QComboBox *typePayer;

    //Variables credit investment
    double qte,totAchat;

    DLabel *totQty_lab;
    DLabel *totAchat_lab;

    //credit
    CreditInvestment *creditInvestmentPage;
};

#endif // INVESTMENTS_H
