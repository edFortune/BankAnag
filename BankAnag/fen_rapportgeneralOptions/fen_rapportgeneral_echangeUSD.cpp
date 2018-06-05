#include "fen_rapportgeneral.h"

QWidget* Fen_RapportGeneral::rapportGeneral_echangeUSD()
{
    widParent_echangeUSD = new QWidget;



    return widParent_echangeUSD;


}



QWidget* Fen_RapportGeneral::add_WidgetRapportEchangeUSD()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#DC143C;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Echange US: "+QLocale(QLocale::English).toString(echange_diff));
    lab_titre->setStyleSheet("background-color:#DB7093;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,3);

    grid->addWidget(add_styleHeader("Achat","#DB7093",QLocale(QLocale::English).toString(echange_achat),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Vente","#DB7093",QLocale(QLocale::English).toString(echange_vente),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Difference","#DB7093",QLocale(QLocale::English).toString(echange_diff),"#344956"),1,2);


    return wid;

}

void Fen_RapportGeneral::result_echangeUSD()
{
    echange_achat =0, echange_vente = 0, echange_diff = 0;
    querry.exec("SELECT * FROM rapportEchangeUSDTable");
    while(querry.next())
    {
        echange_achat += querry.value(4).toDouble();
        echange_vente += querry.value(6).toDouble();
    }

    echange_achat = echange_achat*5;
    echange_vente = echange_vente*5;
    echange_diff = echange_vente - echange_achat;

    if(widParent_echangeUSD->children().size()<=0){
        QVBoxLayout *vbox = new QVBoxLayout;
        widParent_echangeUSD->setLayout(vbox);

        vbox->addWidget(add_WidgetRapportEchangeUSD());
    }
}
