#include "produit.h"
#include "produitinvestments.h"
#include "produittransaction.h"

Produit::Produit(QWidget *parent) : QWidget(parent)
{

}

QDate Produit::getCreateDateProduit() const
{
    return createDateProduit;
}

int Produit::getIdFournisseurProduit() const
{
    return idFournisseurProduit;
}

double Produit::getPrixVenteProduit() const
{
    return prixVenteProduit;
}

double Produit::getPrixAchatProduit() const
{
    return prixAchatProduit;
}

QString Produit::getSizeProduit() const
{
    return sizeProduit;
}

QString Produit::getAttributeProduit() const
{
    return attributeProduit;
}

QString Produit::getDescriptionProduit() const
{
    return descriptionProduit;
}

QString Produit::getNomProduit() const
{
    return nomProduit;
}

int Produit::getIdProduit() const
{
    return idProduit;
}

double Produit::getPriceAchatItemByName(const QString itemName) const
{
    double pAchat = 0.0;

    if(priceAchatItemByName.contains(itemName))
        pAchat = priceAchatItemByName.value(itemName);
    return pAchat;
}

int Produit::getIdItemByName(const QString itemName) const
{
    int idItem = -1;
    if(idItemByName.contains(itemName))
        idItem = idItemByName.value(itemName);

    return idItem;
}

void Produit::fetchProduitByName(QString produitName)
{
    query.prepare("SELECT * FROM Produits WHERE Nom = '"+produitName+"' ");
    if(query.exec()){
        if(query.next()){
            this->idProduit = query.value(0).toInt();
            this->nomProduit = query.value(1).toString();
            this->descriptionProduit = query.value(2).toString();
            this->attributeProduit = query.value(3).toString();
            this->sizeProduit = query.value(4).toString();
            this->qteEnStockProduit = query.value(5).toDouble();
            this->prixAchatProduit = query.value(6).toDouble();
            this->prixVenteProduit = query.value(7).toDouble();
            this->createDateProduit = query.value(8).toDate();
            this->idFournisseurProduit = query.value(9).toInt();
        }
    }

    query.finish();
}

DDoubleSpinBox *Produit::getPrixVente() const
{
    return prixVente;
}

void Produit::setPrixVente(DDoubleSpinBox *value)
{
    prixVente = value;
}

int Produit::getIdByValue(int column, QString val)
{
    int id = -1;
    query.prepare("SELECT * FROM Produits");
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

DDoubleSpinBox *Produit::getPrixAchat() const
{
    return prixAchat;
}

void Produit::setPrixAchat(DDoubleSpinBox *value)
{
    prixAchat = value;
}

//-------------------------------------------------------------------------------------------------------
//---------------------------------------------------------Constructor 2---------------------------------
//-------------------------------------------------------------------------------------------------------

Produit::Produit(QSqlQuery q)
{

    query = q;
    fournisseurs = new Fournisseur;

    QGridLayout *grid = new QGridLayout;
    this->setLayout(grid);

    stackPage = new QStackedWidget;
    stackPage->setObjectName("stackPage");
    stackPage->setStyleSheet("#stackPage{background-color:#B0C4DE;}");
    grid->addWidget(stackPage,0,0,4,1);

    ProduitTransaction *transactionTab = new ProduitTransaction(query);
    stackPage->addWidget(transactionTab);

    QWidget *addProduitTab = new QWidget;
    setTabAddProduit(addProduitTab);
    stackPage->addWidget(addProduitTab);

    QWidget *listProduitTab = new QWidget;
    setTabListProduit(listProduitTab);
    stackPage->addWidget(listProduitTab);

    ProduitInvestments *produitTab = new ProduitInvestments(query);
    stackPage->addWidget(produitTab);

    listAchatTab = new Investments(query);
    stackPage->addWidget(listAchatTab);

    QWidget *listVenteTab = new QWidget;
    setTabListVente(listVenteTab);
    stackPage->addWidget(listVenteTab);

    QWidget *historyProduitTab = new QWidget;
    setTabHistoryProduit(historyProduitTab);
    stackPage->addWidget(historyProduitTab);


    QVBoxLayout *vbox = new QVBoxLayout;
    grid->addLayout(vbox,0,1);

    DPushButton *bte_transaction = new DPushButton("Transaction");
    vbox->addWidget(bte_transaction);

    DPushButton *bte_listVente = new DPushButton("Liste des ventes");
    vbox->addWidget(bte_listVente);

    DPushButton *bte_historicite = new DPushButton("Historicité");
    vbox->addWidget(bte_historicite);

    //-----------------------------------------------------
    QWidget *Hline0 = new QWidget;
    Hline0->setObjectName("Hline0");
    Hline0->setStyleSheet("#Hline0{background-color:black;}");
    Hline0->setMinimumHeight(4);
    vbox->addWidget(Hline0);
    //-----------------------------------------------------

    DPushButton *bte_addItem = new DPushButton("Ajouter un nouveau\nproduit");
    vbox->addWidget(bte_addItem);

    DPushButton *bte_listItem = new DPushButton("Liste des produits");
    vbox->addWidget(bte_listItem);


    //-----------------------------------------------------
    QWidget *Hline = new QWidget;
    Hline->setObjectName("Hline");
    Hline->setStyleSheet("#Hline{background-color:black;}");
    Hline->setMinimumHeight(4);
    vbox->addWidget(Hline);
    //-----------------------------------------------------


    DPushButton *bte_Produit = new DPushButton("Achat de produit");
    vbox->addWidget(bte_Produit);

    DPushButton *bte_listAchat = new DPushButton("Liste des achats");
    vbox->addWidget(bte_listAchat);



    connect(bte_transaction,SIGNAL(clicked()),this,SLOT(onClickTransaction()));
    connect(bte_addItem,SIGNAL(clicked()),this,SLOT(onClickAddItem()));
    connect(bte_listItem,SIGNAL(clicked()),this,SLOT(onClickListItem()));
    connect(bte_listVente,SIGNAL(clicked()),this,SLOT(onClickListVente()));
    connect(bte_historicite,SIGNAL(clicked()),this,SLOT(onClickHistoricite()));
    connect(bte_Produit,SIGNAL(clicked()),this,SLOT(onClickProduit()));
    connect(bte_listAchat,SIGNAL(clicked()),this,SLOT(onClickListAchat()));
}

void Produit::generalRefreshModels()
{
    modelTableProduit->select();

    modelTableVente->select();


    modelHistoryProduit->select();
    listAchatTab->refreshModels();

}

void Produit::onClickAddItem()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(1);
}

void Produit::onClickProduit()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(3);
}

void Produit::onClickListAchat()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(4);
}

void Produit::onClickTransaction()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(0);
}

void Produit::onClickListItem()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(2);
}

void Produit::onClickListVente()
{
    generalRefreshModels();
    ajusterAffichage();
    stackPage->setCurrentIndex(5);
}

void Produit::onClickHistoricite()
{
    generalRefreshModels();
    stackPage->setCurrentIndex(6);
}



void Produit::initializeHashList()
{
    query.prepare("SELECT * FROM Produits");
    if(query.exec())
        while(query.next()){
            idItemByName.insert(query.value(1).toString(),query.value(0).toInt());
            priceAchatItemByName.insert(query.value(1).toString(),query.value(5).toDouble());
        }
}

void Produit::setTabAddProduit(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);

    DGroupBox *groupItemDetail = new DGroupBox("Information sur le produit");
    vbox->addWidget(groupItemDetail);

    QGridLayout *gridDetails = new QGridLayout;
    groupItemDetail->setBodyLayout(gridDetails);

    nom = new DLineEdit("Nom");
    gridDetails->addWidget(nom,0,0);

    attribute = new DLineEdit("Attribute");
    gridDetails->addWidget(attribute,0,1);

    size = new DLineEdit("Size");
    gridDetails->addWidget(size,1,0);

    createDate = new DDateEdit("Date de creation");
    createDate->setCalendarPopup(true);
    createDate->setCurrentDate();
    gridDetails->addWidget(createDate,1,1);

    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT NomCompany FROM Fournisseurs");
    QCompleter *completer = new QCompleter;
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(queryModel);
    idFournisseur = new DLineEdit("Nom du fournisseur");
    idFournisseur->setCompleter(completer);
    gridDetails->addWidget(idFournisseur,2,0,1,2);

    description = new DTextEdit("Description du produit");
    gridDetails->addWidget(description,3,0,1,2);

    //------------------------------------------------------------
    DGroupBox *groupPAV = new DGroupBox("Prix achat et vente");
    vbox->addWidget(groupPAV);

    QGridLayout *gridPAV = new QGridLayout;
    groupPAV->setBodyLayout(gridPAV);

    prixAchat = new DDoubleSpinBox("Prix d'achat - HTG");
    prixAchat->setMaximum(999999.99);
    gridPAV->addWidget(prixAchat,0,0);

    prixVente = new DDoubleSpinBox("Prix de vente - HTG");
    prixVente->setMaximum(999999.99);
    gridPAV->addWidget(prixVente,0,1);

    DPushButton *addProduit = new DPushButton("Ajouter");
    vbox->addWidget(addProduit);

    connect(addProduit,SIGNAL(clicked()),this,SLOT(onClickedAddToDB()));
}


void Produit::onClickedAddToDB()
{
    query.prepare("INSERT INTO Produits (Nom,Description,Attribute,Size,PrixAchat,PrixVente,cr_Date,idFournisseur)"
                  "VALUES (:nom,:description,:attribute,:size,:prixachat,:prixvente,:cr_date,:idfournisseur)");

    query.bindValue(":nom",nom->text());
    query.bindValue(":description",description->toPlainText());
    query.bindValue(":attribute",attribute->text());
    query.bindValue(":size",size->text());
    query.bindValue(":prixachat",prixAchat->value());
    query.bindValue(":prixvente",prixVente->value());
    query.bindValue(":cr_date",createDate->date());

    int idfourn = fournisseurs->getIdByValue(4,idFournisseur->text());
    query.bindValue(":idfournisseur",idfourn);

    if(query.exec()){
        qDebug() << "Insertion of a new 'Produit'";
        nom->clear();
        description->clear();
        attribute->clear();
        size->clear();
        prixAchat->setValue(0.0);
        prixVente->setValue(0.0);
        modelTableProduit->select();
    }else{
        qDebug() << " No Insertion of a new 'Produit'";
        qDebug() << query.lastError();
    }
}



void Produit::setTabListProduit(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);

    modelTableProduit = new QSqlRelationalTableModel;
    modelTableProduit->setTable("Produits");
    modelTableProduit->setRelation(9,QSqlRelation("Fournisseurs","ID","NomCompany"));
    modelTableProduit->select();


    QTableView *tableProduit = new QTableView;
    tableProduit->setModel(modelTableProduit);
    tableProduit->setAlternatingRowColors(true);
    tableProduit->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableProduit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vbox->addWidget(tableProduit);

    connect(tableProduit,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onDoubleClickModifiedItem(QModelIndex)));
}

void Produit::onDoubleClickModifiedItem(QModelIndex idx)
{

    int row = idx.row();
    QString id = modelTableProduit->index(row,0,QModelIndex()).data().toString();

    QDialog *diag = new QDialog;
    diag->setModal(true);
    diag->setWindowTitle("Modifier l'article");
    diag->setMinimumWidth(400);

    QVBoxLayout *vbox = new QVBoxLayout;
    diag->setLayout(vbox);

    idItem = new DLabel("ID");
    idItem->setText(id);
    vbox->addWidget(idItem);

    DLabel *nomItem = new DLabel("Nom:");
    nomItem->setText(modelTableProduit->index(row,1,QModelIndex()).data().toString());
    vbox->addWidget(nomItem);

    DLabel *descriptionItem = new DLabel("Description:");
    descriptionItem->setText(modelTableProduit->index(row,2,QModelIndex()).data().toString());
    vbox->addWidget(descriptionItem);

    DLabel *attributeItem = new DLabel("Attribute:");
    attributeItem->setText(modelTableProduit->index(row,3,QModelIndex()).data().toString());
    vbox->addWidget(attributeItem);

    DLabel *sizeItem = new DLabel("Size:");
    sizeItem->setText(modelTableProduit->index(row,4,QModelIndex()).data().toString());
    vbox->addWidget(sizeItem);

    DLabel *qteStockItem = new DLabel("Quantite en stock:");
    qteStockItem->setText(modelTableProduit->index(row,5,QModelIndex()).data().toString());
    vbox->addWidget(qteStockItem);

    prixAchatItem = new DDoubleSpinBox("Prix d'achat");
    prixAchatItem->setMaximum(999999.99);
    prixAchatItem->setValue(modelTableProduit->index(row,6,QModelIndex()).data().toDouble());
    vbox->addWidget(prixAchatItem);

    prixVenteItem = new DDoubleSpinBox("Prix de vente");
    prixVenteItem->setMaximum(999999.99);
    prixVenteItem->setValue(modelTableProduit->index(row,7,QModelIndex()).data().toDouble());
    vbox->addWidget(prixVenteItem);

    DPushButton *modifierbte = new DPushButton("Modifier");
    vbox->addWidget(modifierbte);

    diag->show();

    connect(modifierbte,SIGNAL(clicked()),this,SLOT(onCickedModifier()));
}

void Produit::onCickedModifier()
{
    query.prepare("UPDATE Produits SET PrixAchat = :pA, PrixVente = :pV WHERE ID = :id");

    query.bindValue(":pA",prixAchatItem->value());
    query.bindValue(":pV",prixVenteItem->value());
    query.bindValue(":id",idItem->text().toInt());

    if(query.exec())
    {
        prixAchatItem->setValue(0.00);
        prixVenteItem->setValue(0.00);

        modelTableProduit->select();
    }else
        qDebug()<<"Produit not update: "<<query.lastError();
}

void Produit::setTabListVente(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);

    modelTableVente = new QSqlRelationalTableModel;
    modelTableVente->setTable("Sales_Transaction");
    modelTableVente->select();

    tableVente = new QTableView;
    tableVente->setModel(modelTableVente);
    tableVente->setAlternatingRowColors(true);
    tableVente->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableVente->setContextMenuPolicy(Qt::CustomContextMenu);
    tableVente->setItemDelegate(new ListVenteDelegate);
    vbox->addWidget(tableVente);

    QHBoxLayout *hbox = new QHBoxLayout;
    vbox->addLayout(hbox);

    qteVente_lab = new DLabel("Quantite total des ventes");
    hbox->addWidget(qteVente_lab);

    totVente_lab = new DLabel("Prix total des ventes");
    hbox->addWidget(totVente_lab);

    benefice_lab = new DLabel("Benefice brut");
    hbox->addWidget(benefice_lab);

    ajusterAffichage();
    connect(tableVente,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenu(QPoint)));
    connect(tableVente,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showDiagCreditSale(QModelIndex)));

}

void Produit::showDiagCreditSale(QModelIndex idx)
{
    int row = idx.row();
    QString payment = modelTableVente->index(row,6,QModelIndex()).data().toString();
    int retourVente =  modelTableVente->index(row,7,QModelIndex()).data().toInt();
    totVenteSalesTransac = modelTableVente->index(row,5,QModelIndex()).data().toDouble();
    if(payment=="Credit" && retourVente==0)
    {
        QDialog *diag = new QDialog;
        diag->setWindowTitle("Versement du credit");
        diag->setMinimumWidth(600);
        diag->setModal(true);

        QGridLayout *grid = new QGridLayout;
        diag->setLayout(grid);

        idST_label = new DLabel("ID");
        idST_label->setText(modelTableVente->index(row,0,QModelIndex()).data().toString());
        grid->addWidget(idST_label,0,0);

        DLabel *nomST_label = new DLabel("Nom Complet");
        nomST_label->setText(modelTableVente->index(row,3,QModelIndex()).data().toString());
        grid->addWidget(nomST_label,1,0);

        dateVersST = new DDateEdit("Date");
        dateVersST->setCalendarPopup(true);
        dateVersST->setCurrentDate();
        grid->addWidget(dateVersST,0,2);

        descripVersST = new DLineEdit("Description");
        grid->addWidget(descripVersST,0,3);

        doubleVersementST = new DDoubleSpinBox("Montant du versement");
        doubleVersementST->setMaximum(999999.99);
        grid->addWidget(doubleVersementST,1,2);

        DPushButton *validST = new DPushButton("Valider");
        grid->addWidget(validST,1,3);

        modeltableVersementCVente = new QSqlTableModel;
        modeltableVersementCVente->setTable("Versement_CreditST");
        modeltableVersementCVente->select();
        modeltableVersementCVente->setFilter("id_ST = "+idST_label->text());

        QTableView *tableVersementCVente = new QTableView;
        tableVersementCVente->setModel(modeltableVersementCVente);
        tableVersementCVente->setAlternatingRowColors(true);
        tableVersementCVente->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableVersementCVente->setEditTriggers(QAbstractItemView::NoEditTriggers);
        grid->addWidget(tableVersementCVente,2,0,1,4);

        DLabel *totVenteST_label = new DLabel("Total Vente");
        totVenteST_label->setTextFromDouble(totVenteSalesTransac);
        grid->addWidget(totVenteST_label,3,0);

        totVersementST_label = new DLabel("Total versement");
        grid->addWidget(totVersementST_label,3,1);

        balancetST_label = new DLabel("Balance");
        grid->addWidget(balancetST_label,3,2);

        query.prepare("SELECT SUM(MontantVerse) FROM Versement_CreditST "
                      "WHERE id_ST = "+modelTableVente->index(row,0,QModelIndex()).data().toString());
        if(query.exec())
            if(query.first())
            {
                totVersementST_label->setTextFromDouble(query.value(0).toDouble());
                balancetST_label->setTextFromDouble(totVenteSalesTransac-query.value(0).toDouble());
            }

        diag->show();
        connect(validST,SIGNAL(clicked()),this,SLOT(addVersementCreditST()));
    }
}

void Produit::addVersementCreditST()
{
    if(doubleVersementST->value()<=0)
        return;
    if(descripVersST->text().isEmpty())
        return;

    query.prepare("INSERT INTO Versement_CreditST (dateVersement,Description,MontantVerse,id_ST)"
                  "VALUES (:dateVers,:descrip,:mtntVers,:id)");
    query.bindValue(":dateVers",dateVersST->date());
    query.bindValue(":descrip",descripVersST->text());
    query.bindValue(":mtntVers",doubleVersementST->value());
    query.bindValue(":id",idST_label->text().toInt());

    if(query.exec())
    {
        descripVersST->clear();
        doubleVersementST->setValue(0);
        modeltableVersementCVente->setFilter("id_ST = "+idST_label->text());
        query.prepare("SELECT SUM(MontantVerse) FROM Versement_CreditST "
                      "WHERE id_ST = "+idST_label->text());
        if(query.exec())
            if(query.first())
            {
                totVersementST_label->setTextFromDouble(query.value(0).toDouble());
                balancetST_label->setTextFromDouble(totVenteSalesTransac-query.value(0).toDouble());
            }
    }

}

void Produit::showContextMenu(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("Retourner la vente"),this);
    contextMenu.addAction(&action);

    connect(&action,SIGNAL(triggered()),this,SLOT(retournerVente()));
    contextMenu.exec(QCursor::pos());
}

void Produit::retournerVente()
{
    int row = tableVente->selectionModel()->currentIndex().row();
    QString id = modelTableVente->index(row,0).data().toString();

    query.prepare("UPDATE Sales_Transaction SET Return = 1 WHERE ID = "+id);
    if(query.exec()){
        qDebug()<<"Return has been update";
        modelTableVente->select();
        ajusterAffichage();
        ajusterQteEnStock(id.toInt());
    }else
        qDebug()<<"Return has not been update: "<<query.lastError();
}


void Produit::ajusterAffichage()
{
    query.prepare("SELECT SUM(Qte),"
                  "SUM(Total),"
                  "(SELECT SUM([Quantite achat]*PrixAchat) FROM ProduitInvestment)"
                  "FROM Sales_Transaction WHERE Return=0");
    if(query.exec()){
        if(query.first()){
            qteVente_lab->setTextFromDouble(query.value(0).toDouble());
            totVente_lab->setPriceTextFromDouble("HTG",query.value(1).toDouble());
            benefice_lab->setPriceTextFromDouble("HTG",query.value(1).toDouble()-query.value(2).toDouble());
        }
    }else
        qDebug()<<"Affichage not selected: "<<query.lastError();

}

void Produit::ajusterQteEnStock(int id)
{
    QList<QString>listID;
    QList<double>listQty;
    query.prepare("SELECT idProduit,Qte FROM Sales_Details WHERE idSales_T = "+QString::number(id));
    if(query.exec()){
        qDebug()<<"Ajuster qty en stock";
        while(query.next())
        {
            listID.append(query.value(0).toString());
            listQty.append(query.value(1).toDouble());
        }

        for(int i=0;i<listID.size();++i){
            query.prepare("UPDATE Produits SET [Qantite en stock] = "
                          "[Qantite en stock]+:qteReturn WHERE ID = "+listID.at(i));
            query.bindValue(":qteReturn",listQty.at(i));
            if(query.exec()){
                qDebug()<<"Qty: "<<listQty.at(i)<<" ID: "<<listID.at(i);
            }

            #ifdef Q_OS_WIN
                Sleep(uint(100));
            #endif
        }

    }else
        qDebug()<<"Not ajuster qty en stock";


}





double Produit::getQteEnStockProduit() const
{
    return qteEnStockProduit;
}

void Produit::setTabHistoryProduit(QWidget *w)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);


    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT Nom FROM Produits");
    QCompleter *completer = new QCompleter;
    completer->setModel(queryModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    searchProdHistory = new DLineEdit("Rechercher un produit:");
    searchProdHistory->setCompleter(completer);
    vbox->addWidget(searchProdHistory);

    modelHistoryProduit = new QSqlRelationalTableModel;
    modelHistoryProduit->setTable("Sales_Details");
    modelHistoryProduit->setRelation(6,QSqlRelation("Sales_Transaction","ID","Date"));
    modelHistoryProduit->setHeaderData(1,Qt::Horizontal,"#Produit");
    modelHistoryProduit->select();

    QTableView *tableHistoryProduit = new QTableView;
    tableHistoryProduit->setModel(modelHistoryProduit);
    tableHistoryProduit->setAlternatingRowColors(true);
    tableHistoryProduit->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableHistoryProduit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableHistoryProduit->setColumnWidth(2,250);
    vbox->addWidget(tableHistoryProduit);

    QHBoxLayout *hbox = new QHBoxLayout;
    vbox->addLayout(hbox);

    qtyTotalVente_lab = new DLabel("Quantite total des ventes:");
    hbox->addWidget(qtyTotalVente_lab);

    prixTotalAchat_lab = new DLabel("Prix total des achats:");
    hbox->addWidget(prixTotalAchat_lab);

    prixTotalVente_lab = new DLabel("Prix total des ventes:");
    hbox->addWidget(prixTotalVente_lab);

    beneficeVente_lab = new DLabel("Profit:");
    hbox->addWidget(beneficeVente_lab);

    QLineEdit *searchProdHistory_Q = searchProdHistory->getLineEdit();
    connect(searchProdHistory_Q,SIGNAL(returnPressed()),this,SLOT(onPressedSearchHistory()));
    connect(tableHistoryProduit,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onDoubleClickTableHist(QModelIndex)));
}

void Produit::onDoubleClickTableHist(QModelIndex idx)
{
    int row = idx.row();
    IDSALES_DETAILS = -1;
    QString id = modelHistoryProduit->index(row,0).data().toString();
    IDSALES_DETAILS = modelHistoryProduit->index(row,0).data().toInt();
    qDebug()<<id;

    diagPrixAchat = new QDialog;
    diagPrixAchat->setModal(true);
    diagPrixAchat->setMinimumWidth(200);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagPrixAchat->setLayout(vbox);

    DLabel *idRow = new DLabel("ID ");
    idRow->setText(id);
    vbox->addWidget(idRow);

    DLabel *idProduit = new DLabel("ID PRODUIT");
    idProduit->setText(modelHistoryProduit->index(row,1).data().toString());
    vbox->addWidget(idProduit);

    DLabel *nomProduit = new DLabel("NOM PRODUIT: ");
    nomProduit->setText(modelHistoryProduit->index(row,2).data().toString());
    vbox->addWidget(nomProduit);

    prixAchatChange_spin = new DDoubleSpinBox("Prix achat");
    prixAchatChange_spin->setMaximum(9999999);
    prixAchatChange_spin->setValue(modelHistoryProduit->index(row,4).data().toDouble());
    vbox->addWidget(prixAchatChange_spin);

    DPushButton *boutonChange = new DPushButton("Modifier");
    vbox->addWidget(boutonChange);

    connect(boutonChange,SIGNAL(clicked()),this,SLOT(onClickChangePrixAchat()));

    diagPrixAchat->show();
}


void Produit::onClickChangePrixAchat()
{
    if(IDSALES_DETAILS==-1)
        return;

    query.prepare("UPDATE Sales_Details SET PrixAchat = :pA WHERE ID = :id");
    query.bindValue(":id",IDSALES_DETAILS);
    query.bindValue(":pA",prixAchatChange_spin->value());

    if(query.exec())
    {
        qDebug()<<"Prix achat was update";
        diagPrixAchat->close();
        modelHistoryProduit->select();
        if(!searchProdHistory->text().isEmpty())
            onPressedSearchHistory();
    }else
        qDebug()<<"Prix achat was not update: "<<query.lastError();

}


void Produit::onPressedSearchHistory()
{
    modelHistoryProduit->setFilter("[Nom Produit] = '"+searchProdHistory->text()+"' ");

    query.prepare(" SELECT SUM(Qte),SUM(Qte*PrixAchat),SUM(Qte*PrixVente) FROM Sales_Details "
                  " WHERE [Nom Produit] = '"+searchProdHistory->text()+"' ");
    if(query.exec())
        if(query.first())
        {
            qtyTotalVente_lab->setTextFromDouble(query.value(0).toDouble());
            prixTotalAchat_lab->setTextFromDouble(query.value(1).toDouble());
            prixTotalVente_lab->setTextFromDouble(query.value(2).toDouble());
            beneficeVente_lab->setTextFromDouble(query.value(2).toDouble()-query.value(1).toDouble());
        }


}
