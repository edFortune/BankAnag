#include "investmentmanagement.h"

InvestmentManagement::InvestmentManagement(QWidget *parent) : QWidget(parent)
{

}

InvestmentManagement::InvestmentManagement(QSqlQuery q)
{
    query = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QSplitter *splitter = new QSplitter;
    vbox->addWidget(splitter);

    QListWidget *listeWidget = new QListWidget;
    listeWidget->setViewMode(QListView::IconMode);
    listeWidget->setIconSize(QSize(50, 50));
    listeWidget->setMovement(QListView::Static);
    listeWidget->setMaximumWidth(110);
    listeWidget->setSpacing(12);
    splitter->addWidget(listeWidget);


    QListWidgetItem *fournisseurButton = new QListWidgetItem(listeWidget);
    fournisseurButton->setIcon(QIcon("Image/fournisseurIcon.png"));
    fournisseurButton->setText(tr("Fournisseurs"));
    fournisseurButton->setTextAlignment(Qt::AlignHCenter);
    fournisseurButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *clientButton = new QListWidgetItem(listeWidget);
    clientButton->setIcon(QIcon("Image/clientIcon.png"));
    clientButton->setText(tr("Clients"));
    clientButton->setTextAlignment(Qt::AlignHCenter);
    clientButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *produitButton = new QListWidgetItem(listeWidget);
    produitButton->setIcon(QIcon("Image/produitIcon.png"));
    produitButton->setText(tr("Produit"));
    produitButton->setTextAlignment(Qt::AlignHCenter);
    produitButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



    pageStack = new QStackedWidget;
    splitter->addWidget(pageStack);

    Fournisseur *fournisseurPage = new Fournisseur(query);
    pageStack->addWidget(fournisseurPage);

    Client *clientPage = new Client(query);
    pageStack->addWidget(clientPage);

    Produit *produitPage = new Produit(query);
    pageStack->addWidget(produitPage);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,0);

    QPushButton *closeBte = new QPushButton("Close");
    closeBte->setFixedHeight(30);
    closeBte->setIcon(QIcon("Image/bclose.png"));
    vbox->addWidget(closeBte);
    vbox->setAlignment(closeBte,Qt::AlignRight);

//    QPushButton *closeBte = new QPushButton("close",this);
//    closeBte->setMaximumSize(QSize(50,50));
//    closeBte->setIcon(QIcon("Image/bclose.png"));
//    closeBte->setGeometry(1250,550,500,500);



    connect(listeWidget,SIGNAL(activated(QModelIndex)),this,SLOT(onActivatedListWidget(QModelIndex)));
    connect(closeBte,SIGNAL(clicked()),this,SLOT(fermerFen()));
}

void InvestmentManagement::setFenWidget(QMdiSubWindow *sub)
{
    subWind = sub;
}

void InvestmentManagement::fermerFen()
{
    subWind->close();
}

void InvestmentManagement::onActivatedListWidget(QModelIndex idx)
{
    pageStack->setCurrentIndex(idx.row());
}
