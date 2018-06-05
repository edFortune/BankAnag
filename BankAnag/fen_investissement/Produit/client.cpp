#include "client.h"

#include <QDialog>

Client::Client(QWidget *parent) : QWidget(parent)
{

}

Client::Client(QSqlQuery q)
{
    query = q;

    QHBoxLayout *hbox = new QHBoxLayout;
    this->setLayout(hbox);
    hbox->setSpacing(2);

    QWidget *listClientSide = new QWidget;
    hbox->addWidget(listClientSide);
    setTabListClient(listClientSide);

    QWidget *infoClientSide = new QWidget;
    hbox->addWidget(infoClientSide);
    setTabInfoClient(infoClientSide);

}



void Client::setTabListClient(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);

    modelTableClient = new QSqlTableModel;
    modelTableClient->setTable("Client");
    modelTableClient->select();

    tableClient = new QTableView;
    tableClient->setModel(modelTableClient);
    tableClient->setAlternatingRowColors(true);
    tableClient->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vbox->addWidget(tableClient);

    connect(tableClient,SIGNAL(clicked(QModelIndex)),this,SLOT(onClickedTableClient(QModelIndex)));
}


void Client::setTabInfoClient(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    w->setObjectName("wInfoClient");
    w->setStyleSheet("#wInfoClient{background-color:lightgray;}");

    QHBoxLayout *hboxTitle = new QHBoxLayout;
    vbox->addLayout(hboxTitle);

    QLabel *title = new QLabel("Information sur le client:");
    title->setFont(QFont("Datum",10,QFont::Bold,false));
    hboxTitle->addWidget(title);

    DPushButton *addClient = new DPushButton("Ajouter un client");
    addClient->setMaximumWidth(200);
    hboxTitle->addWidget(addClient);

    QWidget *Hline = new QWidget;
    Hline->setObjectName("Hline");
    Hline->setStyleSheet("#Hline{background-color:black;}");
    Hline->setMinimumHeight(3);
    vbox->addWidget(Hline);

    QGridLayout *grid = new QGridLayout;
    vbox->addLayout(grid);

    QFormLayout *formInfo1 = new QFormLayout;
    formInfo1->setSpacing(15);
    grid->addLayout(formInfo1,0,0);


    formInfo1->addRow("ID",&clientInfo.id);
    formInfo1->addRow("Company",&clientInfo.company);
    formInfo1->addRow("Nom",&clientInfo.nom);
    formInfo1->addRow("Prenom",&clientInfo.prenom);
    formInfo1->addRow("Sexe",&clientInfo.sexe);
    formInfo1->addRow("Adresse",&clientInfo.adresse);
    formInfo1->addRow("Phone",&clientInfo.phone);
    formInfo1->addRow("E-Mail",&clientInfo.email);


    QFormLayout *formInfo2 = new QFormLayout;
    formInfo2->setSpacing(15);
    grid->addLayout(formInfo2,0,1);

    formInfo2->addRow("Last Sale Date",new QLabel("---"));
    formInfo2->addRow("Rating",new QLabel("---"));
    formInfo2->addRow("Total Purchased",new QLabel("---"));
    formInfo2->addRow("Total Returned",new QLabel("---"));
    formInfo2->addRow("Total od Discounts",new QLabel("---"));


    QWidget *Hline2 = new QWidget;
    Hline2->setObjectName("Hline2");
    Hline2->setStyleSheet("#Hline2{background-color:black;}");
    Hline2->setMinimumHeight(2);
    vbox->addWidget(Hline2);


    modelTransaction = new QSqlTableModel;
    modelTransaction->setTable("Sales_Transaction");
    modelTransaction->select();

    tableTransaction = new QTableView;
    tableTransaction->setModel(modelTransaction);
    tableTransaction->setMinimumWidth(900);
    tableTransaction->setAlternatingRowColors(true);
    tableTransaction->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableTransaction->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vbox->addWidget(tableTransaction);

    connect(addClient,SIGNAL(clicked()),this,SLOT(onClickedAddClient()));

}

void Client::onClickedAddClient()
{
    QDialog *diagAddClient = new QDialog;
    diagAddClient->setWindowTitle("Ajouter un nouveau client");
    diagAddClient->setModal(true);
    diagAddClient->setMinimumWidth(300);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagAddClient->setLayout(vbox);

    company_edit = new DLineEdit("Companie:");
    vbox->addWidget(company_edit);

    titre_comb = new DComboBox("Titre");
    titre_comb->addItem("Mr.");
    titre_comb->addItem("Mlle");
    titre_comb->addItem("Mme");
    vbox->addWidget(titre_comb);

    nom_edit = new DLineEdit("Nom:");
    vbox->addWidget(nom_edit);

    prenom_edit = new DLineEdit("Prenom:");
    vbox->addWidget(prenom_edit);

    email_edit = new DLineEdit("E-mail:");
    vbox->addWidget(email_edit);

    phone_edit = new DLineEdit("Phone:");
    vbox->addWidget(phone_edit);

    adresse_edit = new DLineEdit("Adresse:");
    vbox->addWidget(adresse_edit);

    DPushButton *ajouterClient = new DPushButton("Ajouter");
    vbox->addWidget(ajouterClient);


    diagAddClient->show();

    connect(ajouterClient,SIGNAL(clicked()),this,SLOT(onClickedInsertClient()));

}

void Client::onClickedInsertClient()
{
    query.prepare("INSERT INTO Client (Company,Titre,Nom,Prenom,Email,Phone,Adresse)"
                  "VALUES (:comp,:tit,:nom,:prenom,:mail,:phone,:adress)");
    query.bindValue(":comp",company_edit->text());
    query.bindValue(":tit",titre_comb->currentText());
    query.bindValue(":nom",nom_edit->text());
    query.bindValue(":prenom",prenom_edit->text());
    query.bindValue(":mail",email_edit->text());
    query.bindValue(":phone",phone_edit->text());
    query.bindValue(":adress",adresse_edit->text());

    if(query.exec())
    {
        qDebug()<<"Client has been inserted";
        company_edit->clear();
        nom_edit->clear();
        prenom_edit->clear();
        email_edit->clear();
        phone_edit->clear();
        adresse_edit->clear();
        modelTableClient->select();
    }else
        qDebug()<<"Client has not been inserted";

}


void Client::onClickedTableClient(QModelIndex idx)
{
    int row = idx.row();
    QString id = modelTableClient->data(modelTableClient->index(row,0),Qt::EditRole).toString();
    QString nomComp = modelTableClient->data(modelTableClient->index(row,1),Qt::EditRole).toString();

    query.prepare("SELECT * FROM Client WHERE ID= "+id);
    if(query.exec())
    {
        if(query.next())
        {
            clientInfo.id.setText(query.value(0).toString());
            clientInfo.company.setText(query.value(1).toString());
            clientInfo.nom.setText(query.value(3).toString());
            clientInfo.prenom.setText(query.value(4).toString());
            clientInfo.adresse.setText(query.value(7).toString());
            clientInfo.phone.setText(query.value(6).toString());
            clientInfo.email.setText(query.value(5).toString());

            modelTransaction->setFilter("[Nom Complet] = '"+nomComp+"' ");
        }

    }
}
