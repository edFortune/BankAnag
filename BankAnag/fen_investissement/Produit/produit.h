#ifndef PRODUIT_H
#define PRODUIT_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QTreeView>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCompleter>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dtextedit.h"
#include "DesignWidgets/ddoublespinbox.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dlabel.h"

#include "fournisseur.h"
#include "customitemdelegates.h"
#include "investments.h"


class Produit : public QWidget
{
    Q_OBJECT
public:
    explicit Produit(QWidget *parent = 0);
    Produit(QSqlQuery q);

    DDoubleSpinBox *getPrixAchat() const;
    void setPrixAchat(DDoubleSpinBox *value);

    DDoubleSpinBox *getPrixVente() const;
    void setPrixVente(DDoubleSpinBox *value);

    void initializeHashList();

    int getIdByValue(int column, QString val);

    int getIdItemByName(const QString itemName) const;

    void fetchProduitByName(QString produitName);

    double getPriceAchatItemByName(const QString itemName) const;

    //Getter function that return values from the database
    int getIdProduit() const;
    QString getNomProduit() const;
    QString getDescriptionProduit() const;
    QString getAttributeProduit() const;
    QString getSizeProduit() const;
    double getPrixAchatProduit() const;
    double getPrixVenteProduit() const;
    int getIdFournisseurProduit() const;
    QDate getCreateDateProduit() const;
    double getQteEnStockProduit() const;


signals:

private slots:
    void onClickedAddToDB();
    void onClickAddItem();
    void onClickListItem();
    void onClickListVente();
    void onClickHistoricite();
    void onClickProduit();
    void onClickListAchat();
    void onClickTransaction();
    void showContextMenu(QPoint);
    void retournerVente();
    void onPressedSearchHistory();

    //Private functions
    void onDoubleClickModifiedItem(QModelIndex idx);
    void onCickedModifier();
    void showDiagCreditSale(QModelIndex);
    void addVersementCreditST();
    void onDoubleClickTableHist(QModelIndex idx);
    void onClickChangePrixAchat();
private:
    void setTabAddProduit(QWidget *w);
    void setTabListProduit(QWidget *w);
    void setTabHistoryProduit(QWidget *w);
    void setTabListVente(QWidget *w);
    void ajusterAffichage();
    void ajusterQteEnStock(int);

    void generalRefreshModels();


    //Private variables
private:
    QSqlQuery query;
    QSqlRelationalTableModel *modelTableProduit;

    Investments *listAchatTab;

    DLineEdit *nom;
    DTextEdit *description;
    DLineEdit *attribute;
    DLineEdit *size;
    DDoubleSpinBox *prixAchat;
    DDoubleSpinBox *prixVente;
    DLineEdit *idFournisseur;
    DDateEdit *createDate;

    Fournisseur *fournisseurs;
    QHash<QString,int>idItemByName;
    QHash<QString,double>priceAchatItemByName;

    //Variable of object class
    int idProduit;
    QString nomProduit;
    QString descriptionProduit;
    QString attributeProduit;
    QString sizeProduit;
    double qteEnStockProduit;
    double prixAchatProduit;
    double prixVenteProduit;
    int idFournisseurProduit;
    QDate createDateProduit;

    //Stacked
    QStackedWidget *stackPage;

    //others
    DLineEdit *searchProdHistory;
    DLabel *qteVente_lab;
    DLabel *totVente_lab;
    DLabel *benefice_lab;

    //Liste des produits
    DLabel *idItem;
    DDoubleSpinBox *prixAchatItem;
    DDoubleSpinBox *prixVenteItem;

    //Liste des ventes
    QTableView *tableVente;
    QSqlRelationalTableModel *modelTableVente;
    QSqlRelationalTableModel *modelHistoryProduit;
    DLabel *totVersementST_label;
    DLabel *balancetST_label;
    QSqlTableModel *modeltableVersementCVente;
    DDateEdit *dateVersST;
    DDoubleSpinBox *doubleVersementST;
    DLineEdit *descripVersST;
    DLabel *idST_label;
    double totVenteSalesTransac;

    //History
    DLabel *qtyTotalVente_lab;
    DLabel *prixTotalAchat_lab;
    DLabel *prixTotalVente_lab;
    DLabel *beneficeVente_lab;

    //
    int IDSALES_DETAILS;
    DDoubleSpinBox *prixAchatChange_spin;
    QDialog *diagPrixAchat;


};

#endif // PRODUIT_H
