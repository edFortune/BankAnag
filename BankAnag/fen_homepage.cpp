#include "fen_homepage.h"
#include "DesignWidgets/dgroupbox.h"
#include <QSqlQuery>

Fen_HOMEPAGE::Fen_HOMEPAGE(QMdiArea *m,QSqlQuery querry,QToolBar *t)
{
    widgetWindow = m;
    q = querry;
    toolbar = t;

    QWidget *HomePage = new QWidget;

    fenHomePage = widgetWindow->addSubWindow(HomePage);
    fenHomePage->setObjectName("fenHomePage");
    fenHomePage->setStyleSheet("#fenHomePage{background-color:white;}");
    fenHomePage->setWindowTitle("Page d'acceuil");
    fenHomePage->setWindowState(Qt::WindowMaximized);

    fenHomePage->show();

    QLabel *tabarrow[10];
    for(int i = 0;i<9;i++)
    {
        tabarrow[i] = new QLabel;
        tabarrow[i]->setPixmap(QPixmap("Image/arrow.png"));
    }


    QGridLayout *gridHome = new QGridLayout;
    HomePage->setLayout(gridHome);
    gridHome->setSpacing(10);


    DGroupBox *grpTransac = new DGroupBox("Transaction");
    grpTransac->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grpTransac);

    QHBoxLayout *htransac = new QHBoxLayout;
    grpTransac->setBodyLayout(htransac);


    QPushButton *transacIcon = new QPushButton("Transaction");
    transacIcon->setIcon(QIcon("Image/home.png"));
    transacIcon->setIconSize(QSize(60,50));
    transacIcon->setFlat(true);
    htransac->addWidget(transacIcon);

    htransac->addWidget(tabarrow[0]);

    QPushButton *listeTransacIcon = new QPushButton("Liste des\ntransactions");
    listeTransacIcon->setIcon(QIcon("Image/info.png"));
    listeTransacIcon->setIconSize(QSize(60,50));
    listeTransacIcon->setFlat(true);
    htransac->addWidget(listeTransacIcon);

    htransac->addWidget(tabarrow[1]);

    QPushButton *transacInfoIcon = new QPushButton("Information sur\nles transactions");
    transacInfoIcon->setIcon(QIcon("Image/transacInfo.png"));
    transacInfoIcon->setIconSize(QSize(60,50));
    transacInfoIcon->setFlat(true);
    htransac->addWidget(transacInfoIcon);

    //........

    DGroupBox *grpcontact = new DGroupBox("Clients");
    grpcontact->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grpcontact,0,1);

    QHBoxLayout *hcontact = new QHBoxLayout;
    grpcontact->setBodyLayout(hcontact);

    QPushButton *saveIcon = new QPushButton("Inscription");
    saveIcon->setIcon(QIcon("Image/Floopy.png"));
    saveIcon->setIconSize(QSize(60,50));
    saveIcon->setFlat(true);
    hcontact->addWidget(saveIcon);

    hcontact->addWidget(tabarrow[2]);

    QPushButton *listeClientIcon = new QPushButton("Liste des\nclients");
    listeClientIcon->setIcon(QIcon("Image/liste.png"));
    listeClientIcon->setIconSize(QSize(60,50));
    listeClientIcon->setFlat(true);
    hcontact->addWidget(listeClientIcon);

    hcontact->addWidget(tabarrow[3]);

    QPushButton *contactIcon = new QPushButton(QString::fromUtf8("Mise à jour de dossier\nd'un client"));
    contactIcon->setIcon(QIcon("Image/contact.png"));
    contactIcon->setIconSize(QSize(60,50));
    contactIcon->setFlat(true);
    hcontact->addWidget(contactIcon);

    //.........

    DGroupBox *grp_print = new DGroupBox("Investissement");
    grp_print->setStyleSheet("background-color:ivory");
    grp_print->setFixedHeight(150);
    gridHome->addWidget(grp_print,1,0);

    QHBoxLayout *h_print = new QHBoxLayout;
    grp_print->setBodyLayout(h_print);

    //h_print->addWidget(tabarrow[6]);

    QPushButton *manageInvestmentProduitIcon = new QPushButton("Gestion des produits");
    manageInvestmentProduitIcon->setIcon(QIcon("Image/listInvestmentIcon.png"));
    manageInvestmentProduitIcon->setIconSize(QSize(60,50));
    manageInvestmentProduitIcon->setFlat(true);
    h_print->addWidget(manageInvestmentProduitIcon);

    QPushButton *manageInvestmentServiceIcon = new QPushButton("Gestion des services");
    manageInvestmentServiceIcon->setIcon(QIcon("Image/serviceMIcon.png"));
    manageInvestmentServiceIcon->setIconSize(QSize(60,50));
    manageInvestmentServiceIcon->setFlat(true);
    h_print->addWidget(manageInvestmentServiceIcon);

    //.........

    DGroupBox *grp_vente = new DGroupBox("***");
    grp_vente->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grp_vente,1,1);

    QHBoxLayout *h_caisse = new QHBoxLayout;
    grp_vente->setBodyLayout(h_caisse);

    QPushButton *Icon1 = new QPushButton("****");
    Icon1->setIcon(QIcon("Image/bclose.png"));
    Icon1->setIconSize(QSize(60,50));
    Icon1->setFlat(true);
    h_caisse->addWidget(Icon1);

    QPushButton *Icon2 = new QPushButton("****");
    Icon2->setIcon(QIcon("Image/bclose.png"));
    Icon2->setIconSize(QSize(60,50));
    Icon2->setFlat(true);
    h_caisse->addWidget(Icon2);

    QPushButton *Icon3 = new QPushButton("****");
    Icon3->setIcon(QIcon("Image/bclose.png"));
    Icon3->setIconSize(QSize(60,50));
    Icon3->setFlat(true);
    h_caisse->addWidget(Icon3);

    //.........//

    DGroupBox *grp_achat = new DGroupBox("****");
    //grp_achat->setStyleSheet("background-color:ivory");
    //grp_Item->setFixedHeight(100);
    gridHome->addWidget(grp_achat,2,0);

    QHBoxLayout *h_achat = new QHBoxLayout;
    grp_achat->setBodyLayout(h_achat);

    QPushButton *receiveItemIcon = new QPushButton("****");
    receiveItemIcon->setIcon(QIcon("Image/bclose.png"));
    receiveItemIcon->setIconSize(QSize(60,50));
    receiveItemIcon->setFlat(true);
    h_achat->addWidget(receiveItemIcon);

    //h_achat->addWidget(tabarrow[7]);

    QPushButton *listeAchatIcon = new QPushButton("****");
    listeAchatIcon->setIcon(QIcon("Image/bclose.png"));
    listeAchatIcon->setIconSize(QSize(60,50));
    listeAchatIcon->setFlat(true);
    h_achat->addWidget(listeAchatIcon);

    //h_achat->addWidget(arrow5);

    QPushButton *fournisseurItemIcon = new QPushButton("****");
    fournisseurItemIcon->setIcon(QIcon("Image/bclose.png"));
    fournisseurItemIcon->setIconSize(QSize(60,50));
    fournisseurItemIcon->setFlat(true);
    h_achat->addWidget(fournisseurItemIcon);

    //.........
    DGroupBox *grp_info = new DGroupBox("****");
    //grp_info->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grp_info,3,0,1,2);

    QHBoxLayout *h_info = new QHBoxLayout;
    grp_info->setBodyLayout(h_info);

    //.........

    DGroupBox *grp_StatusAchat = new DGroupBox("****");
    //grp_StatusAchat->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grp_StatusAchat,2,1);

    QHBoxLayout *h_StatusAchat = new QHBoxLayout;
    grp_StatusAchat->setBodyLayout(h_StatusAchat);



    //..............................................................................................

    DGroupBox *grpCaisse = new DGroupBox("Controle general");
    //grpsecurite->setStyleSheet("background-color:ivory");
    gridHome->addWidget(grpCaisse,0,2,4,1);

    QVBoxLayout *vboxCaisse = new QVBoxLayout;
    grpCaisse->setBodyLayout(vboxCaisse);

    QPushButton *addCaisseIcon = new QPushButton("Caisse");
    addCaisseIcon->setIcon(QIcon("Image/caisse.png"));
    addCaisseIcon->setIconSize(QSize(60,50));
    addCaisseIcon->setFlat(true);
    vboxCaisse->addWidget(addCaisseIcon);

    //........

    QPushButton *depenseIcon = new QPushButton("Liste des\ndepenses");
    depenseIcon->setIcon(QIcon("Image/setting.png"));
    depenseIcon->setIconSize(QSize(60,50));
    depenseIcon->setFlat(true);
    vboxCaisse->addWidget(depenseIcon);

    //.........

    QPushButton *rapportIcon = new QPushButton("Rapports");
    rapportIcon->setIcon(QIcon("Image/reportIcon.png"));
    rapportIcon->setIconSize(QSize(60,50));
    rapportIcon->setFlat(true);
    vboxCaisse->addWidget(rapportIcon);

    //.........

    setBarreDoutil();

    QObject::connect(transacIcon,SIGNAL(clicked()),this,SLOT(afficheFenTransaction()));
    QObject::connect(saveIcon,SIGNAL(clicked()),this,SLOT(afficheInfoInscript()));
    QObject::connect(listeClientIcon,SIGNAL(clicked()),this,SLOT(afficheInfoListe()));
    QObject::connect(listeTransacIcon,SIGNAL(clicked()),this,SLOT(afficherListeTransaction()));

    //QObject::connect(loginIcon,SIGNAL(clicked()),this,SLOT(setDialogLogin()));
    QObject::connect(contactIcon,SIGNAL(clicked()),this,SLOT(afficherDonneeClient()));
    QObject::connect(depenseIcon,SIGNAL(clicked()),this,SLOT(afficherDepense()));
    QObject::connect(transacInfoIcon,SIGNAL(clicked()),this,SLOT(afficheFenTransactionInfo()));

    //QObject::connect(addPrintIcon,SIGNAL(clicked()),this,SLOT(afficheFenPrintPreview()));
    QObject::connect(addCaisseIcon,SIGNAL(clicked()),this,SLOT(afficheFenCaisse()));
    QObject::connect(rapportIcon,SIGNAL(clicked()),this,SLOT(afficheFenRapportGeneral()));

    //Investissement
    QObject::connect(manageInvestmentProduitIcon,SIGNAL(clicked()),this,SLOT(afficheFenInvestmentManagement()));

    //Service
    QObject::connect(manageInvestmentServiceIcon,SIGNAL(clicked()),this,SLOT(afficheFenServiceManagement()));


}

void Fen_HOMEPAGE::setToolBar(QToolBar *t)
{
    toolbar = t;
}

void Fen_HOMEPAGE::setBarreDoutil()
{

    toolbar->setIconSize(QSize(30,30));

    actionHome = new QAction("Acceuil",this);
    actionHome->setIcon(QIcon("Image/home1.png"));
    toolbar->addAction(actionHome);
    toolbar->addSeparator();
    //--------------------------------------
    actionTransact = new QAction("Transaction",this);
    actionTransact->setIcon(QIcon("Image/home.png"));
    toolbar->addAction(actionTransact);
    toolbar->addSeparator();
    //--------------------------------------
    actionInscrip = new QAction("Inscription",this);
    actionInscrip->setIcon(QIcon("Image/Floopy.png"));
    toolbar->addAction(actionInscrip);
    toolbar->addSeparator();
    //--------------------------------------
    actionListeClient = new QAction("Liste des clients",this);
    actionListeClient->setIcon(QIcon("Image/liste.png"));
    toolbar->addAction(actionListeClient);
    toolbar->addSeparator();
    //--------------------------------------
    actionListeTransac = new QAction("Liste des transactions",this);
    actionListeTransac->setIcon(QIcon("Image/info.png"));
    toolbar->addAction(actionListeTransac);
    toolbar->addSeparator();
    //--------------------------------------



    QObject::connect(actionTransact,SIGNAL(triggered()),this,SLOT(afficheFenTransaction()));
    QObject::connect(actionInscrip,SIGNAL(triggered()),this,SLOT(afficheInfoInscript()));
    QObject::connect(actionListeClient,SIGNAL(triggered()),this,SLOT(afficheInfoListe()));
    QObject::connect(actionListeTransac,SIGNAL(triggered()),this,SLOT(afficherListeTransaction()));


}


void Fen_HOMEPAGE::afficheInfoListe()
{
    QWidget *w = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_Lister = new Fen_ListeClient(q,widgetWindow);
    v->addWidget(subFen_Lister);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenLister = widgetWindow->addSubWindow(w);
    fenLister->setWindowTitle("Liste des clients");
    fenLister->setMinimumSize(widgetWindow->size());
    fenLister->setWindowIcon(QIcon("Image/liste.png"));
    fenLister->setStyleSheet("QMdiSubWindow{background-color:white;}");
    fenLister->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenLister()));
}

void Fen_HOMEPAGE::fermerFenLister()
{
    fenLister->close();
}


void Fen_HOMEPAGE::afficheFenTransaction()
{
    QWidget *w = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_Transac = new Fen_Transaction(q);
    v->addWidget(subFen_Transac);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenTransac = widgetWindow->addSubWindow(w);
    fenTransac->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenTransac->setMinimumSize(widgetWindow->size());
    fenTransac->setWindowTitle("Faire une transaction");
    fenTransac->setWindowIcon(QIcon("Image/home.png"));
    fenTransac->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenTransac()));
}

void Fen_HOMEPAGE::fermerFenTransac()
{
    fenTransac->close();
}



void Fen_HOMEPAGE::afficheInfoInscript()
{
    QWidget *w = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_Inscrip = new Fen_Inscription(q);
    v->addWidget(subFen_Inscrip);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenInscrip = widgetWindow->addSubWindow(w);
    fenInscrip->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenInscrip->setMinimumSize(widgetWindow->size());
    fenInscrip->setWindowTitle("Inscription");
    fenInscrip->setWindowIcon(QIcon("Image/Floopy.png"));


    fenInscrip->scroll(500,500);
    fenInscrip->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenInscript()));
}

void Fen_HOMEPAGE::fermerFenInscript()
{
    fenInscrip->close();
}



void Fen_HOMEPAGE::afficherListeTransaction()
{
    QWidget *w = new QWidget;
    //w->setStyleSheet("background-color:white;");

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_ListTransaction = new Fen_ListeTransaction(q);
    v->addWidget(subFen_ListTransaction);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenListTransac = widgetWindow->addSubWindow(w);
    fenListTransac->setWindowTitle("Liste des transactions");
    fenListTransac->setMinimumSize(widgetWindow->size());
    fenListTransac->setWindowIcon(QIcon("Image/info.png"));
    fenListTransac->setStyleSheet("QMdiSubWindow{background-color:white;}");
    fenListTransac->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenListeTransac()));
}

void Fen_HOMEPAGE::fermerFenListeTransac()
{
    fenListTransac->close();
}



void Fen_HOMEPAGE::afficherDonneeClient()
{
    QWidget *w = new QWidget;
//    w->setStyleSheet("background-color:white;");

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_DonneeClient = new Fen_DonneeClient(q);
    v->addWidget(subFen_DonneeClient);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);


    fen_DonneeClient = widgetWindow->addSubWindow(w);
    fen_DonneeClient->setWindowTitle("Contact");
    fen_DonneeClient->setMinimumSize(widgetWindow->size());
    fen_DonneeClient->setWindowIcon(QIcon("Image/contact.png"));
    fen_DonneeClient->setStyleSheet("QMdiSubWindow{background-color:white;}");
    fen_DonneeClient->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenDonneeClient()));
}

void Fen_HOMEPAGE::fermerFenDonneeClient()
{
    fen_DonneeClient->close();
}



void Fen_HOMEPAGE::afficherDepense()
{
    QWidget *w = new QWidget;
//    w->setStyleSheet("background-color:white;");

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_Depense = new Fen_Depense(q);
    v->addWidget(subFen_Depense);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);


    fenDepense = widgetWindow->addSubWindow(w);
    fenDepense->setWindowTitle("Contact");
    fenDepense->setMinimumSize(widgetWindow->size());
    fenDepense->setWindowIcon(QIcon("Image/contact.png"));
    fenDepense->setStyleSheet("QMdiSubWindow{background-color:white;}");
    fenDepense->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenDepense()));
}


void Fen_HOMEPAGE::fermerFenDepense()
{
    fenDepense->close();
}


void Fen_HOMEPAGE::afficheFenTransactionInfo()
{
    QWidget *w = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    v->setMargin(0);
    w->setLayout(v);

    subFen_TransacInfo = new Fen_transactionInfo(q);
    v->addWidget(subFen_TransacInfo);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenTransacInfo = widgetWindow->addSubWindow(w);
    fenTransacInfo->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenTransacInfo->setMinimumSize(widgetWindow->size());
    fenTransacInfo->setWindowTitle("Info des transactions");
    fenTransacInfo->setWindowIcon(QIcon("Image/home.png"));
    fenTransacInfo->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenTransacInfo()));
}

void Fen_HOMEPAGE::fermerFenTransacInfo()
{
    fenTransacInfo->close();
}



void Fen_HOMEPAGE::afficheFenPrintPreview()
{
//    QWidget *w = new QWidget;

//    QVBoxLayout *v = new QVBoxLayout;
//    v->setSpacing(0);
//    v->setMargin(0);
//    w->setLayout(v);

//    subFen_PrintPreview = new Fen_Impression(q);
//    v->addWidget(subFen_PrintPreview);

//    fenPrintPreview = widgetWindow->addSubWindow(w);
//    fenPrintPreview->setStyleSheet("QMdiSubWindow{background-color:white}");
//    fenPrintPreview->setMinimumSize(widgetWindow->size());
//    fenPrintPreview->setWindowTitle("Print Preview");
//    fenPrintPreview->setWindowIcon(QIcon("Image/home.png"));
//    fenPrintPreview->show();

//    subFen_PrintPreview->setCloseFen(fenPrintPreview);
}



void Fen_HOMEPAGE::afficheFenCaisse()
{
    subFen_Caisse = new Fen_Caisse(q);

    fenCaisse = widgetWindow->addSubWindow(subFen_Caisse);
    fenCaisse->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenCaisse->setMinimumSize(widgetWindow->size());
    fenCaisse->setWindowTitle("Caisse");
    fenCaisse->setWindowIcon(QIcon("Image/home.png"));
    fenCaisse->show();

    subFen_Caisse->set_FenWidget(fenCaisse);
}


void Fen_HOMEPAGE::afficheFenRapportGeneral()
{

    subFen_RapportGeneral = new Fen_RapportGeneral(q);

    fenRapportGeneral = widgetWindow->addSubWindow(subFen_RapportGeneral);
    fenRapportGeneral->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenRapportGeneral->setMinimumSize(widgetWindow->size());
    fenRapportGeneral->setWindowTitle("Rapport General");
    fenRapportGeneral->setWindowIcon(QIcon("Image/rapportIcon.png"));
    fenRapportGeneral->show();

    subFen_RapportGeneral->set_FenWidget(fenRapportGeneral);
}


void Fen_HOMEPAGE::afficheFenInvestmentManagement()
{
    subFen_InvestmentManagement = new InvestmentManagement(q);

    fenInvestmentManagement = widgetWindow->addSubWindow(subFen_InvestmentManagement);
    fenInvestmentManagement->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenInvestmentManagement->setMinimumSize(widgetWindow->size());
    fenInvestmentManagement->setWindowTitle("Investissement");
    fenInvestmentManagement->setWindowIcon(QIcon("Image/investmentIcon.png"));
    fenInvestmentManagement->show();

    subFen_InvestmentManagement->setFenWidget(fenInvestmentManagement);

}


void Fen_HOMEPAGE::afficheFenServiceManagement()
{
    subFen_ServiceManagement = new ServiceManagement(q);

    fenServiceManagement = widgetWindow->addSubWindow(subFen_ServiceManagement);
    fenServiceManagement->setStyleSheet("QMdiSubWindow{background-color:white}");
    fenServiceManagement->setMinimumSize(widgetWindow->size());
    fenServiceManagement->setWindowTitle("Service Management");
    fenServiceManagement->setWindowIcon(QIcon("Image/investmentIcon.png"));
    fenServiceManagement->show();

    subFen_ServiceManagement->setFenWidget(fenServiceManagement);


}
