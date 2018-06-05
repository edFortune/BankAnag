#include "fen_rapportgeneral.h"


QWidget* Fen_RapportGeneral::rapportGeneral_depense()
{
    widgetParent_depense = new QWidget;




    return widgetParent_depense;

}

QWidget* Fen_RapportGeneral::add_WidgetRapportDepense()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:red;");

    QVBoxLayout *v = new QVBoxLayout;
    wid->setLayout(v);

    QLabel *lab_titre = new QLabel("Depense: "+QLocale(QLocale::English).toString(depense_totalGeneral));
    lab_titre->setStyleSheet("background-color:#CD3333; color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    v->addWidget(lab_titre);

    QHBoxLayout *hLayout = new QHBoxLayout;
    v->addLayout(hLayout);

    hLayout->addWidget(add_styleHeader("A payer","#CD3333",QLocale(QLocale::English).toString(depense_total),"#344956"));
    hLayout->addWidget(add_styleHeader("Payer","#CD3333",QLocale(QLocale::English).toString(depensePayer_total),"#344956"));



    return wid;
}


void Fen_RapportGeneral::result_depense()
{
    depense_total = 0,depensePayer_total = 0;
    querry.exec("SELECT * FROM depenseTable");
    while(querry.next())
        depense_total +=querry.value(3).toDouble();

    querry.exec("SELECT * FROM depensePayerTable");
    while(querry.next())
        depensePayer_total +=querry.value(3).toDouble();

    depense_totalGeneral = depense_total + depensePayer_total;

    if(widgetParent_depense->children().size()<=0){
        QVBoxLayout *vbox = new QVBoxLayout;
        widgetParent_depense->setLayout(vbox);
        vbox->addWidget(add_WidgetRapportDepense());
    }


}
