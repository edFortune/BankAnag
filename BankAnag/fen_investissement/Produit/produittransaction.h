#ifndef PRODUITTRANSACTION_H
#define PRODUITTRANSACTION_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QMdiSubWindow>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QSqlQuery>
#include <QCompleter>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QDebug>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dtextedit.h"
#include "DesignWidgets/dlabel.h"
#include "DesignWidgets/ddoublespinbox.h"

#include "customitemdelegates.h"
#include "produit.h"

class ProduitTransaction : public QWidget
{
    Q_OBJECT
public:
    explicit ProduitTransaction(QWidget *parent = 0);
    ProduitTransaction(QSqlQuery q);
    void setFenWidget(QMdiSubWindow *sub);

signals:
private slots:
    void onEnterItem(QString);
    void onItemModelTransactionChanged(QStandardItem*);
    void onValueDiscountChanged(double);
    void onClickMenuContext(QPoint);
    void deleteItem();
    void onClickedTakePayment();
    void onClickedSavePayment();
    void fermerFen();

    void insertIntoSalesDetails(int id, int idxItem);

public slots:

private:
    void updateQteProduitEnStock(double qteEnStock, int idProduit);


private:
    QMdiSubWindow *subWindow;
    QSqlQuery query;
    QStandardItemModel *modelTransaction;
    DComboBox *enterItem;
    DLabel *subtotal;
    DLabel *totalPayment;
    DDoubleSpinBox *discount;

    DDateEdit *dateTransac;
    DComboBox *customerInfo;

    QTableView *tableTransaction;
    QDialog *diagPayment;

    DDoubleSpinBox *cashPayment;
    DComboBox *typePayment;

    double totalPayment_V;
    double qteVendu_V;

};

#endif // PRODUITTRANSACTION_H
