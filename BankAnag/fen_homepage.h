#ifndef FEN_HOMEPAGE_H
#define FEN_HOMEPAGE_H

//#include <widgetStyleHeader.h>
#include <QToolBar>
#include <QAction>

#include "fen_client/fen_inscription.h"
#include "fen_client/fen_listeClient.h"
#include "fen_transaction/fen_listetransaction.h"
#include "fen_transaction/fen_transaction.h"
#include "fen_client/fen_donneeclient.h"
#include "fen_caisseOptions/fen_depense.h"
#include "fen_transaction/fen_transactioninfo.h"
#include "fen_caisseOptions/fen_caisse.h"
#include "fen_rapportgeneralOptions/fen_rapportgeneral.h"

#include "fen_investissement/Produit/investmenttransaction.h"
#include "fen_investissement/Produit/investmentmanagement.h"

#include "fen_investissement/Service/servicemanagement.h"

class Fen_HOMEPAGE : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_HOMEPAGE(QMdiArea *m, QSqlQuery querry, QToolBar *t);
    void setBarreDoutil();
    void setToolBar(QToolBar *t);

signals:
    
private slots:
    void afficheInfoInscript();
    void afficheInfoListe();
    void afficherListeTransaction();
    void afficheFenTransaction();
    void fermerFenInscript();
    void fermerFenListeTransac();
    void fermerFenTransac();
    void fermerFenLister();
    void afficherDonneeClient();
    void fermerFenDonneeClient();
    void afficherDepense();
    void fermerFenDepense();
    void afficheFenTransactionInfo();
    void fermerFenTransacInfo();
    void afficheFenPrintPreview();
    void afficheFenCaisse();
    void afficheFenRapportGeneral();

    //Investment Slots
    void afficheFenInvestmentManagement();

    //Service Slots
    void afficheFenServiceManagement();

private:
    Fen_Inscription *subFen_Inscrip;
    Fen_ListeClient *subFen_Lister;
    Fen_ListeTransaction *subFen_ListTransaction;
    Fen_Transaction *subFen_Transac;
    Fen_DonneeClient *subFen_DonneeClient;
    Fen_Depense *subFen_Depense;
    Fen_transactionInfo *subFen_TransacInfo;
    Fen_Caisse *subFen_Caisse;
    Fen_RapportGeneral *subFen_RapportGeneral;

    //Investment
    InvestmentManagement *subFen_InvestmentManagement;
    QMdiSubWindow *fenInvestmentManagement;

    //Service
    ServiceManagement *subFen_ServiceManagement;
    QMdiSubWindow *fenServiceManagement;


    QMdiSubWindow *fenInscrip, *fenHomePage,*fenTransac,*fen_DonneeClient,*fenDepense;
    QMdiSubWindow *fenTransacInfo,*fenPrintPreview,*fenCaisse,*fenRapportGeneral;

    QMdiArea *widgetWindow;
    QSqlQuery q;

    //--------------------------
    QToolBar *toolbar;
    QAction *actionTransact;
    QAction *actionHome;
    QAction *actionInscrip;
    QAction *actionListeClient;
    QAction *actionListeTransac;
    QAction *actionLogin;
    QAction *actionSettings;


    QMdiSubWindow *fenLister,*fenListTransac;
};

#endif // FEN_HOMEPAGE_H





