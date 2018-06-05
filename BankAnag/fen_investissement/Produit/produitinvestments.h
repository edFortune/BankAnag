#ifndef PRODUITINVESTMENTS_H
#define PRODUITINVESTMENTS_H

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QScrollArea>

#include <QGridLayout>
#include <QFormLayout>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dtextedit.h"
#include "DesignWidgets/dlabel.h"

#include "fournisseur.h"
#include "produit.h"

#include <QSqlQuery>
#include <QCompleter>
#include <QSqlQueryModel>

class ProduitInvestments : public QWidget
{
    Q_OBJECT
public:
    explicit ProduitInvestments(QWidget *parent = 0);
    ProduitInvestments(QSqlQuery q);
    static void refreshModels();

signals:

private slots:
    void onChangeProduitIndex(QString val);
    void onChangeInvesterIndex(QString);
    void onChangeTypePayerIndex(int);
    void onValuePrixAchatChange(double val);
    void onValuePrixVenteChange(double);
    void onValueQteAchatChange(double val);
    void onValueMtntVerstChange(double);
    void onClickedAjoutInvestment();

public slots:

    //Private functions
private:
    void addCreditOnDB(int id);
    void addVersementOnDB(int id);

    //Private variables
private:
    QSqlQuery query;

    Produit *produitInstance;
    Fournisseur *fournisseurInstance;

    //Invester Label details
    DDateEdit *dateInvestment;
    DComboBox *invester_name;
    DComboBox *itemName;
    DDoubleSpinBox *qteAchat;
    DDoubleSpinBox *prixAchat;
    DDoubleSpinBox *prixVente;
    DComboBox *typePayer;
    DTextEdit *descriptInvest;

    //Fournisseur QLabel details
    QLabel *idFourn;
    QLabel *nomFourn;
    QLabel *prenomFourn;
    QLabel *sexeFourn;
    QLabel *addrFourn;
    QLabel *telFourn;
    QLabel *emailFourn;
    QLabel *nomComp;

    //Produit QLabel details
    QLabel *prixAprod_lab;
    QLabel *idprod_lab;
    QLabel *nomprod_lab;
    QLabel *descriprod_lab;
    QLabel *attriprod_lab;
    QLabel *sizeprod_lab;
    QLabel *prixVprod_lab;

    DLabel *qteAchat_lab;
    DLabel *totalA_lab;
    DLabel *totalV_lab;
    DLabel *profit_lab;

    //Credit variable details
    DLabel *totalCredit;
    DLabel *totalBalance;
    DDoubleSpinBox *mtntVerst;
    DGroupBox *groupCredit;

    //Variable operations
    double totAchat;
    double totVente;
    int idInvestmentProduit;


};

#endif // PRODUITINVESTMENTS_H
