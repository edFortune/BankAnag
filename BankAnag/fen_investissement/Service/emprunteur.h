#ifndef EMPRUNTEUR_H
#define EMPRUNTEUR_H

#include <QWidget>
#include <QLabel>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QTableView>
#include <QDialog>

#include <QDate>
#include <QDebug>
#include <QMenu>
#include <QAction>

#include "DesignWidgets/dpushbutton.h"
#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/dcombobox.h"

class Emprunteur : public QWidget
{
    Q_OBJECT
public:
    explicit Emprunteur(QWidget *parent = 0);
    Emprunteur(QSqlQuery q);

signals:

public slots:

private slots:
    void insertNewEmprunteur();
    void onClickTableEmprunteur(QModelIndex);
    void onClickedAddEmprunteur();
    void showContextMenu(QPoint);
    void effacerEmprunteur();


private:
    void setTabListEmprunteur(QWidget *w);
    void setTabInfoEmprunteur(QWidget *w);

private:
    struct EmprunteurInfo{
        QLabel id,company,nom,prenom,sexe,adresse,phone,email;
        QLabel lastSaleDate,rating,totPurchased,totReturn,totDiscount;
    };

    QSqlQuery query;

    struct EmprunteurInfo emprunteurInfo;

    DLineEdit *nomEmprunteur;
    DLineEdit *prenomEmprunteur;
    DComboBox *sexeEmprunteur;
    DLineEdit *company;
    DLineEdit *adressEmprunteur;
    DLineEdit *telEmprunteur;
    DLineEdit *emailEmprunteur;

    QSqlTableModel *modelTableEmprunteur;
    QTableView *tableEmprunteur;

    QSqlRelationalTableModel *modelServiceTransaction;

};

#endif // EMPRUNTEUR_H
