#include "produitinvestments.h"

ProduitInvestments::ProduitInvestments(QWidget *parent)
    : QWidget(parent)
{

}

ProduitInvestments::ProduitInvestments(QSqlQuery q)
{
    query = q;
    produitInstance = new Produit;
    fournisseurInstance = new Fournisseur;
    //produitInstance->initializeHashList();

    QHBoxLayout *hLayout = new QHBoxLayout;
    this->setLayout(hLayout);

    QScrollArea *scroll = new QScrollArea;
    //scroll->setBackgroundRole(QPalette::Dark);
    hLayout->addWidget(scroll);

    QWidget *widScroll = new QWidget;
    widScroll->setObjectName("widScroll");
    widScroll->setStyleSheet("#widScroll{background-color:white;}");
    widScroll->setMinimumSize(QSize(950,850));
    scroll->setWidget(widScroll);
    scroll->setAlignment(Qt::AlignCenter);

    QGridLayout *grid = new QGridLayout;
    grid->setMargin(10);
    widScroll->setLayout(grid);

    dateInvestment = new DDateEdit("Date de l'investissement");
    dateInvestment->setCalendarPopup(true);
    dateInvestment->setCurrentDate();
    grid->addWidget(dateInvestment,0,0);




    //Groupe de l'info sur le fournisseur--------------------------------------------------------------
    DGroupBox *groupFournisseur = new DGroupBox("Information sur le founisseur");
    groupFournisseur->setHeaderBgColor("#836FFF");
    grid->addWidget(groupFournisseur,1,0,1,2);

    QGridLayout *gridFournisseur = new QGridLayout;
    groupFournisseur->setBodyLayout(gridFournisseur);


    QSqlQueryModel *queryInvesterModel = new QSqlQueryModel;
    queryInvesterModel->setQuery("SELECT NomCompany FROM Fournisseurs");
    QCompleter *completerInvester = new QCompleter;
    completerInvester->setModel(queryInvesterModel);
    completerInvester->setCaseSensitivity(Qt::CaseInsensitive);
    invester_name = new DComboBox("Nom:");
    invester_name->setEditable(true);
    invester_name->setCompleter(completerInvester);
    invester_name->setModel(queryInvesterModel);
    gridFournisseur->addWidget(invester_name,0,0);


    DGroupBox *groupfournDetails = new DGroupBox("Details");
    gridFournisseur->addWidget(groupfournDetails,0,1,2,1);

    QHBoxLayout *hbox = new QHBoxLayout;
    groupfournDetails->setBodyLayout(hbox);

    QFormLayout *formDetailFourn1 = new QFormLayout;
    hbox->addLayout(formDetailFourn1);

    idFourn = new QLabel("---");
    formDetailFourn1->addRow("ID:",idFourn);

    nomFourn = new QLabel("---");
    formDetailFourn1->addRow("Nom:",nomFourn);

    prenomFourn = new QLabel("---");
    formDetailFourn1->addRow("Prenom:",prenomFourn);

    sexeFourn = new QLabel("---");
    formDetailFourn1->addRow("Sexe:",sexeFourn);


    QFormLayout *formDetailFourn2 = new QFormLayout;
    hbox->addLayout(formDetailFourn2);

    addrFourn = new QLabel("---");
    formDetailFourn2->addRow("Adresse:",addrFourn);

    telFourn = new QLabel("---");
    formDetailFourn2->addRow("Telephone:",telFourn);

    emailFourn = new QLabel("---");
    formDetailFourn2->addRow("Email:",emailFourn);

    nomComp = new QLabel("---");
    formDetailFourn2->addRow("Nom de l'entreprise:",nomComp);







    //Groupe de l'info sur les produits-----------------------------------------------------------
    DGroupBox *groupBox = new DGroupBox("Information sur le produit");
    groupBox->setHeaderBgColor("#7A67EE");
    grid->addWidget(groupBox,2,0,1,2);

    QGridLayout *gridBox = new QGridLayout;
    groupBox->setBodyLayout(gridBox);

    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT Nom FROM Produits");
    QCompleter *completer = new QCompleter;
    completer->setModel(queryModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    itemName = new DComboBox("Nom du produit");
    itemName->setModel(queryModel);
    itemName->setCompleter(completer);
    itemName->setEditable(true);
    itemName->setMinimumWidth(550);
    gridBox->addWidget(itemName,0,0);

    qteAchat = new DDoubleSpinBox("Quantite acheter");
    qteAchat->setMaximum(999999.99);
    gridBox->addWidget(qteAchat,1,0);

    prixAchat = new DDoubleSpinBox("Prix d'achat");
    prixAchat->setMaximum(999999.99);
    gridBox->addWidget(prixAchat,2,0);

    prixVente = new DDoubleSpinBox("Prix de vente");
    prixVente->setMaximum(999999.99);
    gridBox->addWidget(prixVente,3,0);


    DGroupBox *groupProduitDetails = new DGroupBox("Details");
    gridBox->addWidget(groupProduitDetails,0,1,4,1);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    groupProduitDetails->setBodyLayout(hbox2);

    QFormLayout *formDetailProduit1 = new QFormLayout;
    hbox2->addLayout(formDetailProduit1);

    idprod_lab = new QLabel("---");
    formDetailProduit1->addRow("ID:",idprod_lab);

    nomprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Nom du produit:",nomprod_lab);

    descriprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Description:",descriprod_lab);

    attriprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Attribute:",attriprod_lab);

    sizeprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Size:",sizeprod_lab);

    prixAprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Prix d'achat - HTG:",prixAprod_lab);

    prixVprod_lab = new QLabel("---");
    formDetailProduit1->addRow("Prix de vente - HTG:",prixVprod_lab);

    QVBoxLayout *vboxPlus = new QVBoxLayout;
    hbox2->addLayout(vboxPlus);

    qteAchat_lab = new DLabel("Quantite:");
    vboxPlus->addWidget(qteAchat_lab);

    totalA_lab = new DLabel("Total d'achat:");
    vboxPlus->addWidget(totalA_lab);

    totalV_lab = new DLabel("Total de vente:");
    vboxPlus->addWidget(totalV_lab);

    profit_lab = new DLabel("Profit:");
    profit_lab->setColor("blue");
    profit_lab->setBold(true);
    vboxPlus->addWidget(profit_lab);



    //Groupe de l'info sur l'investissement----------------------------------------------------------
    DGroupBox *groupInvestment = new DGroupBox("Information sur l'investissement");
    grid->addWidget(groupInvestment,3,0,1,2);

    QGridLayout *gridInvestment = new QGridLayout;
    groupInvestment->setBodyLayout(gridInvestment);

    descriptInvest = new DTextEdit("Description de l'investissement");
    descriptInvest->setMaximumWidth(550);
    gridInvestment->addWidget(descriptInvest,0,0,2,1);

    typePayer = new DComboBox("Type de paiement");
    typePayer->addItem("Cash");
    typePayer->addItem("Credit");
    gridInvestment->addWidget(typePayer,0,1);

    //----------------------------------------------

    groupCredit = new DGroupBox("Credit");
    groupCredit->setHeaderBgColor("#6959CD");
    groupCredit->setEnabled(false);
    gridInvestment->addWidget(groupCredit,1,1);

    QGridLayout *gridCredit = new QGridLayout;
    groupCredit->setBodyLayout(gridCredit);

    totalCredit = new DLabel("Montant du:");
    gridCredit->addWidget(totalCredit,0,0);

    mtntVerst = new DDoubleSpinBox("Montant du 1er versement:");
    mtntVerst->setMaximum(9999999.99);
    gridCredit->addWidget(mtntVerst,1,0);

    totalBalance = new DLabel("Balance:");
    gridCredit->addWidget(totalBalance,2,0);

    DPushButton *ajoutInvestment = new DPushButton("Ajouter");
    grid->addWidget(ajoutInvestment,4,1);


    QComboBox *invester_name_Q = invester_name->getComboBox();
    connect(invester_name_Q,SIGNAL(activated(QString)),this,SLOT(onChangeInvesterIndex(QString)));

    QComboBox *itemName_Q = itemName->getComboBox();
    connect(itemName_Q,SIGNAL(activated(QString)),this,SLOT(onChangeProduitIndex(QString)));

    QDoubleSpinBox *qteAchat_Q = qteAchat->getDoubleSpinBox();
    connect(qteAchat_Q,SIGNAL(valueChanged(double)),this,SLOT(onValueQteAchatChange(double)));

    QDoubleSpinBox *prixAchat_Q = prixAchat->getDoubleSpinBox();
    connect(prixAchat_Q,SIGNAL(valueChanged(double)),this,SLOT(onValuePrixAchatChange(double)));

    QDoubleSpinBox *prixVente_Q = prixVente->getDoubleSpinBox();
    connect(prixVente_Q,SIGNAL(valueChanged(double)),this,SLOT(onValuePrixVenteChange(double)));

    QComboBox *typePayer_Q = typePayer->getComboBox();
    connect(typePayer_Q,SIGNAL(activated(int)),this,SLOT(onChangeTypePayerIndex(int)));

    QDoubleSpinBox *mtntVerst_Q = mtntVerst->getDoubleSpinBox();
    connect(mtntVerst_Q,SIGNAL(valueChanged(double)),this,SLOT(onValueMtntVerstChange(double)));

    connect(ajoutInvestment,SIGNAL(clicked()),this,SLOT(onClickedAjoutInvestment()));

}

void ProduitInvestments::refreshModels()
{


}

void ProduitInvestments::onChangeProduitIndex(QString val)
{
    produitInstance->fetchProduitByName(val);
    idprod_lab->setText(QString::number(produitInstance->getIdProduit()));
    nomprod_lab->setText(produitInstance->getNomProduit());
    descriprod_lab->setText(produitInstance->getDescriptionProduit());
    attriprod_lab->setText(produitInstance->getAttributeProduit());
    sizeprod_lab->setText(produitInstance->getSizeProduit());
    prixAprod_lab->setText(QString::number(produitInstance->getPrixAchatProduit()));
    prixVprod_lab->setText(QString::number(produitInstance->getPrixVenteProduit()));

}

void ProduitInvestments::onChangeInvesterIndex(QString val)
{
    fournisseurInstance->fetchFournisseurByCompanyName(val);
    idFourn->setText(QString::number(fournisseurInstance->getIdFournisseur()));
    nomFourn->setText(fournisseurInstance->getNomFournisseur());
    prenomFourn->setText(fournisseurInstance->getPrenomFournisseur());
    sexeFourn->setText(fournisseurInstance->getSexeFournisseur());
    nomComp->setText(fournisseurInstance->getNomCompanyFournisseur());
    addrFourn->setText(fournisseurInstance->getAdresseFournisseur());
    telFourn->setText(fournisseurInstance->getTelephoneFournisseur());
    emailFourn->setText(fournisseurInstance->getEmailFournisseur());

}

void ProduitInvestments::onChangeTypePayerIndex(int idx)
{
    if(idx==0){
        totalCredit->setText("---");
        mtntVerst->setValue(0.00);
        totalBalance->setText("---");
        groupCredit->setEnabled(false);
    }else{
        totalCredit->setText(totalA_lab->text());
        onValueMtntVerstChange(mtntVerst->value());
        groupCredit->setEnabled(true);
    }
}


void ProduitInvestments::onValuePrixAchatChange(double val)
{
    totAchat = val *qteAchat->value();
    totVente = prixVprod_lab->text().toDouble() *qteAchat->value();

    prixAprod_lab->setText(QString::number(val));
    totalA_lab->setTextFromDoubleToInt(totAchat);
    totalV_lab->setTextFromDoubleToInt(totVente);
    profit_lab->setTextFromDoubleToInt(totVente-totAchat);

    if(typePayer->currentIndex()==1){
        totalCredit->setText(totalA_lab->text());
        onValueMtntVerstChange(mtntVerst->value());
    }
}

void ProduitInvestments::onValuePrixVenteChange(double val)
{
    totAchat = prixAprod_lab->text().toDouble() *qteAchat->value();
    totVente = val *qteAchat->value();

    prixVprod_lab->setText(QString::number(val));
    totalA_lab->setTextFromDoubleToInt(totAchat);
    totalV_lab->setTextFromDoubleToInt(totVente);
    profit_lab->setTextFromDoubleToInt(totVente-totAchat);
}

void ProduitInvestments::onValueQteAchatChange(double val)
{
    totAchat = prixAprod_lab->text().toDouble() *val;
    totVente = prixVprod_lab->text().toDouble() *val;

    qteAchat_lab->setTextFromInt(val);
    totalA_lab->setTextFromDoubleToInt(totAchat);
    totalV_lab->setTextFromDoubleToInt(totVente);
    profit_lab->setTextFromDoubleToInt(totVente-totAchat);

    if(typePayer->currentIndex()==1){
        totalCredit->setText(totalA_lab->text());
        onValueMtntVerstChange(mtntVerst->value());
    }

}

void ProduitInvestments::onValueMtntVerstChange(double d)
{
    totalBalance->setTextFromDoubleToInt(totAchat-d);
}

void ProduitInvestments::onClickedAjoutInvestment()
{

    if(qteAchat->value()<=0){
        qteAchat->setMessageError("* Ce champs ne doit pas etre inferieur ou egale a 0.");
        return;
    }

    if(prixAprod_lab->text().toDouble()<=0)
        return;

    if(descriptInvest->toPlainText().isEmpty()){
        descriptInvest->setMessageError("* Veuillez decrire votre investissement.\n(ex:Achat de 200 Sacs de ciment)");
        return;
    }

    fournisseurInstance->fetchFournisseurByCompanyName(invester_name->currentText());
    int idFournisseur = fournisseurInstance->getIdFournisseur();

    produitInstance->fetchProduitByName(itemName->currentText());
    int idProduit = produitInstance->getIdProduit();
    double qteEnStock = produitInstance->getQteEnStockProduit();


    query.prepare("INSERT INTO ProduitInvestment ([Quantite achat], PrixAchat, idFournisseur, idProduit, Description, cr_date,Statut)"
                  "VALUES (:qteAchat,:prixAchat,:idF,:idP,:description,:cr_date,:statut)");

    query.bindValue(":qteAchat",qteAchat->value());
    query.bindValue(":prixAchat",prixAprod_lab->text().toDouble());
    query.bindValue(":idF",idFournisseur);
    query.bindValue(":idP",idProduit);
    query.bindValue(":description",descriptInvest->toPlainText());
    query.bindValue(":cr_date",dateInvestment->date());
    query.bindValue(":statut",typePayer->currentIndex());

    if(query.exec())
    {
        query.prepare("UPDATE Produits SET [Qantite en stock] = :qte WHERE ID = :idd");
        query.bindValue(":qte",qteEnStock+qteAchat->value());
        query.bindValue(":idd",idProduit);
        if(query.exec())
            qDebug()<<"Quantite en stock ajuster ";
        else
            qDebug()<<"Quantite en stock non ajuster: "<<query.lastError();

        if(typePayer->currentIndex()==1)
        {
            idInvestmentProduit = query.lastInsertId().toInt();
            addCreditOnDB(idInvestmentProduit);

        }

        idprod_lab->setText("---");
        nomprod_lab->setText("---");
        descriprod_lab->setText("---");
        attriprod_lab->setText("---");
        sizeprod_lab->setText("---");
        prixAprod_lab->setText("---");
        prixVprod_lab->setText("---");

        idFourn->setText("---");
        nomFourn->setText("---");
        prenomFourn->setText("---");
        sexeFourn->setText("---");
        nomComp->setText("---");
        addrFourn->setText("---");
        telFourn->setText("---");
        emailFourn->setText("---");

        qteAchat->setHiddenMessageError(true);
        descriptInvest->setHiddenMessageError(true);

        qteAchat->setValue(0.00);
        prixAchat->setValue(0.00);
        prixVente->setValue(0.00);
        descriptInvest->clear();

    }else
        qDebug()<<"Investment not inserted : "<<query.lastError();

}


void ProduitInvestments::addCreditOnDB(int id)
{
    qDebug()<<"Id investment has been catched: "<<id;

    query.prepare("INSERT INTO CreditInvestment (cr_Date, id_PI, MontantDu)"
                  "VALUES (:cD,:idPi,:mtntDu)");

    query.bindValue(":cD",dateInvestment->date());
    query.bindValue(":idPi",id);
    query.bindValue(":mtntDu",totAchat);

    if(query.exec()){
        qDebug()<<"Credit inserted";
        addVersementOnDB(query.lastInsertId().toInt());
    }else
        qDebug()<<"Credit not insert: "<<query.lastError();
}


void ProduitInvestments::addVersementOnDB(int id)
{
    qDebug()<<"Id credit has been catched: "<<id;

    query.prepare("INSERT INTO Versement_CI (dateVersement, Description, MontantVerse, id_CI)"
                  "VALUES (:Dv,:descrip,:mtntV,:idCi)");

    query.bindValue(":Dv",dateInvestment->date());
    query.bindValue(":descrip","Montant du 1er versement");
    query.bindValue(":mtntV",mtntVerst->value());
    query.bindValue(":idCi",id);

    if(query.exec()){
        //Update the statut of investment
        query.prepare("UPDATE ProduitInvestment SET Statut = :state WHERE ID = "+idInvestmentProduit);
        query.bindValue(":state",1);
        if(query.exec()){
            qDebug()<<"Statut investment update ";
        }else
            qDebug()<<"Statut investment not update: "<<query.lastError();

        totalCredit->setText("---");
        mtntVerst->setValue(0.00);
        totalBalance->setText("---");
        groupCredit->setEnabled(false);
        typePayer->setCurrentIndex(0);
    }else
        qDebug()<<"Versement not insert: "<<query.lastError();
}
