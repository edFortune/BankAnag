#include "fen_rapportgeneral.h"


QWidget* Fen_RapportGeneral::rapportGeneral_client()
{
    widgetParentClient = new QWidget;

    return widgetParentClient;

}



QWidget *Fen_RapportGeneral::add_WidgetRapportClient(QString titre,int client25, int client50, int client100, int client250)
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#808069;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    int total = client25 + client50 + client100 + client250;

    QLabel *lab_titre = new QLabel(titre+": "+QLocale(QLocale::English).toString(total));
    lab_titre->setStyleSheet("background-color:#8B8B7A;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,4);


    grid->addWidget(add_styleHeader("Groupe 25","#8B8B7A",QLocale(QLocale::English).toString(client25),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Groupe 50","#8B8B7A",QLocale(QLocale::English).toString(client50),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Groupe 100","#8B8B7A",QLocale(QLocale::English).toString(client100),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Groupe 250","#8B8B7A",QLocale(QLocale::English).toString(client250),"#344956"),1,3);

    return wid;
}

QWidget* Fen_RapportGeneral::add_WidgetRapportClientSignatureAutoriser()
{
    QWidget *wid = new QWidget;
    wid->setStyleSheet("background-color:#808069;");

    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLabel *lab_titre = new QLabel("Droit de signature: "+QLocale(QLocale::English).toString(client_total));
    lab_titre->setStyleSheet("background-color:#8B8B7A;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    grid->addWidget(lab_titre,0,0,1,4);

    grid->addWidget(add_styleHeader("Groupe 25","#8B8B7A",QLocale(QLocale::English).toString(client25_signature),"#344956"),1,0);
    grid->addWidget(add_styleHeader("Groupe 50","#8B8B7A",QLocale(QLocale::English).toString(client50_signature),"#344956"),1,1);
    grid->addWidget(add_styleHeader("Groupe 100","#8B8B7A",QLocale(QLocale::English).toString(client100_signature),"#344956"),1,2);
    grid->addWidget(add_styleHeader("Groupe 250","#8B8B7A",QLocale(QLocale::English).toString(client250_signature),"#344956"),1,3);

    return wid;
}


void Fen_RapportGeneral::result_client()
{
    QStringList statutClientList;

    if(widgetParentClient->children().size()<=0){

        if(querry.exec("SELECT * FROM StatutClient")){
            while(querry.next()){
                statutClientList.append(querry.value(1).toString());
            }
        }

        QHBoxLayout *hbox = new QHBoxLayout;
        widgetParentClient->setLayout(hbox);

        QScrollArea *scrollBox = new QScrollArea;
        hbox->addWidget(scrollBox);

        QVBoxLayout *vbox = new QVBoxLayout;
        scrollBox->setLayout(vbox);

        for(int i = 0; i<statutClientList.size();i++){

            client_groupe25 =0,client_groupe50=0,client_groupe100=0,client_groupe250=0,client_total=0;
            querry.exec("SELECT * FROM liste_client_6");
            while(querry.next())
            {
                if(querry.value(23).toInt()==25 && querry.value(33).toString()==statutClientList.at(i))
                    client_groupe25++;
                else if(querry.value(23).toInt()==50 && querry.value(33) ==statutClientList.at(i))
                    client_groupe50++;
                else if(querry.value(23).toInt()==100 && querry.value(33)==statutClientList.at(i))
                    client_groupe100++;
                else if(querry.value(23).toInt()==250 && querry.value(33) ==statutClientList.at(i))
                    client_groupe250++;
            }

            vbox->addWidget(add_WidgetRapportClient(statutClientList.at(i),client_groupe25,client_groupe50,client_groupe100,client_groupe250));
        }

        //vbox->addWidget(add_WidgetRapportClientSignatureAutoriser());

    }

}
