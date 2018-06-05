#include "fen_transaction/fen_transactioninfo.h"

Fen_transactionInfo::Fen_transactionInfo(QWidget *parent) :
    QWidget(parent)
{
}

Fen_transactionInfo::Fen_transactionInfo(QSqlQuery q)
{
    querry = q;

    QVBoxLayout *v = new QVBoxLayout;
    this->setLayout(v);

    QTabWidget *tabparent = new QTabWidget;
    v->addWidget(tabparent);

    QWidget *transactionTab = new QWidget;
    tabparent->addTab(transactionTab,"TRANSACTION");
    setTransactionTab(transactionTab);

}


void Fen_transactionInfo::setTransactionTab(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    QImage *image = new QImage("Image/iconLogIn.png");
    QImage image2 = image->scaled(300,200,Qt::KeepAspectRatio);

    img = new QLabel;
    img->setPixmap(QPixmap::fromImage(image2) );
    img->setStyleSheet("border: 2px solid black;");
    img->setMinimumSize(300,200);
    grid->addWidget(img,0,0,1,1);
    grid->setAlignment(img,Qt::AlignLeft | Qt::AlignTop);

    model = new QStandardItemModel(0,10);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"NOM");
    model->setHeaderData(2,Qt::Horizontal,"PRENOM");
    model->setHeaderData(3,Qt::Horizontal,"DEPOT");
    model->setHeaderData(4,Qt::Horizontal,"QTE DE DEPOT");
    model->setHeaderData(5,Qt::Horizontal,"RETRAIT");
    model->setHeaderData(6,Qt::Horizontal,"QTE DE RETRAIT");
    model->setHeaderData(7,Qt::Horizontal,"SOLDE");
    model->setHeaderData(8,Qt::Horizontal,"GROUPE");
    model->setHeaderData(9,Qt::Horizontal,"STATUS");


    tableTransaction = new QTableView;
    tableTransaction->setModel(model);
    tableTransaction->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableTransaction->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableTransaction->setAlternatingRowColors(true);
    tableTransaction->setSortingEnabled(true);
    tableTransaction->setColumnWidth(0,50);
    grid->addWidget(tableTransaction,0,1,3,5);

    QWidget *wid_layout = new QWidget;
    grid->addWidget(wid_layout,1,0,1,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setSpacing(0);
    wid_layout->setLayout(vLayout);

    QLabel *lab_titre = new QLabel("INFO");
    lab_titre->setFont(QFont("",15,15,false));
    lab_titre->setMargin(5);
    lab_titre->setStyleSheet("background-color:#CD3333;color:white;");
    lab_titre->setMaximumHeight(30);
    vLayout->addWidget(lab_titre);

    QWidget *wid_layout2 = new QWidget;
    wid_layout2->setStyleSheet("background-color:#344956;");
    vLayout->addWidget(wid_layout2);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->setSpacing(0);
    vLayout2->setMargin(2);
    wid_layout2->setLayout(vLayout2);

    lab_ID = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("ID",lab_ID));

    lab_Nom = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Nom",lab_Nom));

    lab_Prenom = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Prenom",lab_Prenom));

    lab_depot = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Depot",lab_depot));

    lab_retrait = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Retrait",lab_retrait));

    lab_solde = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Solde",lab_solde));

    lab_groupe = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Groupe",lab_groupe));

    lab_status = new QLabel("---");
    vLayout2->addWidget(string_and_label_WidgetStyle("Status",lab_status));

    add_dataTotableTransaction();

    connect(tableTransaction,SIGNAL(doubleClicked(QModelIndex)),\
            this,SLOT(on_doubleClick_tableTransacion(QModelIndex)));

}


void Fen_transactionInfo::add_dataTotableTransaction()
{
    QStringList stringlisteID,stringlisteNom,stringlistePrenom,stringlisteGroupe,stringlisteStatus;

    querry.exec("SELECT * FROM liste_client_6");
    while(querry.next())
    {
        stringlisteID.append(querry.value(0).toString());
        stringlisteNom.append(querry.value(2).toString());
        stringlistePrenom.append(querry.value(3).toString());
        stringlisteGroupe.append(querry.value(23).toString());
        stringlisteStatus.append(querry.value(33).toString());
    }

    QList<QStandardItem*>listDataRow;
    int totDep,totRet,qteDep,qteRet;

    for(int i = 0;i<stringlisteID.size();i++)
    {
        totDep=0,totRet=0,qteDep=0,qteRet=0,listDataRow.clear();
        querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+stringlisteID.at(i));
        while(querry.next())
        {
            if(querry.value(3).toString()=="DEPOT")
                qteDep++;
            else if(querry.value(3).toString()=="RETRAIT")
                qteRet++;
            totDep += querry.value(5).toInt();
            totRet +=querry.value(4).toInt();

        }

        QStandardItem *idItem = new QStandardItem;
        idItem->setData(stringlisteID.at(i),Qt::DisplayRole);

        QStandardItem *totDepItem = new QStandardItem;
        totDepItem->setData(totDep,Qt::DisplayRole);

        QStandardItem *totRetItem = new QStandardItem;
        totRetItem->setData(totRet,Qt::DisplayRole);

        QStandardItem *qteDepItem = new QStandardItem;
        qteDepItem->setData(qteDep,Qt::DisplayRole);

        QStandardItem *qteRetItem = new QStandardItem;
        qteRetItem->setData(qteRet,Qt::DisplayRole);

        QStandardItem *soldeItem = new QStandardItem;
        soldeItem->setData(totDep-totRet,Qt::DisplayRole);

        listDataRow.append(new QStandardItem(stringlisteID.at(i)));
        listDataRow.append(new QStandardItem(stringlisteNom.at(i)));
        listDataRow.append(new QStandardItem(stringlistePrenom.at(i)));
        listDataRow.append(totDepItem);
        listDataRow.append(qteDepItem);
        listDataRow.append(totRetItem);
        listDataRow.append(qteRetItem);
        listDataRow.append(soldeItem);
        listDataRow.append(new QStandardItem(stringlisteGroupe.at(i)));
        listDataRow.append(new QStandardItem(stringlisteStatus.at(i)));

        model->insertRow(i,listDataRow);

    }

}


void Fen_transactionInfo::on_doubleClick_tableTransacion(QModelIndex idx)
{
    QString photo;
    QString id = model->data(model->index(idx.row(),0,QModelIndex())).toString();

    querry.exec("SELECT * FROM liste_client_6 WHERE id= "+id);
    while(querry.next())
        photo = querry.value(25).toString();

    QImage *image = new QImage(photo);
    QImage image2 = image->scaled(300,200,Qt::KeepAspectRatio);
    img->setPixmap(QPixmap::fromImage(image2) );

    lab_ID->setText(id);
    lab_Nom->setText(model->data(model->index(idx.row(),1,QModelIndex())).toString());
    lab_Prenom->setText(model->data(model->index(idx.row(),2,QModelIndex())).toString());
    lab_depot->setText(model->data(model->index(idx.row(),3,QModelIndex())).toString());
    lab_retrait->setText(model->data(model->index(idx.row(),5,QModelIndex())).toString());
    lab_solde->setText(model->data(model->index(idx.row(),7,QModelIndex())).toString());
    lab_groupe->setText(model->data(model->index(idx.row(),8,QModelIndex())).toString());
    lab_status->setText(model->data(model->index(idx.row(),9,QModelIndex())).toString());
}


