#ifndef FEN_RAPPORTGENERAL_H
#define FEN_RAPPORTGENERAL_H

//#include <widgetStyleHeader.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QListView>
#include <QTableView>
#include <QDateEdit>
#include <QTreeView>
#include <QSpinBox>
#include <QTreeWidgetItem>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

#include <QMdiSubWindow>

#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QStringListModel>
#include <QSplitter>
#include <QListView>
#include <QList>
#include <QStackedWidget>
#include <QEvent>
#include <QFileDialog>

class Fen_RapportGeneral : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_RapportGeneral(QWidget *parent = 0);
    Fen_RapportGeneral(QSqlQuery);
    void set_FenWidget(QMdiSubWindow*);

protected:
    QWidget* add_styleHeader(QString titre,QString col_titre,QString data,QString col_data);

    QWidget* rapportGeneral_client();
    QWidget* add_WidgetRapportClient();
    QWidget* add_WidgetRapportClient(QString titre, int client25, int client50, int client100, int client250);
    QWidget* add_WidgetRapportClientSignatureAutoriser();

    QWidget* rapportGeneral_transaction();
    QWidget* add_WidgetRapportTransaction();
    QWidget* add_WidgetRapportTransactionDepot();
    QWidget* add_WidgetRapportTransactionRetrait();
    QWidget* add_WidgetRapportTransactionSolde();

    QWidget* rapportGeneral_echangeUSD();
    QWidget* add_WidgetRapportEchangeUSD();

    QWidget* rapportGeneral_achatVente();
    QWidget* add_WidgetRapportAchatVente();

    QWidget* rapportGeneral_depense();
    QWidget* add_WidgetRapportDepense();

    QWidget* rapportGeneral_caisse();
    QWidget* add_WidgetRapportCaisse();


    void fetch_RapportGeneral();
    void result_client();
    void result_achatVente();
    void result_transaction();
    void result_depense();
    void result_echangeUSD();
    void result_caisse();

    
signals:
    
public slots:
    void changePage(QListWidgetItem*,QListWidgetItem*);
    void closeFen();


private:
    QSqlQuery querry;

    QMdiSubWindow *fenRapportGeneral;


    QWidget *widgetParentClient,*widgetParent_AchatVente,*widgetParent_Caisse,*widgetParent_depense;
    QWidget *widParent_echangeUSD,*widParent_transaction;

    int client_groupe25,client_groupe50,client_groupe100,client_groupe250,client_total;
    int client25_sorti,client50_sorti,client100_sorti,client250_sorti,clientTotal_sorti;
    int client25_perdu,client50_perdu,client100_perdu,client250_perdu,clientTotal_perdu;
    int client25_signature,client50_signature,client100_signature,client250_signature,clientTotal_signature;


    int transac_depot, transac_retrait,transac_diff;
    int transac_depot25, transac_depot50, transac_depot100,transac_depot250,transac_totaldepot;
    int transac_retrait25, transac_retrait50, transac_retrait100,transac_retrait250,transac_totalretrait;
    int transac_diff25, transac_diff50, transac_diff100, transac_diff250;

    double echange_achat, echange_vente, echange_diff;
    double achatVente_achat, achatVente_vente, achatVente_diff,versementInvestment;
    double depense_total,depensePayer_total,depense_totalGeneral;
    double caisse_totalGeneral, caisse_beneficeBrut,caisse_beneficeNet;


    QStackedWidget *stackedWid;
    QListWidget *listeWidget;

    
};

#endif // FEN_RAPPORTGENERAL_H
