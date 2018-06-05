#include "service.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "DesignWidgets/dpushbutton.h"

Service::Service(QWidget *parent) : QWidget(parent)
{

}

Service::Service(QSqlQuery q)
{
    query = q;

    QGridLayout *grid = new QGridLayout;
    this->setLayout(grid);

    modelInvestmentService = new QSqlRelationalTableModel;
    modelInvestmentService->setTable("ServiceInvestment");
    modelInvestmentService->setRelation(6,QSqlRelation("Emprunteur","ID","NomCompany"));
    modelInvestmentService->select();


    tableServiceInvestment = new QTableView;
    tableServiceInvestment->setModel(modelInvestmentService);
    tableServiceInvestment->setAlternatingRowColors(true);
    tableServiceInvestment->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableServiceInvestment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableServiceInvestment->setColumnWidth(0,50);
    tableServiceInvestment->setColumnWidth(2,300);
    tableServiceInvestment->setColumnWidth(4,150);
    tableServiceInvestment->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableServiceInvestment,0,0,4,1);

    DPushButton *bte_addInvestment = new DPushButton("Ajouter un nouveau\ninvestissement");
    grid->addWidget(bte_addInvestment,0,1);

    totInvestmentHTG_lab = new DLabel("Total des investissement en HTG");
    grid->addWidget(totInvestmentHTG_lab,1,1);

    totInvestmentUSD_lab = new DLabel("Total des investissement en USD");
    grid->addWidget(totInvestmentUSD_lab,2,1);



    updateInvestmentTotal();

    connect(bte_addInvestment,SIGNAL(clicked()),this,SLOT(showDialogAddInvestment()));
    connect(tableServiceInvestment,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onClickedServiceTable(QModelIndex)));
    connect(tableServiceInvestment,SIGNAL(customContextMenuRequested(QPoint)),\
            this,SLOT(showContextInvestmentMenu(QPoint)));
}

void Service::updateInvestmentTotal()
{
    query.prepare("SELECT SUM([MONTANT INVESTISSEMENT]) FROM ServiceInvestment WHERE [TYPE ARGENT] = 'HTG'");
    if(query.exec())
        if(query.first())
            totInvestmentHTG_lab->setTextFromDouble(query.value(0).toDouble());

    query.prepare("SELECT SUM([MONTANT INVESTISSEMENT]) FROM ServiceInvestment WHERE [TYPE ARGENT] = 'USD'");
    if(query.exec())
        if(query.first())
            totInvestmentUSD_lab->setTextFromDouble(query.value(0).toDouble());
}

void Service::showContextInvestmentMenu(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer l'investissement"),this);
    contextMenu.addAction(&action);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerInvestment()));
    contextMenu.exec(QCursor::pos());
}

void Service::effacerInvestment()
{
    int row = tableServiceInvestment->selectionModel()->currentIndex().row();
    QString id = modelInvestmentService->index(row,0,QModelIndex()).data().toString();

    query.prepare("DELETE FROM ServiceInvestment WHERE ID ="+id);
    if(query.exec())
    {
        updateInvestmentTotal();
        modelInvestmentService->select();
    }
}

void Service::showDialogAddInvestment()
{
    QDialog *diagAddInvestment = new QDialog;
    diagAddInvestment->setWindowTitle("Ajouter un nouveau investissement");
    diagAddInvestment->setMinimumWidth(300);
    diagAddInvestment->setModal(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagAddInvestment->setLayout(vbox);

    dateInvestment = new DDateEdit("Date:");
    dateInvestment->setCurrentDate();
    dateInvestment->setCalendarPopup(true);
    vbox->addWidget(dateInvestment);

    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT NomCompany FROM Emprunteur");
    QCompleter *completer = new QCompleter;
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(queryModel);
    emprunteurInvest = new DComboBox("Emprunteur");
    emprunteurInvest->setEditable(true);
    emprunteurInvest->setCompleter(completer);
    vbox->addWidget(emprunteurInvest);

    typeArgent = new DComboBox("Type d'argent:");
    typeArgent->addItem("HTG");
    typeArgent->addItem("USD");
    vbox->addWidget(typeArgent);

    montantInvest = new DDoubleSpinBox("Montant:");
    montantInvest->setMaximum(999999.99);
    vbox->addWidget(montantInvest);

    tauxMontant = new DDoubleSpinBox("Taux:");
    tauxMontant->setMaximum(999.99);
    vbox->addWidget(tauxMontant);

    descriptionInvest = new DTextEdit("Description:");
    vbox->addWidget(descriptionInvest);

    DPushButton *ajouterInvestment = new DPushButton("Ajouter");
    vbox->addWidget(ajouterInvestment);

    diagAddInvestment->show();

    connect(ajouterInvestment,SIGNAL(clicked()),this,SLOT(insertIntoServiceInvestmentTable()));
}


void Service::insertIntoServiceInvestmentTable()
{

    if(montantInvest->value()<=0)
        return;
    if(descriptionInvest->toPlainText().isEmpty())
        return;
    if(emprunteurInvest->currentText().isEmpty())
        return;
    int idEmprunteur=-1;
    query.exec("SELECT ID FROM Emprunteur WHERE NomCompany = '"+emprunteurInvest->currentText()+"' ");
    while(query.next())
        idEmprunteur = query.value(0).toInt();

    if(idEmprunteur==-1 || !idEmprunteur)
        return;

    query.prepare("INSERT INTO ServiceInvestment(DATE,DESCRIPTION,[TYPE ARGENT],[MONTANT INVESTISSEMENT],TAUX,EMPRUNTEUR)"
                  "VALUES (:date,:descrip,:tArgent,:mtntInvest,:taux,:emprunt)");

    query.bindValue(":date",dateInvestment->date());
    query.bindValue(":descrip",descriptionInvest->toPlainText());
    query.bindValue(":tArgent",typeArgent->currentText());
    query.bindValue(":mtntInvest",montantInvest->value());
    query.bindValue(":taux",tauxMontant->value());
    query.bindValue(":emprunt",idEmprunteur);

    if(query.exec())
    {
        qDebug()<<"ServiceInvestment was inserted";
        descriptionInvest->clear();
        montantInvest->setValue(0.00);
        tauxMontant->setValue(0.00);

        modelInvestmentService->select();
        updateInvestmentTotal();

    }else{
        qDebug()<<"ServiceInvestment was not inserted: "<<query.lastError();
    }

}

void Service::onClickedServiceTable(QModelIndex idx)
{
    int row = idx.row();
    QString id = modelInvestmentService->index(row,0,QModelIndex()).data().toString();
    double mtntInvestment = modelInvestmentService->index(row,4,QModelIndex()).data().toDouble();
    double sumVersement = -1;

    query.prepare("SELECT SUM(MONTANT) FROM Versement_SInvestment WHERE ID_PARENT = "+id);
    if(query.exec())
    {
        if(query.first())
            sumVersement = query.value(0).toDouble();
    }

    QDialog *dialogVersement = new QDialog;
    dialogVersement->setModal(true);
    dialogVersement->setMinimumWidth(700);
    dialogVersement->setMinimumHeight(400);
    dialogVersement->setWindowTitle("Versements");

    QGridLayout *grid = new QGridLayout;
    dialogVersement->setLayout(grid);

    modelVersement = new QSqlRelationalTableModel;
    modelVersement->setTable("Versement_SInvestment");
    modelVersement->select();
    modelVersement->setFilter("ID_PARENT = "+id);

    tableVersement = new QTableView;
    tableVersement->setModel(modelVersement);
    tableVersement->setAlternatingRowColors(true);
    tableVersement->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVersement->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableVersement->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableVersement,0,0,4,4);

    idEmprunteur_lab = new DLabel("ID de l'emprunt:");
    idEmprunteur_lab->setText(id);
    grid->addWidget(idEmprunteur_lab,0,5);

    DPushButton *addVersement = new DPushButton("Ajouter un versement");
    grid->addWidget(addVersement,1,5);

    mtntInvestment_lab = new DLabel("Montant de l'investissement:");
    mtntInvestment_lab->setText(QString::number(mtntInvestment));
    grid->addWidget(mtntInvestment_lab,5,0);

    versement_lab = new DLabel("Total des versements:");
    versement_lab->setTextFromDouble(sumVersement);
    grid->addWidget(versement_lab,5,1);

    balance_lab = new DLabel("Balance:");
    if(mtntInvestment-sumVersement<0)
        balance_lab->setText("0");
    else
        balance_lab->setTextFromDouble(mtntInvestment-sumVersement);
    grid->addWidget(balance_lab,5,2);

    profit_lab = new DLabel("Profit:");
    if(sumVersement-mtntInvestment>0)
        profit_lab->setTextFromDouble(sumVersement-mtntInvestment);
    grid->addWidget(profit_lab,5,3);

    dialogVersement->show();

    connect(addVersement,SIGNAL(clicked()),this,SLOT(showDiagAddVersement()));
    connect(tableVersement,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextVersementMenu(QPoint)));
}

void Service::showContextVersementMenu(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer le versement"),this);
    contextMenu.addAction(&action);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerVersement()));
    contextMenu.exec(QCursor::pos());
}

void Service::effacerVersement()
{
    int row = tableVersement->selectionModel()->currentIndex().row();
    QString id = modelVersement->index(row,0,QModelIndex()).data().toString();

    query.prepare("DELETE FROM Versement_SInvestment WHERE ID ="+id);
    if(query.exec())
    {
        modelVersement->setFilter("ID_PARENT = "+idEmprunteur_lab->text());

        double sumVersement = -1;
        query.prepare("SELECT SUM(MONTANT) FROM Versement_SInvestment WHERE ID_PARENT = "+idEmprunteur_lab->text());
        if(query.exec())
            if(query.first())
                sumVersement = query.value(0).toDouble();

        versement_lab->setTextFromDouble(sumVersement);

        if(mtntInvestment_lab->text().toDouble()-sumVersement<0)
            balance_lab->setText("0");
        else
            balance_lab->setTextFromDouble(mtntInvestment_lab->text().toDouble()-sumVersement);

        if(sumVersement-mtntInvestment_lab->text().toDouble()>0)
            profit_lab->setTextFromDouble(sumVersement-mtntInvestment_lab->text().toDouble());
    }

}

void Service::showDiagAddVersement()
{
    QDialog *diagVersement = new QDialog;
    diagVersement->setWindowTitle("Ajouter un versement");
    diagVersement->setModal(true);
    diagVersement->setMinimumWidth(350);

    QVBoxLayout *vbox = new QVBoxLayout;
    diagVersement->setLayout(vbox);

    dateVersement = new DDateEdit("Date:");
    dateVersement->setCurrentDate();
    dateVersement->setCalendarPopup(true);
    vbox->addWidget(dateVersement);

    descriptVersement = new DLineEdit("Description:");
    vbox->addWidget(descriptVersement);

    montantVersement = new DDoubleSpinBox("Montant:");
    montantVersement->setMaximum(999999.99);
    vbox->addWidget(montantVersement);

    tauxVersement = new DDoubleSpinBox("Taux:");
    tauxVersement->setMaximum(9999.99);
    vbox->addWidget(tauxVersement);

    DPushButton *ajouterVersement = new DPushButton("Ajouter");
    vbox->addWidget(ajouterVersement);

    diagVersement->show();

    connect(ajouterVersement,SIGNAL(clicked()),this,SLOT(insertIntoVersementTable()));
}




void Service::insertIntoVersementTable()
{
    query.prepare("INSERT INTO Versement_SInvestment(DATE,DESCRIPTION,MONTANT,TAUX,ID_PARENT)"
                  "VALUES (:date,:descrip,:mtnt,:taux,:idParent)");

    query.bindValue(":date",dateVersement->date());
    query.bindValue(":descrip",descriptVersement->text());
    query.bindValue(":mtnt",montantVersement->value());
    query.bindValue(":taux",tauxVersement->value());
    query.bindValue(":idParent",idEmprunteur_lab->text().toInt());

    if(query.exec())
    {
        qDebug()<<"Versement was insert";
        descriptVersement->clear();
        montantVersement->setValue(0.00);
        tauxVersement->setValue(0.00);
        modelVersement->select();

        double sumVersement = -1;
        query.prepare("SELECT SUM(MONTANT) FROM Versement_SInvestment WHERE ID_PARENT = "+idEmprunteur_lab->text());
        if(query.exec())
            if(query.first())
                sumVersement = query.value(0).toDouble();

        versement_lab->setTextFromDouble(sumVersement);

        if(mtntInvestment_lab->text().toDouble()-sumVersement<0)
            balance_lab->setText("0");
        else
            balance_lab->setTextFromDouble(mtntInvestment_lab->text().toDouble()-sumVersement);

        if(sumVersement-mtntInvestment_lab->text().toDouble()>0)
            profit_lab->setTextFromDouble(sumVersement-mtntInvestment_lab->text().toDouble());

    }else
        qDebug()<<"Versement was not insert: "<<query.lastError();

}
