#include "investments.h"
#include "produit.h"

Investments::Investments(QWidget *parent) : QWidget(parent)
{

}

Investments::Investments(QSqlQuery q)
{
    query = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QTabWidget *tabWid = new QTabWidget;
    vbox->addWidget(tabWid);

    QWidget *listInvestmentTab = new QWidget;
    setTabListeInvestment(listInvestmentTab);
    tabWid->addTab(listInvestmentTab,"Liste des investissements de produit");

    creditInvestmentPage = new CreditInvestment(query);
    tabWid->addTab(creditInvestmentPage,"Gestion des credits d'investissements");

    connect(tabWid,SIGNAL(tabBarClicked(int)),this,SLOT(onClickedTabBar()));

}

void Investments::onClickedTabBar()
{
    creditInvestmentPage->selectModelCredit();
    modelInvestment->select();
}


void Investments::refreshModels()
{
    modelInvestment->select();
}



void Investments::setTabListeInvestment(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    modelInvestment = new QSqlRelationalTableModel;
    modelInvestment->setTable("ProduitInvestment");
    modelInvestment->setRelation(2,QSqlRelation("Produits","ID","Nom"));
    modelInvestment->setRelation(5,QSqlRelation("Fournisseurs","ID","NomCompany"));
    modelInvestment->setHeaderData(6,Qt::Horizontal,"Date");
    modelInvestment->select();

    tableInvestment = new QTableView;
    tableInvestment->setModel(modelInvestment);
    tableInvestment->setColumnWidth(4,300);
    tableInvestment->setAlternatingRowColors(true);
    tableInvestment->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableInvestment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableInvestment->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableInvestment,0,0,1,4);

    totQty_lab = new DLabel("Nombre d'achat total");
    grid->addWidget(totQty_lab,1,0);

    totAchat_lab = new DLabel("Prix total d'achat");
    grid->addWidget(totAchat_lab,1,1);

    ajusterAffichage();

    //connect(tableInvestment,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onDoubleClickedTableInvest(QModelIndex)));
    connect(tableInvestment,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenuInvestment(QPoint)));
}

void Investments::ajusterAffichage()
{
    query.prepare("SELECT SUM([Quantite achat]),SUM([Quantite achat]*PrixAchat) FROM ProduitInvestment");
    if(query.exec()){
        if(query.first()){
            totQty_lab->setTextFromDouble(query.value(0).toDouble());
            totAchat_lab->setPriceTextFromDouble("HTG",query.value(1).toDouble());
        }
    }else
        qDebug()<<"Affichage not selected: "<<query.lastError();


}


void Investments::showContextMenuInvestment(QPoint)
{
    //Q_UNUSED(p);

    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer l'investissement"),this);

    contextMenu.addAction(&action);
    connect(&action,SIGNAL(triggered()),this,SLOT(effacerInvestment()));
    contextMenu.exec(QCursor::pos());
}



void Investments::effacerInvestment()
{
    int row = tableInvestment->selectionModel()->currentIndex().row();
    QString id = modelInvestment->index(row,0).data().toString();
    int checkId=modelInvestment->index(row,7).data().toInt();

    Produit *produitInstance = new Produit;
    produitInstance->fetchProduitByName(modelInvestment->index(row,2).data().toString());
    double idProduit = produitInstance->getIdProduit();
    double qteEnStock = produitInstance->getQteEnStockProduit();
    double qteProduitInvest = modelInvestment->index(row,1).data().toDouble();

    if(checkId){
        QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Transaction: Debiter",\
                                        "Cet investissement est deja dans la liste des credits, "
                                        "il peut contenir des transactions deja effectuees. "
                                        "Voulez-vous vraiment le supprimer?",\
                                        QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
        if(resBtn == QMessageBox::Yes)
        {
            updateQteProduitEnStock(qteEnStock,qteProduitInvest,idProduit);
            query.prepare("DELETE FROM ProduitInvestment WHERE ID = "+id);
            if(query.exec()){
                qDebug()<<"ProduitInvestment was delete";
                ajusterAffichage();
                modelInvestment->select();
            }else
                qDebug()<<"ProduitInvestment was not delete: "<<query.lastError();
        }

    }else{
        updateQteProduitEnStock(qteEnStock,qteProduitInvest,idProduit);
        query.prepare("DELETE FROM ProduitInvestment WHERE ID = "+id);
        if(query.exec())
        {
            qDebug()<<"ProduitInvestment was delete";
            ajusterAffichage();
            modelInvestment->select();
        }else
            qDebug()<<"ProduitInvestment was not delete: "<<query.lastError();
    }


}



void Investments::updateQteProduitEnStock(double qteEnStock, double qteInvestment, int idProduit)
{
    qDebug()<<qteEnStock<<endl<<qteInvestment<<endl<<idProduit;

    query.prepare("UPDATE Produits SET [Qantite en stock] = :qte WHERE ID = :idd");
    query.bindValue(":qte",qteEnStock-qteInvestment);
    query.bindValue(":idd",idProduit);
    if(query.exec())
        qDebug()<<"Quantite en stock ajuster ";
    else
        qDebug()<<"Quantite en stock non ajuster: "<<query.lastError();
}

void Investments::onDoubleClickedTableInvest(QModelIndex idx)
{
    //int row = tableInvestment->selectionModel()->currentIndex().row();

    diagCredit = new QDialog;
    diagCredit->setWindowTitle("Configurer le statut de l'investissement");
    diagCredit->setModal(true);
    diagCredit->setMinimumWidth(300);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagCredit->setLayout(vbox);

    dateCredit = new DDateEdit("Date du credit");
    dateCredit->setCalendarPopup(true);
    dateCredit->setCurrentDate();
    vbox->addWidget(dateCredit);

    QString id = modelInvestment->index(idx.row(),0).data().toString();
    idInvestment = new DLabel("Id de l'investissement");
    idInvestment->setText(id);
    vbox->addWidget(idInvestment);

    QString desc = modelInvestment->index(idx.row(),4).data().toString();
    DLabel *descript = new DLabel("Description");
    descript->setText(desc);
    vbox->addWidget(descript);

    typePayer = new QComboBox;
    typePayer->addItem("Cash");
    typePayer->addItem("Credit");
    typePayer->setMinimumHeight(30);
    vbox->addWidget(typePayer);

    qte = modelInvestment->index(idx.row(),1).data().toDouble();
    totAchat = modelInvestment->index(idx.row(),3).data().toDouble();

    DPushButton *ajustCredit = new DPushButton("Ajouter dans la liste des credits");
    vbox->addWidget(ajustCredit);

    diagCredit->show();

    connect(ajustCredit,SIGNAL(clicked()),this,SLOT(onClickedAddCredit()));
}



void Investments::onClickedAddCredit()
{
    query.prepare("UPDATE ProduitInvestment SET Statut = :statut WHERE ID = "+idInvestment->text());
    query.bindValue(":statut",typePayer->currentIndex());
    if(query.exec()){
        qDebug()<<"ProduitInvestment statut changed";
        modelInvestment->select();
        query.finish();
    }else
        qDebug()<<"ProduitInvestment statut not changed"<<query.lastError();


    if(typePayer->currentIndex()==1){
        query.prepare("INSERT INTO CreditInvestment (cr_Date,id_PI,MontantDu)"
                      "VALUES (:crDate,:id_pi,:mtntDu)");
        query.bindValue(":crDate",dateCredit->date());
        query.bindValue(":id_pi",idInvestment->text().toInt());
        query.bindValue(":mtntDu",qte*totAchat);


        if(query.exec()){
            query.finish();
            diagCredit->close();
        }else
            qDebug()<<"CreditInvestment not insert"<<query.lastError();
    }


}



