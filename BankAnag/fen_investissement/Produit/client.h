#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

#include <QSqlQuery>
#include <QDebug>

#include <QSqlTableModel>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dcombobox.h"
#include "DesignWidgets/dpushbutton.h"

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    Client(QSqlQuery q);

signals:

public slots:

private slots:
    void onClickedAddClient();
    void onClickedInsertClient();
    void onClickedTableClient(QModelIndex);

private:
    void setTabInfoClient(QWidget *w);
    void setTabListClient(QWidget *w);



private:
    struct ClientInfo{
        QLabel id,company,nom,prenom,sexe,adresse,phone,email;
        QLabel lastSaleDate,rating,totPurchased,totReturn,totDiscount;
    };

    QSqlQuery query;
    QList<QLabel*> label_listInfo;

    struct ClientInfo clientInfo;

    QSqlTableModel *modelTransaction;
    QTableView *tableTransaction;

    QSqlTableModel *modelTableClient;
    QTableView *tableClient;

    DLineEdit *company_edit;
    DComboBox *titre_comb;
    DLineEdit *nom_edit;
    DLineEdit *prenom_edit;
    DLineEdit *email_edit;
    DLineEdit *phone_edit;
    DLineEdit *adresse_edit;

};

#endif // CLIENT_H
