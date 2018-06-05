#include "produittransaction.h"

ProduitTransaction::ProduitTransaction(QWidget *parent) : QWidget(parent)
{

}

ProduitTransaction::ProduitTransaction(QSqlQuery q)
{
    query = q;

    QGridLayout *grid = new QGridLayout;
    this->setLayout(grid);
    this->setObjectName("widProduit");
    this->setStyleSheet("#widProduit{background-color: #77be96;}");

    dateTransac = new DDateEdit("Date");
    dateTransac->setCalendarPopup(true);
    dateTransac->setCurrentDate();
    grid->addWidget(dateTransac,0,4);

    //DComboBox *cashierComb = new DComboBox("Cahier");
    //grid->addWidget(cashierComb,0,3);

    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT Nom FROM Produits");
    QCompleter *completer = new QCompleter;
    completer->setModel(queryModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    enterItem = new DComboBox("Enter Item");
    enterItem->setEditable(true);
    enterItem->setCompleter(completer);
    enterItem->setModel(queryModel);
    grid->addWidget(enterItem,2,0,1,2);

    //DPushButton *bteFindItem = new DPushButton("Find Item(s)");
    //grid->addWidget(bteFindItem,2,3);

    modelTransaction = new QStandardItemModel(0,9);
    modelTransaction->setHeaderData(0,Qt::Horizontal,"Item#");
    modelTransaction->setHeaderData(1,Qt::Horizontal,"Item Name");
    modelTransaction->setHeaderData(2,Qt::Horizontal,"Item Description");
    modelTransaction->setHeaderData(3,Qt::Horizontal,"Attribute");
    modelTransaction->setHeaderData(4,Qt::Horizontal,"Size");
    modelTransaction->setHeaderData(5,Qt::Horizontal,"Qty");
    modelTransaction->setHeaderData(6,Qt::Horizontal,"Price");
    modelTransaction->setHeaderData(7,Qt::Horizontal,"Ext Price");
    modelTransaction->setHeaderData(8,Qt::Horizontal,"Avail Qty");

    tableTransaction = new QTableView;
    tableTransaction->setModel(modelTransaction);
    tableTransaction->setObjectName("tableTransaction");
    tableTransaction->setColumnWidth(1,100);
    tableTransaction->setColumnWidth(2,200);
    tableTransaction->setStyleSheet("#tableTransaction{background-color:#e6e9e7;}");
    tableTransaction->setItemDelegate(new TransactionDelegate);
    tableTransaction->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableTransaction->setAlternatingRowColors(true);
    tableTransaction->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableTransaction,3,0,1,5);


    QSqlQueryModel *queryModelCustomer = new QSqlQueryModel;
    queryModelCustomer->setQuery("SELECT Company FROM Client");
    QCompleter *completerCustomer = new QCompleter;
    completerCustomer->setModel(queryModelCustomer);
    completerCustomer->setCaseSensitivity(Qt::CaseInsensitive);
    customerInfo = new DComboBox("Customer Info");
    customerInfo->setMinimumWidth(200);
    customerInfo->setEditable(true);
    customerInfo->setCompleter(completerCustomer);
    grid->addWidget(customerInfo,4,0);


    //DPushButton *bteFindCustomer = new DPushButton("Find");
    //grid->addWidget(bteFindCustomer,5,0);

    DTextEdit *comments = new DTextEdit("Comments");
    grid->addWidget(comments,4,1,3,1);


    subtotal = new DLabel("SubTotal");
    subtotal->setMinimumWidth(160);
    grid->addWidget(subtotal,4,4);

    discount = new DDoubleSpinBox("Discount");
    discount->setMaximum(999999.99);
    grid->addWidget(discount,5,4);

    totalPayment = new DLabel("Total");
    grid->addWidget(totalPayment,6,4);

    DPushButton *takePayment = new DPushButton("Take Payment");
    grid->addWidget(takePayment,7,4);

    QComboBox *enterItem_Q = enterItem->getComboBox();
    connect(enterItem_Q,SIGNAL(activated(QString)),this,SLOT(onEnterItem(QString)));

    connect(modelTransaction,SIGNAL(itemChanged(QStandardItem*)),\
            this,SLOT(onItemModelTransactionChanged(QStandardItem*)));

    QDoubleSpinBox *discount_Q = discount->getDoubleSpinBox();
    connect(discount_Q,SIGNAL(valueChanged(double)),this,SLOT(onValueDiscountChanged(double)));
    connect(tableTransaction,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onClickMenuContext(QPoint)));

    connect(takePayment,SIGNAL(clicked()),this,SLOT(onClickedTakePayment()));


}

void ProduitTransaction::onEnterItem(QString itemName)
{
    qDebug()<<itemName;
    QList<QStandardItem*> item;



    query.prepare("SELECT * FROM Produits WHERE Nom = '"+itemName+"' ");
    if(query.exec())
    {
        if(query.next()){
            QStandardItem *id = new QStandardItem;
            id->setData(query.value(0).toInt(),Qt::DisplayRole);
            item.append(id);

            QStandardItem *nom = new QStandardItem;
            nom->setData(query.value(1).toString(),Qt::DisplayRole);
            item.append(nom);

            QStandardItem *description = new QStandardItem;
            description->setData(query.value(2).toString(),Qt::DisplayRole);
            item.append(description);

            QStandardItem *attribute = new QStandardItem;
            attribute->setData(query.value(3).toString(),Qt::DisplayRole);
            item.append(attribute);

            QStandardItem *size = new QStandardItem;
            size->setData(query.value(4).toString(),Qt::DisplayRole);
            item.append(size);

            QStandardItem *qty = new QStandardItem;
            qty->setData(1,Qt::DisplayRole);

            QStandardItem *price = new QStandardItem;
            price->setData(query.value(7).toDouble(),Qt::DisplayRole);

            QStandardItem *extPrice = new QStandardItem;
            extPrice->setData(query.value(7).toDouble(),Qt::DisplayRole);

            QStandardItem *availQty = new QStandardItem;
            availQty->setData(query.value(5).toDouble(),Qt::DisplayRole);

            modelTransaction->appendRow(item);
            modelTransaction->setItem(modelTransaction->rowCount()-1,5,qty);
            modelTransaction->setItem(modelTransaction->rowCount()-1,6,price);
            modelTransaction->setItem(modelTransaction->rowCount()-1,7,extPrice);
            modelTransaction->setItem(modelTransaction->rowCount()-1,8,availQty);
        }
    }
}


void ProduitTransaction::onItemModelTransactionChanged(QStandardItem *item)
{
    Q_UNUSED(item);
    totalPayment_V=0;
    qteVendu_V=0;

    for(int i=0;i<modelTransaction->rowCount();++i){
        totalPayment_V += modelTransaction->data(modelTransaction->index(i,7),Qt::EditRole).toDouble();
        qteVendu_V += modelTransaction->data(modelTransaction->index(i,5),Qt::EditRole).toDouble();
    }

    //qDebug()<<total;
    subtotal->setTextFromDouble(totalPayment_V);
    totalPayment->setTextFromDouble(totalPayment_V - discount->value());
}

void ProduitTransaction::onValueDiscountChanged(double value)
{
    totalPayment->setTextFromDouble(totalPayment_V-value);
}

void ProduitTransaction::onClickMenuContext(QPoint)
{
    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("effacer l'article"),this);

    contextMenu.addAction(&action);
    connect(&action,SIGNAL(triggered()),this,SLOT(deleteItem()));
    contextMenu.exec(QCursor::pos());

}

void ProduitTransaction::deleteItem()
{
    int row = tableTransaction->selectionModel()->currentIndex().row();
    modelTransaction->removeRow(row,QModelIndex());
    onItemModelTransactionChanged(new QStandardItem);
}

void ProduitTransaction::onClickedTakePayment()
{
    diagPayment = new QDialog;
    diagPayment->setWindowTitle("Receipt Payment");
    diagPayment->setMinimumWidth(400);
    diagPayment->setModal(true);

    QGridLayout *grid = new QGridLayout;
    diagPayment->setLayout(grid);

    cashPayment = new DDoubleSpinBox("Montant du recu");
    cashPayment->setMaximum(999999.99);
    cashPayment->setValue(totalPayment_V - discount->value());
    grid->addWidget(cashPayment,0,0,1,2);

    typePayment = new DComboBox("Type de paiement");
    typePayment->addItem("Cash");
    typePayment->addItem("Check");
    typePayment->addItem("Credit");

    grid->addWidget(typePayment,1,0,1,2);

    DPushButton *pushSavePayment = new DPushButton("Save");
    grid->addWidget(pushSavePayment,2,1);

    diagPayment->show();

    connect(pushSavePayment,SIGNAL(clicked()),this,SLOT(onClickedSavePayment()));
}

void ProduitTransaction::onClickedSavePayment()
{
    query.prepare("INSERT INTO Sales_Transaction(Date,[Type Vente], [Nom Complet], Qte, Total, Payment,Return)"
                  "VALUES (:date,:typeV,:nomC,:qte,:total,:pay,:return)");

    query.bindValue(":date",dateTransac->date());
    query.bindValue(":typeV","Sales");
    query.bindValue(":nomC",customerInfo->currentText());
    query.bindValue(":qte",qteVendu_V);
    query.bindValue(":total",totalPayment_V - discount->value());
    query.bindValue(":pay",typePayment->currentText());
    query.bindValue(":return",0);

    if(query.exec())
    {
        int lastID = query.lastInsertId().toInt();
        for(int i=0;i<modelTransaction->rowCount();++i)
        {
            insertIntoSalesDetails(lastID,i);
        }
        while(modelTransaction->rowCount()>0)
            modelTransaction->removeRow(0,QModelIndex());

        subtotal->setText("---");
        discount->setValue(0.00);
        totalPayment->setText("---");
        diagPayment->close();
    }else
        qDebug()<<"Transaction not insert :"<<query.lastError();
}

void ProduitTransaction::insertIntoSalesDetails(int id,int idxItem)
{
    query.prepare("INSERT INTO Sales_Details(idProduit,[Nom Produit],Qte,PrixAchat,PrixVente,idSales_T)"
                  "VALUES (:idp,:Nproduit,:qte,(SELECT PrixAchat FROM Produits WHERE ID =:idp),:pV,:idS)");


    query.bindValue(":idp",modelTransaction->data(modelTransaction->index(idxItem,0),Qt::EditRole).toInt());
    query.bindValue(":Nproduit",modelTransaction->data(modelTransaction->index(idxItem,1),Qt::EditRole).toString());
    query.bindValue(":qte",modelTransaction->data(modelTransaction->index(idxItem,5),Qt::EditRole).toDouble());
    query.bindValue(":pV",modelTransaction->data(modelTransaction->index(idxItem,6),Qt::EditRole).toDouble());
    query.bindValue(":idS",id);

    if(query.exec()){
        qDebug()<<"Insert item :"<<idxItem;
        updateQteProduitEnStock(modelTransaction->data(modelTransaction->index(idxItem,5),Qt::EditRole).toDouble(),\
                                modelTransaction->data(modelTransaction->index(idxItem,0),Qt::EditRole).toInt());
    }
    else
        qDebug()<<"Item not insert :"<<idxItem<<" "<<query.lastError();

}

void ProduitTransaction::updateQteProduitEnStock(double qteEnStock, int idProduit)
{
    qDebug()<<qteEnStock<<endl<<idProduit;

    query.prepare("UPDATE Produits SET [Qantite en stock] = [Qantite en stock] - :qte WHERE ID = :idd");
    query.bindValue(":qte",qteEnStock);
    query.bindValue(":idd",idProduit);
    if(query.exec())
        qDebug()<<"Quantite en stock ajuster ";
    else
        qDebug()<<"Quantite en stock non ajuster: "<<query.lastError();
}

void ProduitTransaction::setFenWidget(QMdiSubWindow *sub)
{
    subWindow = sub;
}

void ProduitTransaction::fermerFen()
{
    subWindow->close();
}
