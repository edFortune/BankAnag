#include "emprunteur.h"

#include <QHBoxLayout>
#include <QFormLayout>





Emprunteur::Emprunteur(QWidget *parent) : QWidget(parent)
{

}

Emprunteur::Emprunteur(QSqlQuery q)
{
    query = q;

    QHBoxLayout *hbox = new QHBoxLayout;
    this->setLayout(hbox);
    hbox->setSpacing(2);

    QWidget *listEmprunteurSide = new QWidget;
    hbox->addWidget(listEmprunteurSide);
    setTabListEmprunteur(listEmprunteurSide);

    QWidget *infoEmprunteurSide = new QWidget;
    hbox->addWidget(infoEmprunteurSide);
    setTabInfoEmprunteur(infoEmprunteurSide);

}

void Emprunteur::setTabListEmprunteur(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    vbox->addSpacing(0);
    vbox->setMargin(0);

    modelTableEmprunteur = new QSqlTableModel;
    modelTableEmprunteur->setTable("Emprunteur");
    modelTableEmprunteur->select();

    tableEmprunteur = new QTableView;
    tableEmprunteur->setModel(modelTableEmprunteur);
    tableEmprunteur->setAlternatingRowColors(true);
    tableEmprunteur->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableEmprunteur->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableEmprunteur->setContextMenuPolicy(Qt::CustomContextMenu);
    tableEmprunteur->setMinimumWidth(200);
    tableEmprunteur->setColumnWidth(0,50);
    vbox->addWidget(tableEmprunteur);

    connect(tableEmprunteur,SIGNAL(clicked(QModelIndex)),this,SLOT(onClickTableEmprunteur(QModelIndex)));
    connect(tableEmprunteur,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenu(QPoint)));
}

void Emprunteur::setTabInfoEmprunteur(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    w->setObjectName("wInfoFournisseur");
    w->setStyleSheet("#wInfoFournisseur{background-color:lightgray;}");

    QHBoxLayout *hboxTitle = new QHBoxLayout;
    vbox->addLayout(hboxTitle);

    QLabel *title = new QLabel("Information sur l'emprunteur:");
    title->setFont(QFont("Datum",10,QFont::Bold,false));
    hboxTitle->addWidget(title);

    DPushButton *addEmprunteur = new DPushButton("Ajouter un emprunteur");
    addEmprunteur->setMaximumWidth(200);
    hboxTitle->addWidget(addEmprunteur);

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

    formInfo1->addRow("ID",&emprunteurInfo.id);
    formInfo1->addRow("Company",&emprunteurInfo.company);
    formInfo1->addRow("Nom",&emprunteurInfo.nom);
    formInfo1->addRow("Prenom",&emprunteurInfo.prenom);
    formInfo1->addRow("Sexe",&emprunteurInfo.sexe);
    formInfo1->addRow("Adresse",&emprunteurInfo.adresse);
    formInfo1->addRow("Phone",&emprunteurInfo.phone);
    formInfo1->addRow("E-Mail",&emprunteurInfo.email);

    QFormLayout *formInfo2 = new QFormLayout;
    formInfo2->setSpacing(15);
    grid->addLayout(formInfo2,0,1);

    formInfo2->addRow("Vendor Code",new QLabel("---"));
    formInfo2->addRow("Account#",new QLabel("---"));
    formInfo2->addRow("Total Received Cost",new QLabel("---"));
    formInfo2->addRow("Total Returned Cost",new QLabel("---"));
    formInfo2->addRow("Average Cost/Voucher",new QLabel("---"));
    formInfo2->addRow("Total On Order",new QLabel("---"));
    formInfo2->addRow("Total Units On Order",new QLabel("---"));


    QWidget *Hline2 = new QWidget;
    Hline2->setObjectName("Hline2");
    Hline2->setStyleSheet("#Hline2{background-color:black;}");
    Hline2->setMinimumHeight(2);
    vbox->addWidget(Hline2);


    modelServiceTransaction = new QSqlRelationalTableModel;
    modelServiceTransaction->setTable("ServiceInvestment");
    modelServiceTransaction->select();

    QTableView *tableServiceTransaction = new QTableView;
    tableServiceTransaction->setModel(modelServiceTransaction);
    tableServiceTransaction->setMinimumWidth(900);
    tableServiceTransaction->setAlternatingRowColors(true);
    tableServiceTransaction->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableServiceTransaction->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vbox->addWidget(tableServiceTransaction);

    //---------------------------------------------------------------------------
    connect(addEmprunteur,SIGNAL(clicked()),this,SLOT(onClickedAddEmprunteur()));
}


void Emprunteur::onClickedAddEmprunteur()
{
    QDialog *diagAddEmprunteur = new QDialog;
    diagAddEmprunteur->setWindowTitle("Ajouter un nouveau emprunteur");
    diagAddEmprunteur->setModal(true);
    diagAddEmprunteur->setMinimumWidth(300);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagAddEmprunteur->setLayout(vbox);

    nomEmprunteur = new DLineEdit("Nom:");
    vbox->addWidget(nomEmprunteur);

    prenomEmprunteur = new DLineEdit("Prenom:");
    vbox->addWidget(prenomEmprunteur);

    sexeEmprunteur = new DComboBox("Sexe:");
    sexeEmprunteur->addItem("Masculin");
    sexeEmprunteur->addItem("Feminin");
    vbox->addWidget(sexeEmprunteur);

    company = new DLineEdit("Nom du compagnie:");
    vbox->addWidget(company);

    adressEmprunteur = new DLineEdit("Adresse:");
    vbox->addWidget(adressEmprunteur);

    telEmprunteur = new DLineEdit("Telephone:");
    vbox->addWidget(telEmprunteur);

    emailEmprunteur = new DLineEdit("E-mail:");
    vbox->addWidget(emailEmprunteur);

    DPushButton *ajouterEmprunteur = new DPushButton("Ajouter");
    vbox->addWidget(ajouterEmprunteur);

    diagAddEmprunteur->show();

    connect(ajouterEmprunteur,SIGNAL(clicked()),this,SLOT(insertNewEmprunteur()));

}

void Emprunteur::showContextMenu(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer l'emprunteur"),this);
    contextMenu.addAction(&action);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerEmprunteur()));
    contextMenu.exec(QCursor::pos());

}

void Emprunteur::effacerEmprunteur()
{
    int row = tableEmprunteur->selectionModel()->currentIndex().row();
    QString id = modelTableEmprunteur->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    query.prepare("DELETE FROM Emprunteur WHERE ID = "+id);
    if(query.exec())
    {
        emprunteurInfo.nom.clear();
        emprunteurInfo.prenom.clear();
        emprunteurInfo.sexe.clear();
        emprunteurInfo.company.clear();
        emprunteurInfo.adresse.clear();
        emprunteurInfo.phone.clear();
        emprunteurInfo.email.clear();

        modelTableEmprunteur->select();
    }
}

void Emprunteur::insertNewEmprunteur()
{
    query.prepare("INSERT INTO Emprunteur (Nom,Prenom,Sexe,NomCompany,Adresse,Telephone,Email,cr_Date)"
                  "VALUES (:nom,:prenom,:sexe,:nCompany,:adress,:tel,:mail,:cD)");
    query.bindValue(":nom",nomEmprunteur->text());
    query.bindValue(":prenom",prenomEmprunteur->text());
    query.bindValue(":sexe",sexeEmprunteur->currentText());

    if(company->text().isEmpty())
        query.bindValue(":nCompany",nomEmprunteur->text()+" "+prenomEmprunteur->text());
    else
        query.bindValue(":nCompany",company->text());

    query.bindValue(":adress",adressEmprunteur->text());
    query.bindValue(":tel",telEmprunteur->text());
    query.bindValue(":mail",emailEmprunteur->text());
    query.bindValue(":cD",QDate::currentDate());

    if(query.exec())
    {
        qDebug()<<"Emprunteur was inserted";
        nomEmprunteur->clear();
        prenomEmprunteur->clear();
        company->clear();
        adressEmprunteur->clear();
        telEmprunteur->clear();
        emailEmprunteur->clear();

        modelTableEmprunteur->select();
    }else
        qDebug()<<"Emprunteur was not inserted: "<<query.lastError();
}

void Emprunteur::onClickTableEmprunteur(QModelIndex idx)
{
    int row = idx.row();
    QString id = modelTableEmprunteur->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    //QString companyName = modelTableEmprunteur->index(row,0,QModelIndex()).data(Qt::EditRole).toString();

    query.prepare("SELECT * FROM Emprunteur WHERE ID = "+id);
    if(query.exec())
    {
        while(query.next())
        {
            emprunteurInfo.nom.setText(query.value(1).toString());
            emprunteurInfo.prenom.setText(query.value(2).toString());
            emprunteurInfo.sexe.setText(query.value(3).toString());
            emprunteurInfo.company.setText(query.value(4).toString());
            emprunteurInfo.adresse.setText(query.value(5).toString());
            emprunteurInfo.phone.setText(query.value(6).toString());
            emprunteurInfo.email.setText(query.value(7).toString());

            modelServiceTransaction->setFilter("EMPRUNTEUR = "+id);
        }

    }

}
