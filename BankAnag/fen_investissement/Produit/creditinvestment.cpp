#include "creditinvestment.h"

CreditInvestment::CreditInvestment(QWidget *parent) : QWidget(parent)
{

}


CreditInvestment::CreditInvestment(QSqlQuery q)
{
    query = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QTabWidget *tabWid = new QTabWidget;
    vbox->addWidget(tabWid);

    QWidget *listCredittTab = new QWidget;
    setTabListeCredit(listCredittTab);
    tabWid->addTab(listCredittTab,"Liste des credits de produit");

}


void CreditInvestment::setTabListeCredit(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    modelCreditProduit = new QSqlRelationalTableModel;
    modelCreditProduit->setTable("CreditInvestment");
    modelCreditProduit->setRelation(2,QSqlRelation("ProduitInvestment","ID","Description"));
    modelCreditProduit->setHeaderData(1,Qt::Horizontal,"Date");
    modelCreditProduit->setHeaderData(3,Qt::Horizontal,"Montant du credit");
    selectModelCredit();


    tableCreditProduit = new QTableView;
    tableCreditProduit->setModel(modelCreditProduit);
    tableCreditProduit->setColumnWidth(2,300);
    tableCreditProduit->setAlternatingRowColors(true);
    tableCreditProduit->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableCreditProduit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableCreditProduit->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableCreditProduit,0,0);

    connect(tableCreditProduit,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onDoubleClickedTableCredit(QModelIndex)));
    connect(tableCreditProduit,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenuCredit(QPoint)));

}


void CreditInvestment::showContextMenuCredit(QPoint)
{
    //Q_UNUSED(p);

    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer le rapport de credit"),this);

    contextMenu.addAction(&action);
    connect(&action,SIGNAL(triggered()),this,SLOT(effacerCredit()));
    contextMenu.exec(QCursor::pos());
}



void CreditInvestment::effacerCredit()
{
    int row = tableCreditProduit->selectionModel()->currentIndex().row();
    QString id = modelCreditProduit->index(row,0).data().toString();

    query.prepare("DELETE FROM CreditInvestment WHERE ID = "+id);
    if(query.exec()){
        qDebug()<<"Credit was delete";
        modelCreditProduit->select();
    }else
        qDebug()<<"Credit was not delete: "<<query.lastError();
}


void CreditInvestment::selectModelCredit()
{
    modelCreditProduit->select();
}


void CreditInvestment::onDoubleClickedTableCredit(QModelIndex idx)
{
    QDialog *diag = new QDialog;
    diag->setModal(true);
    diag->setMinimumWidth(650);

    QGridLayout *grid = new QGridLayout;
    diag->setLayout(grid);

    idInvest = new DLabel("ID");
    idInvest->setText(modelCreditProduit->index(idx.row(),0).data().toString());
    grid->addWidget(idInvest,0,0);

    DLabel *description = new DLabel("Description de l'investissement");
    description->setText(modelCreditProduit->index(idx.row(),2).data().toString());
    grid->addWidget(description,0,1,1,2);

    dateVers = new DDateEdit("Date");
    dateVers->setCalendarPopup(true);
    dateVers->setCurrentDate();
    grid->addWidget(dateVers,1,0);

    descripVers = new DLineEdit("Description");
    grid->addWidget(descripVers,1,1);

    mtntVersement = new DDoubleSpinBox("Montant");
    mtntVersement->setMaximum(9999999.99);
    grid->addWidget(mtntVersement,1,2);

    modelVersementCredit = new QSqlRelationalTableModel;
    modelVersementCredit->setTable("Versement_CI");
    modelVersementCredit->select();

    tableVersementCredit = new QTableView;
    tableVersementCredit->setModel(modelVersementCredit);
    tableVersementCredit->setColumnWidth(2,200);
    tableVersementCredit->setAlternatingRowColors(true);
    tableVersementCredit->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVersementCredit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableVersementCredit->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableVersementCredit,2,0,1,4);

    totMontantDu = modelCreditProduit->index(idx.row(),3).data().toDouble();
    DLabel *mtntDu = new DLabel("Montant Du");
    mtntDu->setTextFromDoubleToInt(totMontantDu);
    grid->addWidget(mtntDu,3,0);

    totVersement = new DLabel("Versement");
    grid->addWidget(totVersement,3,1);

    balance = new DLabel("Balance");
    grid->addWidget(balance,3,2);


    DPushButton *pushVersement = new DPushButton("Ajouter");
    grid->addWidget(pushVersement,1,3);

    diag->show();
    loadDataVersement(idInvest->text(),totMontantDu);

    connect(pushVersement,SIGNAL(clicked()),this,SLOT(onClickedAddVersement()));
    connect(tableVersementCredit,SIGNAL(customContextMenuRequested(QPoint)),SLOT(showContextMenuVersement(QPoint)));
}


void CreditInvestment::showContextMenuVersement(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer le versement"),this);

    contextMenu.addAction(&action);
    connect(&action,SIGNAL(triggered()),this,SLOT(effacerVersement()));
    contextMenu.exec(QCursor::pos());
}

void CreditInvestment::effacerVersement()
{
    int row = tableVersementCredit->selectionModel()->currentIndex().row();
    QString id = modelVersementCredit->index(row,0).data().toString();

    query.prepare("DELETE FROM Versement_CI WHERE ID = "+id);
    if(query.exec()){
        qDebug()<<"Versement was delete";
        loadDataVersement(idInvest->text(),totMontantDu);
    }else
        qDebug()<<"Versement was not delete: "<<query.lastError();
}



void CreditInvestment::loadDataVersement(QString id, double mtntDu)
{
    double totVers = 0,balanceMtnt = 0;

    query.prepare("SELECT MontantVerse FROM Versement_CI WHERE id_CI = "+id);
    if(query.exec()){
        while(query.next())
            totVers+=query.value(0).toDouble();
    }

    balanceMtnt = mtntDu - totVers;
    totVersement->setTextFromDoubleToInt(totVers);
    balance->setTextFromDoubleToInt(balanceMtnt);
    modelVersementCredit->setFilter("id_CI = "+id);
}


void CreditInvestment::onClickedAddVersement()
{
    if(descripVers->text().isEmpty())
        return;
    if(mtntVersement->value()<=0)
        return;

    query.prepare("INSERT INTO Versement_CI (dateVersement,Description,MontantVerse,id_CI)"
                  "VALUES (:dateV, :descript, :mtntV, :id_c)");
    query.bindValue(":dateV",dateVers->date());
    query.bindValue(":descript",descripVers->text());
    query.bindValue(":mtntV",mtntVersement->value());
    query.bindValue(":id_c",idInvest->text());

    if(query.exec()){
        descripVers->clear();
        mtntVersement->setValue(0.00);
        modelVersementCredit->select();
        loadDataVersement(idInvest->text(),totMontantDu);
        qDebug()<<query.lastInsertId();
    }else
        qDebug()<<query.lastQuery()<<query.lastInsertId() <<query.lastError()<<query.ValuesAsColumns;
}

