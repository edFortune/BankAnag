#include "fen_rapportgeneral.h"


QWidget* Fen_RapportGeneral::rapportGeneral_transaction()
{
    widParent_transaction = new QWidget;




    return widParent_transaction;
}

void Fen_RapportGeneral::result_transaction()
{
    transac_depot = 0, transac_retrait = 0, transac_diff = 0;
    transac_depot25 = 0, transac_depot50 = 0, transac_depot100 = 0,transac_depot250 = 0,transac_totaldepot=0;
    transac_retrait25 = 0, transac_retrait50 = 0, transac_retrait100 = 0,transac_retrait250 = 0,transac_totalretrait=0;
    transac_diff25 = 0, transac_diff50 = 0, transac_diff100 = 0, transac_diff250 = 0;

    querry.exec("SELECT * FROM transaction_table_6");
    while(querry.next())
    {
        transac_depot += querry.value(5).toInt();
        transac_retrait += querry.value(4).toInt();

        if(querry.value(11).toInt()==25)
            transac_depot25+= querry.value(5).toInt();
        else if(querry.value(11).toInt()==50)
            transac_depot50+= querry.value(5).toInt();
        else if(querry.value(11).toInt()==100)
            transac_depot100+= querry.value(5).toInt();
        else if(querry.value(11).toInt()==250)
            transac_depot250+= querry.value(5).toInt();


        if(querry.value(11).toInt()==25)
            transac_retrait25+= querry.value(4).toInt();
        else if(querry.value(11).toInt()==50)
            transac_retrait50+= querry.value(4).toInt();
        else if(querry.value(11).toInt()==100)
            transac_retrait100+= querry.value(4).toInt();
        else if(querry.value(11).toInt()==250)
            transac_retrait250+= querry.value(4).toInt();
    }


    transac_totaldepot = transac_depot25 + transac_depot50 + transac_depot100 + transac_depot250;
    transac_totalretrait = transac_retrait25 + transac_retrait50 + transac_retrait100 + transac_retrait250;
    transac_diff = transac_depot - transac_retrait;

    transac_diff25 = transac_depot25 - transac_retrait25;
    transac_diff50 = transac_depot50 - transac_retrait50;
    transac_diff100 = transac_depot100 - transac_retrait100;
    transac_diff250 = transac_depot250 - transac_retrait250;

    if(widParent_transaction->children().size()<=0){
        QVBoxLayout *vbox = new QVBoxLayout;
        widParent_transaction->setLayout(vbox);

        vbox->addWidget(add_WidgetRapportTransaction());
        vbox->addWidget(add_WidgetRapportTransactionDepot());
        vbox->addWidget(add_WidgetRapportTransactionRetrait());
        vbox->addWidget(add_WidgetRapportTransactionSolde());
    }

}



QWidget* Fen_RapportGeneral::add_WidgetRapportTransaction()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#008080;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Transaction: "+QLocale(QLocale::English).toString(transac_diff));
    lab_titre->setStyleSheet("background-color:#33A1C9;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,3);


    grid->addWidget(add_styleHeader("Depots","#33A1C9",QLocale(QLocale::English).toString(transac_depot),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Retraits","#33A1C9",QLocale(QLocale::English).toString(transac_retrait),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Difference","#33A1C9",QLocale(QLocale::English).toString(transac_diff),"#344956"),1,2);


    return wid;

}



QWidget* Fen_RapportGeneral::add_WidgetRapportTransactionDepot()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#008080;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Transaction - Depots: "+QLocale(QLocale::English).toString(transac_totaldepot));
    lab_titre->setStyleSheet("background-color:#33A1C9;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,4);


    grid->addWidget(add_styleHeader("Groupe 25","#33A1C9",QLocale(QLocale::English).toString(transac_depot25),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Groupe 50","#33A1C9",QLocale(QLocale::English).toString(transac_depot50),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Groupe 100","#33A1C9",QLocale(QLocale::English).toString(transac_depot100),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Groupe 250","#33A1C9",QLocale(QLocale::English).toString(transac_depot250),"#344956"),1,3);


    return wid;
}


QWidget* Fen_RapportGeneral::add_WidgetRapportTransactionRetrait()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#008080;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Transaction - Retraits: "+QLocale(QLocale::English).toString(transac_totalretrait));
    lab_titre->setStyleSheet("background-color:#33A1C9;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,4);


    grid->addWidget(add_styleHeader("Groupe 25","#33A1C9",QLocale(QLocale::English).toString(transac_retrait25),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Groupe 50","#33A1C9",QLocale(QLocale::English).toString(transac_retrait50),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Groupe 100","#33A1C9",QLocale(QLocale::English).toString(transac_retrait100),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Groupe 250","#33A1C9",QLocale(QLocale::English).toString(transac_retrait250),"#344956"),1,3);


    return wid;

}




QWidget* Fen_RapportGeneral::add_WidgetRapportTransactionSolde()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#008080;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Transaction - Differences: "+QLocale(QLocale::English).toString(transac_diff));
    lab_titre->setStyleSheet("background-color:#33A1C9;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,4);


    grid->addWidget(add_styleHeader("Groupe 25","#33A1C9",QLocale(QLocale::English).toString(transac_diff25),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Groupe 50","#33A1C9",QLocale(QLocale::English).toString(transac_diff50),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Groupe 100","#33A1C9",QLocale(QLocale::English).toString(transac_diff100),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Groupe 250","#33A1C9",QLocale(QLocale::English).toString(transac_diff250),"#344956"),1,3);


    return wid;

}
