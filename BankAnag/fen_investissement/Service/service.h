#ifndef SERVICE_H
#define SERVICE_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QAction>

#include <QDialog>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QDebug>

#include <DesignWidgets/ddateedit.h>
#include <DesignWidgets/ddoublespinbox.h>
#include <DesignWidgets/dtextedit.h>
#include <DesignWidgets/dcombobox.h>
#include <DesignWidgets/dlabel.h>
#include <DesignWidgets/dlineedit.h>
#include <DesignWidgets/dgroupbox.h>

class Service : public QWidget
{
    Q_OBJECT
public:
    explicit Service(QWidget *parent = 0);
    Service(QSqlQuery q);

signals:

public slots:

private slots:
    void showDialogAddInvestment();
    void onClickedServiceTable(QModelIndex);
    void insertIntoServiceInvestmentTable();
    void insertIntoVersementTable();
    void showDiagAddVersement();

    void showContextVersementMenu(QPoint);
    void effacerVersement();

    void showContextInvestmentMenu(QPoint);
    void effacerInvestment();

private:
    void updateInvestmentTotal();

private:
    QSqlQuery query;

    DDateEdit *dateInvestment;
    DComboBox *emprunteurInvest;
    DComboBox *typeArgent;
    DDoubleSpinBox *montantInvest;
    DDoubleSpinBox *tauxMontant;
    DTextEdit *descriptionInvest;

    QSqlRelationalTableModel *modelInvestmentService;
    QTableView *tableServiceInvestment;

    QSqlRelationalTableModel *modelVersement;
    QTableView *tableVersement;

    DDateEdit *dateVersement;
    DLineEdit *descriptVersement;
    DDoubleSpinBox *montantVersement;
    DDoubleSpinBox *tauxVersement;


    DLabel *idEmprunteur_lab;
    DLabel *mtntInvestment_lab;
    DLabel *versement_lab;
    DLabel *balance_lab;
    DLabel *profit_lab;


    DLabel *totInvestmentHTG_lab;
    DLabel *totInvestmentUSD_lab;

};

#endif // SERVICE_H
