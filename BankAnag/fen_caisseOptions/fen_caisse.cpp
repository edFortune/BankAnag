#include "fen_caisse.h"

Fen_Caisse::Fen_Caisse(QWidget *parent) :
    QWidget(parent)
{

}

Fen_Caisse::Fen_Caisse(QSqlQuery q)
{
    querry = q;

   QVBoxLayout *v = new QVBoxLayout;
   this->setLayout(v);

   QSplitter *splitter = new QSplitter;
   v->addWidget(splitter);

   listWidget = new QListWidget;
   listWidget->setViewMode(QListView::IconMode);
   listWidget->setIconSize(QSize(40, 40));
   listWidget->setMovement(QListView::Static);
   listWidget->setMaximumWidth(100);
   listWidget->setSpacing(12);
   splitter->addWidget(listWidget);

   QListWidgetItem *rapportCaisseButton = new QListWidgetItem(listWidget);
   rapportCaisseButton->setIcon(QIcon("Image/rapport_quotidien.png"));
   rapportCaisseButton->setText(tr("Quotidien"));
   rapportCaisseButton->setTextAlignment(Qt::AlignHCenter);
   rapportCaisseButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

   QListWidgetItem *echangeUSButton = new QListWidgetItem(listWidget);
   echangeUSButton->setIcon(QIcon("Image/echangeUS_rapport.png"));
   echangeUSButton->setText(tr("Echange US"));
   echangeUSButton->setTextAlignment(Qt::AlignHCenter);
   echangeUSButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

   QListWidgetItem *achatVenteButton = new QListWidgetItem(listWidget);
   achatVenteButton->setIcon(QIcon("Image/achatVente_rapport.png"));
   achatVenteButton->setText(tr("Investment\n(S-fermer)"));
   achatVenteButton->setTextAlignment(Qt::AlignHCenter);
   achatVenteButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


   QListWidgetItem *taxButton = new QListWidgetItem(listWidget);
   taxButton->setIcon(QIcon("Image/tax_rapport.png"));
   taxButton->setText(tr("Autres\nproduits"));
   taxButton->setTextAlignment(Qt::AlignHCenter);
   taxButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


   pagesWidget = new QStackedWidget;
   splitter->addWidget(pagesWidget);


   QWidget *rapportCaisseWidget = new QWidget;
   setrapportCaissePage(rapportCaisseWidget);
   pagesWidget->addWidget(rapportCaisseWidget);

   QWidget *echangeUSWidget = new QWidget;
   set_EchangeUSDPage(echangeUSWidget);
   pagesWidget->addWidget(echangeUSWidget);

   QWidget *achatVenteWidget = new QWidget;
   set_AchatVenteMarchandisePage(achatVenteWidget);
   pagesWidget->addWidget(achatVenteWidget);


   QWidget *autreProduit = new QWidget;
   setRapportAutreProduitPage(autreProduit);
   pagesWidget->addWidget(autreProduit);


   splitter->setStretchFactor(0,0);
   splitter->setStretchFactor(1,0);

   QPushButton *closeBte = new QPushButton("Close");
   closeBte->setFixedHeight(30);
   closeBte->setIcon(QIcon("Image/bclose.png"));
   v->addWidget(closeBte);
   v->setAlignment(closeBte,Qt::AlignRight);

   connect(closeBte,SIGNAL(clicked()),this,SLOT(closeFen()));
   connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
           SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}


void Fen_Caisse::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current)
        current = previous;

    if(listWidget->row(current)==2)
        actualiseData();
    pagesWidget->setCurrentIndex(listWidget->row(current));

}
