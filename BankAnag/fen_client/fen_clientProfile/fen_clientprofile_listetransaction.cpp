#include "fen_clientprofile.h"


QWidget *Fen_ClientProfile::setTransactionTab()
{

    QWidget *transactionTab = new QWidget;

    pGLayout2 = new QGridLayout;
    transactionTab->setLayout(pGLayout2);


    modelTransaction = new QSqlTableModel;
    modelTransaction->setTable("transaction_table_6");
    modelTransaction->setFilter("ID_CLIENT ="+foreign_id);
    modelTransaction->select();


    transac_table = new QTableView;
    //transac_table->setFixedHeight(320);
    transac_table->setModel(modelTransaction);
    transac_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    transac_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transac_table->setAlternatingRowColors(true);
    pGLayout2->addWidget(transac_table,0,1,3,1);


    for(int i=0;i<5;i++){
        infoTabTransac[i] = new QLabel("---");
        infoTabTransac[i]->setFont(QFont("",10,10,false));
        }

    QGroupBox *infoTransac = new QGroupBox("Resume des transactions");
    pGLayout2->addWidget(infoTransac,0,2,1,1);

    QFormLayout *FormResumtransac = new QFormLayout;
    infoTransac->setLayout(FormResumtransac);

    FormResumtransac->addRow("Nombre de depot: ",infoTabTransac[0]);
    FormResumtransac->addRow("Total des depots: ",infoTabTransac[1]);

    FormResumtransac->addRow("Nombre de retrait: ",infoTabTransac[2]);
    FormResumtransac->addRow("Total des retraits: ",infoTabTransac[3]);

    FormResumtransac->addRow("Solde: ",infoTabTransac[4]);

    ptitre = new QGroupBox("Transaction");
    //pGLayout2->addWidget(ptitre,0,1,1,1);

    pFormtransac = new QFormLayout;
    ptitre->setLayout(pFormtransac);

    debitEdit = new QSpinBox;
    debitEdit->setMaximum(10000);
    pFormtransac->addRow("Debiter le compte: ",debitEdit);

    creditEdit = new QSpinBox;
    creditEdit->setMaximum(10000);
    pFormtransac->addRow("Crediter le compte: ",creditEdit);

    valider = new QPushButton("valider");
    pFormtransac->addRow("validation",valider);

    QGroupBox *grpcher = new QGroupBox("Recherche");
    pGLayout2->addWidget(grpcher,1,2);

    QFormLayout *fcher = new QFormLayout;
    grpcher->setLayout(fcher);

    check1 = new QCheckBox;
    check1->setChecked(true);
    fcher->addRow("Depot",check1);

    check2 = new QCheckBox;
    check2->setChecked(true);
    fcher->addRow("Retrait",check2);

    date1 = new QDateEdit;
    date1->setCalendarPopup(true);
    date1->setDate(QDate::fromString("01/07/2016","dd/MM/yyyy"));
    date1->setDisplayFormat("dd/MM/yyyy");
    fcher->addRow("De: ",date1);

    date2 = new QDateEdit;
    date2->setCalendarPopup(true);
    date2->setDate(QDate::currentDate());
    date2->setDisplayFormat("dd/MM/yyyy");
    fcher->addRow("a: ",date2);

    QPushButton *chercher = new QPushButton("Cliquez ici");
    fcher->addRow("Chercher",chercher);

    QPushButton *printPage = new QPushButton;
    printPage->setIcon(QIcon("Image/print.png"));
    printPage->setIconSize(QSize(30,30));
    printPage->setFlat(true);

    pGLayout2->addWidget(printPage,1,0,1,1);

    //...............................................

    QGroupBox *groupDelai = new QGroupBox("Jour ecoule");
    pGLayout1->addWidget(groupDelai,0,4,1,1);

    QGridLayout *g = new QGridLayout;
    groupDelai->setLayout(g);

    delai = new QLCDNumber;
    delai->display(setDelaisJour());
    g->addWidget(delai,0,0);

    //.....................................................

    QGroupBox *groupComptInfo = new QGroupBox("Info sur le compte");
    pGLayout1->addWidget(groupComptInfo,1,4,1,1);

    QFormLayout *f0 = new QFormLayout;
    groupComptInfo->setLayout(f0);

    dateInscrip = new QLabel("---");
    f0->addRow("Date d'inscription:",dateInscrip);

    group = new QLabel("---");
    f0->addRow("Groupe:",group);

    mtnt = new QLabel("---");
    f0->addRow("Montant commence:",mtnt);

    QPushButton *refreshBtn = new QPushButton;
    refreshBtn->setToolTip("Refresh");
    refreshBtn->setFixedSize(40,40);
    refreshBtn->setIcon(QIcon("Image/refresh.png"));
    refreshBtn->setIconSize(QSize(30,30));
    refreshBtn->setFlat(true);
    pGLayout2->addWidget(refreshBtn,2,0,1,1);


    QObject::connect(printPage,SIGNAL(clicked()),this,SLOT(imprimer()));
    QObject::connect(chercher,SIGNAL(clicked()),this,SLOT(chercher()));
    QObject::connect(refreshBtn,SIGNAL(clicked()),this,SLOT(refresh()));

    return transactionTab;
}

QString Fen_ClientProfile::getDates(){

    //Load all dates in the table
    QList<QDate> dateList;
    querry.prepare("SELECT DATE FROM transaction_table_6");
    if(querry.exec())
        while(querry.next())
            if(!dateList.contains(QDate::fromString(querry.value(0).toString(),"dd/MM/yyyy")))
                dateList.append(QDate::fromString(querry.value(0).toString(),"dd/MM/yyyy"));

    //Create date list of QDate type
    QStringList dateListString;

    //Fill the date list and convert it to string
    for(int i=0;i<dateList.size();i++)
        if(date1->date().operator <=(dateList.at(i)) &  date2->date().operator >=(dateList.at(i)))
            dateListString.append("'"+dateList.at(i).toString("dd/MM/yyyy")+"'");

    //Separate the items of the list whith comma(,) and convert it to string
    QString reqDate = dateListString.join(",");

    return reqDate;
}



void Fen_ClientProfile::setDataTransaction()
{
    getSolde();
    //infoTabTransac[0]->setText(QString::number(nbreDepot));
    infoTabTransac[1]->setText(QString::number(totDebit));
    //infoTabTransac[2]->setText(QString::number(nbreRetrait));
    infoTabTransac[3]->setText(QString::number(totCredit));
    infoTabTransac[4]->setText(QString::number(solde));
}


int Fen_ClientProfile::getSolde()
{

    solde = 0;
    totDebit = 0;
    totCredit = 0;
    qteDepot = 0;
    qteRetrait = 0;


    querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+foreign_id+" "+req);
    while(querry.next())
    {
        totCredit += querry.value(4).toInt();
        totDebit += querry.value(5).toInt();
    }

    querry.finish();

    solde = totDebit - totCredit;

    querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+foreign_id+" "+req);
    while(querry.next())
    {
        qteDepot++;
    }

    infoTabTransac[0]->setText(QString::number(qteDepot));
    querry.finish();


    querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+foreign_id+" AND DESCRIPTION "+req);
    while(querry.next())
    {
        qteRetrait++;
    }

    infoTabTransac[2]->setText(QString::number(qteRetrait));
    querry.finish();

    return solde;
}


void Fen_ClientProfile::imprimer()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution );

    QPrintPreviewDialog *preview = new QPrintPreviewDialog(printer,this);
    preview->setMinimumWidth(800);

    connect(preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    preview->exec();
}

void Fen_ClientProfile::print(QPrinter *printer)
{
    QPainter painter;
    painter.begin(printer);

    int      w = printer->pageRect().width();
    int      h = printer->pageRect().height();
    QRect    page( 0, 0, w, h );

    // create a font appropriate to page size
    QFont    font = painter.font();
    font.setPixelSize( (w+h) / 150 );
    painter.setFont( font );

    addHeader(&painter,page,printer);
    // draw simulated landscape
    page.adjust( w/20, h/20, -w/20, -h/20 );

    painter.end();

}


void Fen_ClientProfile::addHeader(QPainter *painter, QRect page,QPrinter *printer)
{
    // draw labels in corners of page
    painter->drawText( page, Qt::AlignTop, "Etat de compte du client" );
    painter->drawText( page, Qt::AlignTop | Qt::AlignRight,QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm AP"));

    painter->drawImage(100,200,QImage(PicName).scaled(1500,1500,Qt::KeepAspectRatio));
    painter->drawText(1900,200,"ID: "+pTableauInfo[0]->text());
    painter->drawText(1900,300,"Titre: "+pTableauInfo[1]->text());
    painter->drawText(1900,400,"Nom: "+pTableauInfo[2]->text());
    painter->drawText(1900,500,"Prenom: "+pTableauInfo[3]->text());
    painter->drawText(1900,600,"Date de naissance: "+pTableauInfo[4]->text());
    painter->drawText(1900,700,"Type de piece: "+pTableauInfo[5]->text());
    painter->drawText(1900,800,"No. de la piece: "+pTableauInfo[6]->text());
    painter->drawText(1900,900,"Sexe: "+pTableauInfo[7]->text());
    painter->drawText(1900,1000,"Nom de la mere: "+pTableauInfo[8]->text());
    //-------------------------------------------
    painter->drawText(3300,200,"Telephone 1: "+tel_TableauInfo[0]->text());
    painter->drawText(3300,300,"Telephone 2: "+tel_TableauInfo[1]->text());
    painter->drawText(3300,400,"Adresse: "+tel_TableauInfo[2]->text());
    //-------------------------------------------
    painter->drawText(3300,700,"Date d'inscription: "+dateInscrip->text());
    painter->drawText(3300,800,"Groupe: "+group->text());
    painter->drawText(3300,900,"Montant commenc"+QString::fromUtf8("é")+": "+mtnt->text());

    painter->drawLine(100,1300,5000,1300);

    int y = 1500;
    painter->drawText(100,y ,"DATE" );
    painter->drawText(550,y ,"HEURE" );
    painter->drawText(950,y ,"DESCRIPTION" );
    painter->drawText(1550,y ,"RETRAITS" );
    painter->drawText(2050,y ,"DEPOTS" );
    painter->drawText(2450,y ,"JOURS" );
    painter->drawText(2800,y ,"SOLDE" );
    painter->drawText(3200,y ,"PAR QUI?" );
    painter->drawText(3650,y ,"#RETRAIT" );
    painter->drawText(4100,y ,"ID CLIENT" );
    painter->drawText(4500,y ,"GROUPE" );


    painter->drawLine(100,y+30,5000,y+30);
    painter->drawLine(100,y+50,5000,y+50);

    addText(painter,printer);
}

void Fen_ClientProfile::addText(QPainter *painter,QPrinter *printer)
{

    int y = 1700;
    int lines = 0;
    chercher();


    querry.prepare("SELECT * FROM transaction_table_6  WHERE ID_CLIENT = "+pTableauInfo[0]->text()+" "+req+" ");
    if(querry.exec())
    {
        while(querry.next())
        {
            painter->drawText(100,y ,querry.value(1).toString() );
            painter->drawText(550,y ,querry.value(2).toString() );
            painter->drawText(950,y ,querry.value(3).toString() );
            painter->drawText(1550,y ,querry.value(4).toString() );
            painter->drawText(2050,y ,querry.value(5).toString());
            painter->drawText(2450,y ,querry.value(6).toString() );
            painter->drawText(2800,y ,querry.value(7).toString() );
            painter->drawText(3200,y ,querry.value(8).toString() );
            painter->drawText(3650,y ,querry.value(9).toString() );
            painter->drawText(4100,y ,querry.value(10).toString() );
            painter->drawText(4500,y ,querry.value(11).toString() );

            painter->drawLine(100,y+30,5000,y+30);

            if(lines == 35 )
            {
                printer->newPage();
                lines = 0;
                y = 400;
            }

            lines++;
            y +=150;
        }
    }

    addFooter(painter);
}


void Fen_ClientProfile::addFooter(QPainter *painter)
{
    painter->drawLine(100,5800,5000,5800);

    painter->drawText(100,5900 ,"R"+QString::fromUtf8("é")+"sum"+QString::fromUtf8("é")+" des transactions" );

    painter->drawText(100,6100 ,"Nombre de depots: "+QString::number(qteDepot) );
    painter->drawText(100,6300 ,"Nombre de retraits: "+QString::number(qteRetrait) );

    painter->drawText(1500,6100 ,"Total des depots: "+QString::number(totDebit) );
    painter->drawText(1500,6300 ,"Total des retraits: "+QString::number(totCredit) );

    painter->drawText(3000,6100 ,"Solde: "+QString::number(solde) );
}


void Fen_ClientProfile::chercher()
{
    req = " ("+getDates()+") ";

    if(check1->isChecked()){
        if(check2->isChecked())
            req = " AND DATE IN "+req;
        else
           req = "AND DESCRIPTION = 'DEPOT' AND DATE IN "+req;
    }else
        if(check2->isChecked())
            req = "AND DESCRIPTION = 'RETRAIT' AND DATE IN "+req;

    modelTransaction->setFilter("ID_CLIENT = "+pTableauInfo[0]->text()+" "+req);
    modelTransaction->select();

    //setDataTransaction();
    int solde = getSolde();

    infoTabTransac[0]->setText(QString::number(qteDepot));
    infoTabTransac[1]->setText(QString::number(totDebit));
    infoTabTransac[2]->setText(QString::number(qteRetrait));
    infoTabTransac[3]->setText(QString::number(totCredit));
    infoTabTransac[4]->setText(QString::number(solde));


    //qDebug()<<req;

}

void Fen_ClientProfile::refresh()
{
    modelTransaction->setFilter("ID_CLIENT = "+pTableauInfo[0]->text());
    modelTransaction->select();

    int solde = getSolde();

    infoTabTransac[0]->setText(QString::number(qteDepot));
    infoTabTransac[1]->setText(QString::number(totDebit));
    infoTabTransac[2]->setText(QString::number(qteRetrait));
    infoTabTransac[3]->setText(QString::number(totCredit));
    infoTabTransac[4]->setText(QString::number(solde));

}


