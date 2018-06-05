#include "fen_rapportgeneral.h"


QWidget* Fen_RapportGeneral::rapportGeneral_achatVente()
{
    widgetParent_AchatVente = new QWidget;

    return widgetParent_AchatVente;

}



QWidget* Fen_RapportGeneral::add_WidgetRapportAchatVente()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#5D478B;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Investment Report: "+QLocale(QLocale::English).toString(achatVente_diff));
    lab_titre->setStyleSheet("background-color:#AB82FF;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,3);

    grid->addWidget(add_styleHeader("Investment IN","#AB82FF",QLocale(QLocale::English).toString(achatVente_achat),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Investment OUT","#AB82FF",QLocale(QLocale::English).toString(achatVente_vente),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Difference","#AB82FF",QLocale(QLocale::English).toString(achatVente_diff),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Versement","#AB82FF",QLocale(QLocale::English).toString(versementInvestment),"#344956"),2,0,1,3);


    return wid;

}


void Fen_RapportGeneral::result_achatVente()
{
    achatVente_achat =0,achatVente_vente=0,achatVente_diff=0,versementInvestment=0;
    querry.exec("SELECT * FROM investmentTable");
    while(querry.next())
    {
        achatVente_achat += querry.value(3).toDouble();
        achatVente_vente += querry.value(4).toDouble();
    }

    achatVente_achat = achatVente_achat*5;
    achatVente_vente = achatVente_vente*5;
    achatVente_diff = achatVente_vente - achatVente_achat;

    querry.exec("SELECT * FROM versementInvestment");
    while(querry.next())
    {
        versementInvestment += querry.value(3).toDouble();

    }

    if(widgetParent_AchatVente->children().size()<=0){
        QVBoxLayout *vbox = new QVBoxLayout;
        widgetParent_AchatVente->setLayout(vbox);
        vbox->addWidget(add_WidgetRapportAchatVente());
    }

}
