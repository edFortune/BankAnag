#include "fen_listetransaction.h"

Fen_ListeTransaction::Fen_ListeTransaction(QWidget *parent) :
    QWidget(parent)
{

}


Fen_ListeTransaction::Fen_ListeTransaction(QSqlQuery q)
{
    querry = q;

    if(querry.exec("SELECT id FROM liste_client_6 WHERE Statut = 'En cours' "))
        while(querry.next())
            listeClientActif.append("'"+querry.value(0).toString()+"'");


    qDebug()<<"Total of client actif is: "<<listeClientActif.count();
    QString listeClient = listeClientActif.join(",");
    QString reqClientActif = "ID_CLIENT IN ( "+listeClient+" )";

    LayoutLister = new QGridLayout;
    LayoutLister->setSpacing(5);
    this->setLayout(LayoutLister);

    model = new QSqlTableModel;
    model->setTable(QString("transaction_table_6"));
    model->setHeaderData(6,Qt::Horizontal,"NBRE DE JOURS");
    model->setHeaderData(8,Qt::Horizontal,"PAR QUI?");
    model->setHeaderData(9,Qt::Horizontal,"No. RETRAIT");
    model->setHeaderData(10,Qt::Horizontal,"ID CLIENT");
    //model->setHeaderData(12,Qt::Horizontal,"PHOTO DE LA FICHE DE RETRAIT");

    model->setFilter(reqClientActif);
    model->select();

    table = new QTableView;
    table->setModel(model);
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->resizeColumnsToContents();
    table->setMinimumHeight(400);
    table->setColumnWidth(0,80);
    table->setColumnWidth(1,90);
    table->setColumnWidth(7,100);
    table->hideColumn(12);
    table->setItemDelegate(new Fen_Transaction_delegate(table));

    LayoutLister->addWidget(table,1,1,6,8);


    bimprimer = new QPushButton;
    bimprimer->setToolTip("Imprimer");
    bimprimer->setFixedSize(40,40);
    bimprimer->setIcon(QIcon("Image/printIcon.png"));
    bimprimer->setIconSize(QSize(30,30));
    LayoutLister->addWidget(bimprimer,1,0);

    QPushButton *refreshBtn = new QPushButton;
    refreshBtn->setToolTip("Refresh");
    refreshBtn->setFixedSize(40,40);
    refreshBtn->setIcon(QIcon("Image/refresh.png"));
    refreshBtn->setIconSize(QSize(30,30));
    LayoutLister->addWidget(refreshBtn,2,0,1,1);

    brecherche = new QPushButton;
    brecherche->setToolTip("Rechercher");
    brecherche->setFixedSize(40,40);
    brecherche->setIcon(QIcon("Image/searchIcon.png"));
    brecherche->setIconSize(QSize(30,30));
    LayoutLister->addWidget(brecherche,3,0,1,1);

    bsupprimer = new QPushButton;
    bsupprimer->setToolTip("Supprimer");
    bsupprimer->setFixedSize(40,40);
    bsupprimer->setIcon(QIcon("Image/deleteIcon.png"));
    bsupprimer->setIconSize(QSize(30,30));



    QHBoxLayout *hLayout = new QHBoxLayout;
    LayoutLister->addLayout(hLayout,0,1,1,6);

    QComboBox *comCustom = new QComboBox;
    comCustom->addItem("Tout");
    comCustom->addItem("Aujourd'hui");
    hLayout->addWidget(comCustom);

    dateEdit = new QDateEdit;
    dateEdit->setCalendarPopup(true);
    dateEdit->setDate(QDate::fromString("04/07/2016","dd/MM/yyyy"));
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    hLayout->addWidget(dateEdit);

    dateEdit2 = new QDateEdit;
    dateEdit2->setCalendarPopup(true);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setDisplayFormat("dd/MM/yyyy");
    hLayout->addWidget(dateEdit2);

    validerDate = new QPushButton("Cliquer ici");
    //ButtonRoundStyle(validerDate);
    validerDate->setStyleSheet("background-color:#344956;color:white");
    hLayout->addWidget(validerDate);

    getsolde();

    QLabel *totaldep = new QLabel;
    totaldep->setText(QLocale(QLocale::English).toString(totDebit)+" HTG");
    LayoutLister->addWidget(string_and_label_ColorWidgetStyle("Total des depots","#344956",totaldep,"#27ae60"),7,1,1,1);

    QLabel *totalret = new QLabel;
    totalret->setText(QLocale(QLocale::English).toString(totCredit)+" HTG");
    LayoutLister->addWidget(string_and_label_ColorWidgetStyle("Total des retraits","#344956",totalret,"#DB532B"),7,3,1,1);

    QLabel *totalTransac = new QLabel;
    totalTransac->setText(QLocale(QLocale::English).toString(getsolde())+" HTG");
    LayoutLister->addWidget(string_and_label_ColorWidgetStyle("Solde","#344956",totalTransac,"blue"),7,5,1,1);



    QVBoxLayout *vLayoutQteGroupe = new QVBoxLayout;
    vLayoutQteGroupe->setSpacing(0);
    vLayoutQteGroupe->setMargin(0);
    LayoutLister->addLayout(vLayoutQteGroupe,1,9,6,1);

    QLabel *qteGroupeTitre = new QLabel("Quantite par groupe");
    qteGroupeTitre->setStyleSheet("background-color:#344956;color:white");
    qteGroupeTitre->setAlignment(Qt::AlignCenter);
    qteGroupeTitre->setMargin(5);
    qteGroupeTitre->setMinimumWidth(220);
    vLayoutQteGroupe->addWidget(qteGroupeTitre);

    r_group25 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 25",r_group25));


    r_group50 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 50",r_group50));

    r_group100 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 100",r_group100));

    r_group250 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 250",r_group250));


    QLabel *totRetraitTitre = new QLabel("Total des retraits par groupe");
    totRetraitTitre->setStyleSheet("background-color:#344956;color:white");
    totRetraitTitre->setAlignment(Qt::AlignCenter);
    totRetraitTitre->setMargin(5);
    vLayoutQteGroupe->addWidget(totRetraitTitre);


    r2_group25 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 25",r2_group25));

    r2_group50 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 50",r2_group50));

    r2_group100 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 100",r2_group100));

    r2_group250 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 250",r2_group250));


    QLabel *totDepotTitre = new QLabel("Total des depots par groupe");
    totDepotTitre->setStyleSheet("background-color:#344956;color:white");
    totDepotTitre->setAlignment(Qt::AlignCenter);
    totDepotTitre->setMargin(5);
    vLayoutQteGroupe->addWidget(totDepotTitre);


    r1_group25 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 25",r1_group25));


    r1_group50 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 50",r1_group50));

    r1_group100 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 100",r1_group100));

    r1_group250 = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Groupe 250",r1_group250));



    QLabel *mtntTotalTitre = new QLabel("Montant totaux des recherches");
    mtntTotalTitre->setStyleSheet("background-color:#344956;color:white");
    mtntTotalTitre->setAlignment(Qt::AlignCenter);
    mtntTotalTitre->setMargin(5);
    vLayoutQteGroupe->addWidget(mtntTotalTitre);

    resultdepot = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Total des depots",resultdepot));

    resultretrait = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Total des retraits",resultretrait));

    resultsolde = new QLabel("---");
    vLayoutQteGroupe->addWidget(string_and_label_WidgetStyle("Solde",resultsolde));

    //*********************************************
    req = "ID >0";


//    QStringList listCode;
//    if(querry.exec("SELECT * FROM liste_client_6"))
//        while(querry.next())
//            listCode.append(querry.value(0).toString());

//    QString reqUpdate = listCode.join(",");
//    qDebug()<<reqUpdate;

//    if(querry.exec("UPDATE transaction_table_6 SET DELIVRE = 'Oui' WHERE ID_CLIENT IN ("+reqUpdate+")"))
//        qDebug()<<"Oui is insert";
//    else
//        qDebug()<<querry.lastError();




    QObject::connect(comCustom,SIGNAL(activated(int)),this,SLOT(choisirRecherche(int)));
    QObject::connect(validerDate,SIGNAL(clicked()),this,SLOT(chercherDate()));

    QObject::connect(refreshBtn,SIGNAL(clicked()),this,SLOT(refresh()));
    QObject::connect(bimprimer,SIGNAL(clicked()),this,SLOT(imprimer()));
    QObject::connect(brecherche,SIGNAL(clicked()),this,SLOT(showDialogRecherche()));

}

void Fen_ListeTransaction::showDialogRecherche()
{
    QDialog *diag = new QDialog;
    diag->setModal(true);

    QVBoxLayout *v = new QVBoxLayout;
    diag->setLayout(v);

    comRech = new QComboBox;
    comRech->addItem("DESCRIPTION");
    comRech->addItem("N_JOURS");
    comRech->addItem("No_Retrait");
    comRech->addItem("PAR_QUI");
    comRech->addItem("ID_CLIENT");
    comRech->addItem("GROUPE");
    v->addWidget(comRech);

    editRecherch = new QLineEdit;
    v->addWidget(editRecherch);

    bvalider = new QPushButton("Rechercher");
    v->addWidget(bvalider);

    QObject::connect(bvalider,SIGNAL(clicked()),this,SLOT(chercherDonnee()));


    diag->show();
}


int Fen_ListeTransaction::getsolde()
{
    solde = 0;
    totDebit = 0;
    totCredit = 0;

    querry.prepare("SELECT SUM(DEPOTS), SUM(RETRAITS) FROM transaction_table_6 "
                   "WHERE ID_CLIENT IN (SELECT id FROM liste_client_6 WHERE Statut = 'En cours') ");
    if(querry.exec())
        if(querry.first())
        {
            totDebit = querry.value(0).toInt();
            totCredit = querry.value(1).toInt();
        }
    solde = totDebit - totCredit;
    return solde;
}


void Fen_ListeTransaction::getsoldeResultat()
{
    int c = 0;

    //------quantite de groupe -------
    int qte25=0,qte50=0,qte100=0,qte250=0;
    //------total des depots----------
    int depot25=0,depot50=0,depot100=0,depot250=0;
    //------total des retraits--------
    int retrait25=0,retrait50=0,retrait100=0,retrait250=0;

    QString requete = "";

    solde = 0;
    totDebit = 0;
    totCredit = 0;

    for(int i = 0; i<editRecherch->text().size();i++){
         if(editRecherch->text()[i]>='0' && editRecherch->text()[i]<='9'){
             c++;
         }
     }

    QString listeClient = listeClientActif.join(",");
    QString reqClientActif = "AND ID_CLIENT IN ("+listeClient+")";

    if(c == editRecherch->text().size() )
        requete = " "+comRech->currentText()+" = " +editRecherch->text()+ " "+reqClientActif+" ";
    else
        requete = " "+comRech->currentText()+" = '" +editRecherch->text()+ "' "+reqClientActif+" ";

    querry.prepare("SELECT GROUPE, COUNT(GROUPE), SUM(DEPOTS), SUM(RETRAITS) "
                   "FROM transaction_table_6 WHERE "+requete+" GROUP BY GROUPE ORDER BY GROUPE ");
    if(querry.exec())
        while(querry.next())
        {
            qDebug()<<"Groupe: "<<querry.value(0).toString()<<"Qty: "<<querry.value(1).toString();
            if(querry.value(0).toInt()==25)
            {
                qte25 = querry.value(1).toInt();
                depot25 = querry.value(2).toInt();
                retrait25 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==50)
            {
                qte50 = querry.value(1).toInt();
                depot50 = querry.value(2).toInt();
                retrait50 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==100)
            {
                qte100 = querry.value(1).toInt();
                depot100 = querry.value(2).toInt();
                retrait100 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==250)
            {
                qte250 = querry.value(1).toInt();
                depot250 = querry.value(2).toInt();
                retrait250 = querry.value(3).toInt();
            }
            totDebit += querry.value(2).toInt();
            totCredit += querry.value(3).toInt();
        }

    solde = totDebit - totCredit;
    //-----------------groupe------------------------------
    r_group25->setText(QLocale(QLocale::English).toString(qte25));
    r_group50->setText(QLocale(QLocale::English).toString(qte50));
    r_group100->setText(QLocale(QLocale::English).toString(qte100));
    r_group250->setText(QLocale(QLocale::English).toString(qte250));
    //------------------depot-----------------------------
    r1_group25->setText(QLocale(QLocale::English).toString(depot25));
    r1_group50->setText(QLocale(QLocale::English).toString(depot50));
    r1_group100->setText(QLocale(QLocale::English).toString(depot100));
    r1_group250->setText(QLocale(QLocale::English).toString(depot250));
    //------------------retrait-----------------------------
    r2_group25->setText(QLocale(QLocale::English).toString(retrait25));
    r2_group50->setText(QLocale(QLocale::English).toString(retrait50));
    r2_group100->setText(QLocale(QLocale::English).toString(retrait100));
    r2_group250->setText(QLocale(QLocale::English).toString(retrait250));
    //------------------------------------------------
    resultdepot->setText(QLocale(QLocale::English).toString(totDebit));
    resultretrait->setText(QLocale(QLocale::English).toString(totCredit));
    resultsolde->setText(QLocale(QLocale::English).toString(solde));
}


void Fen_ListeTransaction::choisirRecherche(int i)
{
    if(i == 1)
    {
        dateEdit->setDate(QDate::fromString(QDate::currentDate().toString("dd/MM/yyyy"),"dd/MM/yyyy"));
        dateEdit2->setDate(QDate::fromString(QDate::currentDate().toString("dd/MM/yyyy"),"dd/MM/yyyy"));
        chercherDate();
    }else{
        dateEdit->setDate(QDate::fromString("04/07/2016","dd/MM/yyyy"));
        dateEdit2->setDate(QDate::currentDate());
        dateEdit2->setDisplayFormat("dd/MM/yyyy");
        chercherDate();
    }
}

void Fen_ListeTransaction::chercherDate()
{
    //------quantite de groupe -------
    int qte25=0,qte50=0,qte100=0,qte250=0;
    //------total des depots----------
    int depot25=0,depot50=0,depot100=0,depot250=0;
    //------total des retraits--------
    int retrait25=0,retrait50=0,retrait100=0,retrait250=0;

    //Load all dates in the table
    QList<QDate> dateList;
    querry.prepare("SELECT DISTINCT DATE FROM transaction_table_6 "
                   "WHERE ID_CLIENT IN (SELECT id FROM liste_client_6 WHERE Statut = 'En cours') ") ;
    if(querry.exec())
        while(querry.next())
                dateList.append(QDate::fromString(querry.value(0).toString(),"dd/MM/yyyy"));

    //Create date list of QDate type
    QStringList dateListString;

    //Fill the date list and convert it to string
    for(int i=0;i<dateList.size();i++)
        if(dateEdit->date().operator <=(dateList.at(i)) &&  dateEdit2->date().operator >=(dateList.at(i)))
            dateListString.append("'"+dateList.at(i).toString("dd/MM/yyyy")+"'");

    //Separate the items of the list whith comma(,) and convert it to string
    QString reqDate = dateListString.join(",");

    model->setFilter("DATE IN ("+reqDate+")");

    solde = 0;
    totDebit = 0;
    totCredit = 0;

    querry.prepare("SELECT GROUPE, COUNT(GROUPE), SUM(DEPOTS), SUM(RETRAITS) "
                   "FROM transaction_table_6 WHERE DATE IN ("+reqDate+") "
                   "GROUP BY GROUPE ORDER BY GROUPE ");
    if(querry.exec())
        while(querry.next())
        {
            if(querry.value(0).toInt()==25)
            {
                qte25 = querry.value(1).toInt();
                depot25 = querry.value(2).toInt();
                retrait25 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==50)
            {
                qte50 = querry.value(1).toInt();
                depot50 = querry.value(2).toInt();
                retrait50 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==100)
            {
                qte100 = querry.value(1).toInt();
                depot100 = querry.value(2).toInt();
                retrait100 = querry.value(3).toInt();

            }else if(querry.value(0).toInt()==250)
            {
                qte250 = querry.value(1).toInt();
                depot250 = querry.value(2).toInt();
                retrait250 = querry.value(3).toInt();
            }
            totDebit += querry.value(2).toInt();
            totCredit += querry.value(3).toInt();
        }


    solde = totDebit - totCredit;
    //-----------------groupe------------------------------
    r_group25->setText(QLocale(QLocale::English).toString(qte25));
    r_group50->setText(QLocale(QLocale::English).toString(qte50));
    r_group100->setText(QLocale(QLocale::English).toString(qte100));
    r_group250->setText(QLocale(QLocale::English).toString(qte250));
    //------------------depot-----------------------------
    r1_group25->setText(QLocale(QLocale::English).toString(depot25));
    r1_group50->setText(QLocale(QLocale::English).toString(depot50));
    r1_group100->setText(QLocale(QLocale::English).toString(depot100));
    r1_group250->setText(QLocale(QLocale::English).toString(depot250));
    //------------------retrait-----------------------------
    r2_group25->setText(QLocale(QLocale::English).toString(retrait25));
    r2_group50->setText(QLocale(QLocale::English).toString(retrait50));
    r2_group100->setText(QLocale(QLocale::English).toString(retrait100));
    r2_group250->setText(QLocale(QLocale::English).toString(retrait250));
    //------------------------------------------------

    resultdepot->setText(QLocale(QLocale::English).toString(totDebit));
    resultretrait->setText(QLocale(QLocale::English).toString(totCredit));
    resultsolde->setText(QLocale(QLocale::English).toString(solde));

    req = "DATE IN ("+reqDate+")";


}

void Fen_ListeTransaction::chercherDonnee()
{
    QString listeClient = listeClientActif.join(",");
    QString reqClientActif = "ID_CLIENT IN ("+listeClient+")";

   int c = 0;
    for(int i = 0; i<editRecherch->text().size();i++){
        if(editRecherch->text()[i]>='0' && editRecherch->text()[i]<='9'){
            c++;
        }
    }

    if(c == editRecherch->text().size())
    {
        model->setFilter(" "+comRech->currentText()+" = " +editRecherch->text()+ " AND "+reqClientActif+" ");
        model->select();
        req = " "+comRech->currentText()+" = " +editRecherch->text()+ " AND "+reqClientActif+" ";
        getsoldeResultat();
    }else
    {
        model->setFilter(" "+comRech->currentText()+" = '" +editRecherch->text()+ "' AND "+reqClientActif+" ");
        model->select();
        req = " "+comRech->currentText()+" = '" +editRecherch->text()+ "' AND "+reqClientActif+" ";
        getsoldeResultat();
    }
}


void Fen_ListeTransaction::refresh()
{
    QString listeClient = listeClientActif.join(",");
    QString reqClientActif = "ID_CLIENT IN ("+listeClient+")";

    model->setFilter(" ID > 0 AND "+reqClientActif+" ");
    model->select();

    //-----------------groupe------------------------------
    r_group25->setText("---");
    r_group50->setText("---");
    r_group100->setText("---");
    r_group250->setText("---");
    //------------------depot-----------------------------
    r1_group25->setText("---");
    r1_group50->setText("---");
    r1_group100->setText("---");
    r1_group250->setText("---");
    //------------------retrait-----------------------------
    r2_group25->setText("---");
    r2_group50->setText("---");
    r2_group100->setText("---");
    r2_group250->setText("---");

    resultdepot->setText("---");
    resultretrait->setText("---");
    resultsolde->setText("---");
    //getsoldeResultat();

}


void Fen_ListeTransaction::imprimer()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution );

    QPrintPreviewDialog *preview = new QPrintPreviewDialog(printer,this);
    preview->setMinimumWidth(700);
    preview->setMinimumHeight(500);

    connect(preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    preview->exec();
}

void Fen_ListeTransaction::print(QPrinter *printer)
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


void Fen_ListeTransaction::addHeader(QPainter *painter, QRect page,QPrinter *printer)
{
    // draw labels in corners of page
    painter->drawText( page, Qt::AlignTop    | Qt::AlignLeft, "Rapport des transactions" );
    painter->drawText( page, Qt::AlignTop | Qt::AlignRight,QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm AP") );

    painter->drawText(100,200,"De: "+dateEdit->date().toString("dd/MM/yyyy"));
    painter->drawText(100,300,"a: "+dateEdit2->date().toString("dd/MM/yyyy"));

    int y = 500;
    painter->drawText(100,y ,"DATE" );
    painter->drawText(600,y ,"HEURE" );
    painter->drawText(1200,y ,"DESCRIPTION" );
    painter->drawText(1800,y ,"RETRAITS" );
    painter->drawText(2300,y ,"DEPOTS" );
    painter->drawText(2700,y ,"QTE. JOUR" );
    painter->drawText(3200,y ,"SOLDE" );
    painter->drawText(3500,y ,"#RETRAIT");
    painter->drawText(3900,y ,"ID CLIENT" );
    painter->drawText(4300,y ,"GROUPE" );
    painter->drawText(4600,y ,"DLV" );


    painter->drawLine(100,y+30,5000,y+30);
    painter->drawLine(100,y+50,5000,y+50);

    addText(painter,printer);


}

void Fen_ListeTransaction::addText(QPainter *painter,QPrinter *printer)
{
    int y = 700;
    int lines = 0;

    querry.prepare("SELECT * FROM transaction_table_6 WHERE "+req+" ");
    bool c = querry.exec();
    if(c)
    {
        while(querry.next())
        {
            painter->drawText(100,y ,querry.value(1).toString() );
            painter->drawText(600,y ,querry.value(2).toString() );
            painter->drawText(1200,y ,querry.value(3).toString() );
            painter->drawText(1800,y ,querry.value(4).toString() );
            painter->drawText(2300,y ,querry.value(5).toString());
            painter->drawText(2700,y ,querry.value(6).toString() );
            painter->drawText(3200,y ,querry.value(7).toString() );
            painter->drawText(3500,y ,querry.value(9).toString() );
            painter->drawText(3900,y ,querry.value(10).toString() );
            painter->drawText(4300,y ,querry.value(11).toString() );
            painter->drawText(4600,y ,querry.value(13).toString() );

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


void Fen_ListeTransaction::addFooter(QPainter *painter)
{
    painter->drawLine(100,5800,5000,5800);

    painter->drawText(100,5900 ,"Qte par groupe" );
    painter->drawText(100,6000 ,"Groupe 25: "+r_group25->text() );
    painter->drawText(100,6100 ,"Groupe 50: "+r_group50->text() );
    painter->drawText(100,6200 ,"Groupe 100: "+r_group100->text() );
    painter->drawText(100,6300 ,"Groupe 250: "+r_group250->text() );


    painter->drawText(900,5900 ,"Total des retraits par groupe" );
    painter->drawText(900,6000 ,"Groupe 25: "+r2_group25->text() );
    painter->drawText(900,6100 ,"Groupe 50: "+r2_group50->text() );
    painter->drawText(900,6200 ,"Groupe 100: "+r2_group100->text() );
    painter->drawText(900,6300 ,"Groupe 250: "+r2_group250->text() );

    painter->drawText(2200,5900 ,"Total des depots par groupe" );
    painter->drawText(2200,6000 ,"Groupe 25: "+r1_group25->text() );
    painter->drawText(2200,6100 ,"Groupe 50: "+r1_group50->text() );
    painter->drawText(2200,6200 ,"Groupe 100: "+r1_group100->text() );
    painter->drawText(2200,6300 ,"Groupe 250: "+r1_group250->text() );

    painter->drawText(3700,5900 ,"Montants totaux" );
    painter->drawText(3700,6000 ,"Total des depots: "+resultdepot->text() );
    painter->drawText(3700,6100 ,"Total des retraits: "+resultretrait->text() );
    painter->drawText(3700,6200 ,"Solde: "+resultsolde->text() );

}
