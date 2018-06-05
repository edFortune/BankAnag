#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QDialog>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QDebug>

#include <QSqlTableModel>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/dpushbutton.h"



class Fournisseur : public QWidget
{
    Q_OBJECT
public:
    explicit Fournisseur(QWidget *parent = 0);
    Fournisseur(QSqlQuery q);

    int getIdByValue(int column, QString val);

    void fetchFournisseurByCompanyName(QString cName);

    int getIdFournisseur() const;
    QString getNomFournisseur() const;
    QString getPrenomFournisseur() const;
    QString getSexeFournisseur() const;
    QString getAdresseFournisseur() const;
    QString getTelephoneFournisseur() const;
    QString getNomCompanyFournisseur() const;
    QString getEmailFournisseur() const;
    QDate getCr_dateFournisseur() const;

signals:

private slots:
    void onClickedAddToDB();
    void onClickedAddFournisseur();
    void onClickedTableFournisseur(QModelIndex);

    //Private functions
private:
    void setTabListFournisseur(QWidget *w);
    void setTabInfoFournisseur(QWidget *w);

    //Private variables
private:
    struct FournisseurInfo{
        QLabel id,company,nom,prenom,sexe,adresse,phone,email;
        QLabel lastSaleDate,rating,totPurchased,totReturn,totDiscount;
    };

    QSqlQuery query;
    QSqlTableModel *modelTableFournisseur;
    QSqlRelationalTableModel *modelProduitTransaction;

    DLineEdit *nom;
    DLineEdit *prenom;
    DComboBox *sexe;
    DLineEdit *adresse;
    DLineEdit *telephone;
    DDateEdit *createDate;
    DLineEdit *nomCompany;
    DLineEdit *email;

    int idFournisseur;
    QString nomFournisseur;
    QString prenomFournisseur;
    QString sexeFournisseur;
    QString adresseFournisseur;
    QString telephoneFournisseur;
    QString nomCompanyFournisseur;
    QString emailFournisseur;
    QDate cr_dateFournisseur;

    QFormLayout *formInfo1;

    QList<QLabel*> label_listInfo;
    FournisseurInfo fournisseurInfo;

};

#endif // FOURNISSEUR_H
