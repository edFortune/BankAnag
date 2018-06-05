#include "fournisseur.h"

Fournisseur::Fournisseur(QWidget *parent)
    : QWidget(parent)
{

}

Fournisseur::Fournisseur(QSqlQuery q)
{
    query = q;

    QHBoxLayout *hbox = new QHBoxLayout;
    this->setLayout(hbox);
    hbox->setSpacing(2);

    QWidget *listfournisseurSide = new QWidget;
    hbox->addWidget(listfournisseurSide);
    setTabListFournisseur(listfournisseurSide);

    QWidget *infoFournisseurSide = new QWidget;
    hbox->addWidget(infoFournisseurSide);
    setTabInfoFournisseur(infoFournisseurSide);


}

int Fournisseur::getIdByValue(int column, QString val)
{
    int id = -1;
    query.prepare("SELECT * FROM Fournisseurs");
    if(query.exec()){
        while(query.next()){
            if(query.value(column).toString()==val){
                id = query.value(0).toInt();
                break;
            }
        }
    }

    query.finish();

    return id;
}

void Fournisseur::fetchFournisseurByCompanyName(QString cName)
{
    query.prepare("SELECT * FROM Fournisseurs WHERE NomCompany = '"+cName+"' ");
    if(query.exec()){
        if(query.next()){
            this->idFournisseur = query.value(0).toInt();
            this->nomFournisseur = query.value(1).toString();
            this->prenomFournisseur = query.value(2).toString();
            this->sexeFournisseur = query.value(3).toString();
            this->nomCompanyFournisseur = query.value(5).toString();;
            this->adresseFournisseur = query.value(6).toString();
            this->telephoneFournisseur = query.value(7).toString();
            this->emailFournisseur = query.value(8).toString();
            this->cr_dateFournisseur = query.value(9).toDate();
        }
    }
    query.finish();
}


void Fournisseur::onClickedAddFournisseur()
{
    QDialog *diagAddFournisseur = new QDialog;
    diagAddFournisseur->setWindowTitle("Ajouter un nouveau fournisseur");
    diagAddFournisseur->setModal(true);

    QGridLayout *grid = new QGridLayout;
    diagAddFournisseur->setLayout(grid);

    nom = new DLineEdit("Nom:");
    grid->addWidget(nom,0,0);

    prenom = new DLineEdit("Prenom:");
    grid->addWidget(prenom,0,1);

    sexe = new DComboBox("Sexe:");
    sexe->addItem("Masculin");
    sexe->addItem("Feminin");
    grid->addWidget(sexe,1,0,1,2);

    nomCompany = new DLineEdit("Nom de l'entreprise");
    grid->addWidget(nomCompany,2,0);

    adresse = new DLineEdit("Adresse:");
    grid->addWidget(adresse,2,1);

    telephone = new DLineEdit("Telephone:");
    grid->addWidget(telephone,3,0);

    email = new DLineEdit("Email:");
    grid->addWidget(email,3,1);

    createDate = new DDateEdit("Date de creation");
    createDate->setCurrentDate();
    createDate->setCalendarPopup(true);
    grid->addWidget(createDate,4,0);

    DPushButton *addFournisseur = new DPushButton("Ajouter");
    grid->addWidget(addFournisseur,5,0,1,2);

    diagAddFournisseur->show();

    connect(addFournisseur,SIGNAL(clicked()),this,SLOT(onClickedAddToDB()));
}




void Fournisseur::onClickedAddToDB()
{
    if(nom->text().isEmpty())
        return;
    if(prenom->text().isEmpty())
        return;

    query.prepare("INSERT INTO Fournisseurs (Nom,Prenom, Sexe, NomCompany, Adresse, Telephone, Email, cr_Date)"
                  "VALUES (:nom,:prenom,:sexe,:nomcompany,:adresse,:tel,:email,:cr_date)");

    query.bindValue(":nom",nom->text());
    query.bindValue(":prenom",prenom->text());
    query.bindValue(":sexe",sexe->currentText());
    query.bindValue(":nomcompany",nomCompany->text());
    query.bindValue(":adresse",adresse->text());
    query.bindValue(":tel",telephone->text());
    query.bindValue(":email",email->text());
    query.bindValue(":cr_date",createDate->date());

    if(query.exec()){
        qDebug() << "Insertion of a new 'Fournisseur'";
        nom->clear();
        prenom->clear();
        nomCompany->clear();
        telephone->clear();
        adresse->clear();
        email->clear();
        modelTableFournisseur->select();
    }else
        qDebug() << " No Insertion of a new 'Fournisseur'" ;
}




void Fournisseur::setTabListFournisseur(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    vbox->addSpacing(0);
    vbox->setMargin(0);

    modelTableFournisseur = new QSqlTableModel;
    modelTableFournisseur->setTable("Fournisseurs");
    modelTableFournisseur->select();

    QTableView *tableFournisseur = new QTableView;
    tableFournisseur->setModel(modelTableFournisseur);
    tableFournisseur->setAlternatingRowColors(true);
    tableFournisseur->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableFournisseur->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableFournisseur->setMinimumWidth(200);
    tableFournisseur->setColumnWidth(0,50);
    vbox->addWidget(tableFournisseur);

    connect(tableFournisseur,SIGNAL(clicked(QModelIndex)),this,SLOT(onClickedTableFournisseur(QModelIndex)));
}

void Fournisseur::setTabInfoFournisseur(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    w->setObjectName("wInfoFournisseur");
    w->setStyleSheet("#wInfoFournisseur{background-color:lightgray;}");

    QHBoxLayout *hboxTitle = new QHBoxLayout;
    vbox->addLayout(hboxTitle);

    QLabel *title = new QLabel("Information sur le fournisseur:");
    title->setFont(QFont("Datum",10,QFont::Bold,false));
    hboxTitle->addWidget(title);

    DPushButton *addFournisseur = new DPushButton("Ajouter un fournisseur");
    addFournisseur->setMaximumWidth(200);
    hboxTitle->addWidget(addFournisseur);

    QWidget *Hline = new QWidget;
    Hline->setObjectName("Hline");
    Hline->setStyleSheet("#Hline{background-color:black;}");
    Hline->setMinimumHeight(3);
    vbox->addWidget(Hline);

    QGridLayout *grid = new QGridLayout;
    vbox->addLayout(grid);

    formInfo1 = new QFormLayout;
    formInfo1->setSpacing(15);
    grid->addLayout(formInfo1,0,0);


    formInfo1->addRow("ID",&fournisseurInfo.id);
    formInfo1->addRow("Company",&fournisseurInfo.company);
    formInfo1->addRow("Nom",&fournisseurInfo.nom);
    formInfo1->addRow("Prenom",&fournisseurInfo.prenom);
    formInfo1->addRow("Sexe",&fournisseurInfo.sexe);
    formInfo1->addRow("Adresse",&fournisseurInfo.adresse);
    formInfo1->addRow("Phone",&fournisseurInfo.phone);
    formInfo1->addRow("E-Mail",&fournisseurInfo.email);


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


    modelProduitTransaction = new QSqlRelationalTableModel;
    modelProduitTransaction->setTable("ProduitInvestment");
    modelProduitTransaction->setRelation(2,QSqlRelation("Produits","ID","Nom"));
    modelProduitTransaction->setRelation(5,QSqlRelation("Fournisseurs","ID","NomCompany"));
    modelProduitTransaction->setHeaderData(6,Qt::Horizontal,"Date");
    modelProduitTransaction->select();


    QTableView *tableProduitTransaction = new QTableView;
    tableProduitTransaction->setModel(modelProduitTransaction);
    tableProduitTransaction->setMinimumWidth(900);
    tableProduitTransaction->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableProduitTransaction->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableProduitTransaction->setAlternatingRowColors(true);
    vbox->addWidget(tableProduitTransaction);
    //--------------------------------------------------------------------------------

    connect(addFournisseur,SIGNAL(clicked()),this,SLOT(onClickedAddFournisseur()));

}


void Fournisseur::onClickedTableFournisseur(QModelIndex idx)
{
    int row = idx.row();
    QString id = modelTableFournisseur->data(modelTableFournisseur->index(row,0),Qt::EditRole).toString();
    QString nomComp = modelTableFournisseur->data(modelTableFournisseur->index(row,4),Qt::EditRole).toString();

    query.prepare("SELECT * FROM Fournisseurs WHERE ID= "+id);
    if(query.exec())
    {
        if(query.next())
        {
            fournisseurInfo.id.setText(query.value(0).toString());
            fournisseurInfo.company.setText(query.value(4).toString());
            fournisseurInfo.nom.setText(query.value(1).toString());
            fournisseurInfo.prenom.setText(query.value(2).toString());
            fournisseurInfo.sexe.setText(query.value(3).toString());
            fournisseurInfo.adresse.setText(query.value(5).toString());
            fournisseurInfo.phone.setText(query.value(6).toString());
            fournisseurInfo.email.setText(query.value(7).toString());

            modelProduitTransaction->setFilter("NomCompany = '"+nomComp+"' ");
        }

    }
}

QDate Fournisseur::getCr_dateFournisseur() const
{
    return cr_dateFournisseur;
}

QString Fournisseur::getEmailFournisseur() const
{
    return emailFournisseur;
}

QString Fournisseur::getNomCompanyFournisseur() const
{
    return nomCompanyFournisseur;
}

QString Fournisseur::getTelephoneFournisseur() const
{
    return telephoneFournisseur;
}

QString Fournisseur::getAdresseFournisseur() const
{
    return adresseFournisseur;
}

QString Fournisseur::getSexeFournisseur() const
{
    return sexeFournisseur;
}

QString Fournisseur::getPrenomFournisseur() const
{
    return prenomFournisseur;
}

QString Fournisseur::getNomFournisseur() const
{
    return nomFournisseur;
}

int Fournisseur::getIdFournisseur() const
{
    return idFournisseur;
}
