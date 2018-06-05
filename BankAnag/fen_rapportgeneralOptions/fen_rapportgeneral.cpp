#include "fen_rapportgeneral.h"

Fen_RapportGeneral::Fen_RapportGeneral(QWidget *parent) :
    QWidget(parent)
{
}


Fen_RapportGeneral::Fen_RapportGeneral(QSqlQuery q)
{
    querry = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QSplitter *splitter = new QSplitter;
    vbox->addWidget(splitter);



    //-----------liste widget---------------------
    listeWidget = new QListWidget;
    listeWidget->setViewMode(QListView::IconMode);
    listeWidget->setIconSize(QSize(50, 50));
    listeWidget->setMovement(QListView::Static);
    listeWidget->setMaximumWidth(110);
    listeWidget->setSpacing(12);
    splitter->addWidget(listeWidget);

    QListWidgetItem *clientButton = new QListWidgetItem(listeWidget);
    clientButton->setIcon(QIcon("Image/liste.png"));
    clientButton->setText(tr("Client"));
    clientButton->setTextAlignment(Qt::AlignHCenter);
    clientButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *transactionButton = new QListWidgetItem(listeWidget);
    transactionButton->setIcon(QIcon("Image/home.png"));
    transactionButton->setText(tr("Transaction"));
    transactionButton->setTextAlignment(Qt::AlignHCenter);
    transactionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *echangeUSDButton = new QListWidgetItem(listeWidget);
    echangeUSDButton->setIcon(QIcon("Image/echangeUS.png"));
    echangeUSDButton->setText(tr("Echange US"));
    echangeUSDButton->setTextAlignment(Qt::AlignHCenter);
    echangeUSDButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *achatVenteButton = new QListWidgetItem(listeWidget);
    achatVenteButton->setIcon(QIcon("Image/achatVente.png"));
    achatVenteButton->setText(tr("Investissement"));
    achatVenteButton->setTextAlignment(Qt::AlignHCenter);
    achatVenteButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *depenseButton = new QListWidgetItem(listeWidget);
    depenseButton->setIcon(QIcon("Image/setting.png"));
    depenseButton->setText(tr("Depense"));
    depenseButton->setTextAlignment(Qt::AlignHCenter);
    depenseButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *caisseButton = new QListWidgetItem(listeWidget);
    caisseButton->setIcon(QIcon("Image/caisse.png"));
    caisseButton->setText(tr("Caisse"));
    caisseButton->setTextAlignment(Qt::AlignHCenter);
    caisseButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);




    //-----------stacked widget---------------------
    stackedWid = new QStackedWidget;
    splitter->addWidget(stackedWid);

    fetch_RapportGeneral();

    stackedWid->addWidget(rapportGeneral_client());
    stackedWid->addWidget(rapportGeneral_transaction());
    stackedWid->addWidget(rapportGeneral_echangeUSD());
    stackedWid->addWidget(rapportGeneral_achatVente());
    stackedWid->addWidget(rapportGeneral_depense());
    stackedWid->addWidget(rapportGeneral_caisse());

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,0);


    QPushButton *b_closeFen = new QPushButton("Fermer");
    b_closeFen->setIcon(QIcon("Image/bclose.png"));
    vbox->addWidget(b_closeFen);
    vbox->setAlignment(b_closeFen,Qt::AlignRight);

    connect(b_closeFen,SIGNAL(clicked()),this,SLOT(closeFen()));
    connect(listeWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),\
            this,SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));


}

void Fen_RapportGeneral::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(listeWidget->row(current)==0){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_client();


    }else if(listeWidget->row(current)==1){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_transaction();


    }else if(listeWidget->row(current)==2){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_echangeUSD();


    }else if(listeWidget->row(current)==3){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_achatVente();


    }else if(listeWidget->row(current)==4){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_depense();

    }else if(listeWidget->row(current)==5){
        stackedWid->setCurrentIndex(listeWidget->row(current));
        result_caisse();


    }else if(!current)
        current = previous;

}


void Fen_RapportGeneral::set_FenWidget(QMdiSubWindow *f)
{
    fenRapportGeneral = f;
}


void Fen_RapportGeneral::closeFen()
{
    fenRapportGeneral->close();
}


QWidget* Fen_RapportGeneral::add_styleHeader(QString titre,QString col_titre,QString data,QString col_data)
{
    QWidget *wid = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    wid->setLayout(v);


    QLabel *lab_titre = new QLabel(titre);
    lab_titre->setStyleSheet("background-color:"+col_titre+";color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    v->addWidget(lab_titre);

    QLabel *lab_data = new QLabel(data);
    lab_data->setStyleSheet("background-color:"+col_data+";color:white;");
    lab_data->setAlignment(Qt::AlignCenter);
    lab_data->setFont(QFont("",20,20,false));
    lab_data->setMargin(5);
    v->addWidget(lab_data);

    return wid;
}



void Fen_RapportGeneral::fetch_RapportGeneral()
{



}
