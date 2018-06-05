#include "fen_rapportgeneral.h"


QWidget* Fen_RapportGeneral::rapportGeneral_caisse()
{
    widgetParent_Caisse = new QWidget;



    return widgetParent_Caisse;

}



QWidget* Fen_RapportGeneral::add_WidgetRapportCaisse()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#3D9140;");

    QHBoxLayout *hlayout_caisse = new QHBoxLayout;
    wid->setLayout(hlayout_caisse);

    hlayout_caisse->addWidget(add_styleHeader("Total general (Caisse)","#43CD80",QLocale(QLocale::English).toString(caisse_totalGeneral),"#344956"));
    hlayout_caisse->addWidget(add_styleHeader("Benefice Brut","#43CD80",QLocale(QLocale::English).toString(caisse_beneficeBrut),"#344956"));
    hlayout_caisse->addWidget(add_styleHeader("Benefice Net","#43CD80",QLocale(QLocale::English).toString(caisse_beneficeNet),"#344956"));


    return wid;

}

void Fen_RapportGeneral::result_caisse()
{
    result_achatVente();
    result_transaction();
    result_echangeUSD();
    result_depense();

    // caisse ....................................................

    caisse_totalGeneral = 0, caisse_beneficeBrut = 0, caisse_beneficeNet = 0;

    caisse_totalGeneral = (transac_diff + echange_diff + versementInvestment ) - depense_totalGeneral;
    caisse_beneficeBrut = echange_diff + versementInvestment;

    caisse_beneficeNet = caisse_beneficeBrut - depense_totalGeneral;

    if(widgetParent_Caisse->children().size()<=0){
        QVBoxLayout *vbox = new QVBoxLayout;
        widgetParent_Caisse->setLayout(vbox);
        vbox->addWidget(add_WidgetRapportCaisse());
    }

}
