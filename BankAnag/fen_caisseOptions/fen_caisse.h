#ifndef FEN_CAISSE_H
#define FEN_CAISSE_H


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
#include <QGroupBox>
#include <QSplitter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QComboBox>
#include <QTextEdit>

#include <QMdiSubWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QDebug>

#include <QStandardItemModel>



#include "fen_caisse_delegate.h"
#include "fen_caisse_delegate2.h"

class Fen_Caisse : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Caisse(QWidget *parent = 0);
    Fen_Caisse(QSqlQuery);
    void setrapportCaissePage(QWidget*);
    void set_EchangeUSDPage(QWidget*);
    void set_FenWidget(QMdiSubWindow*);
    void set_AchatVenteMarchandisePage(QWidget *);

    //Rapport achat - vente
    void actualiseData();
    void actualiseDataVersement();

    
signals:

protected:

    // Rapport echange USD
    void set_totalGeneral();
    void set_totalGeneralUSD();
    void add_ItemRoot();
    void add_ItemChild();
    void add_Item_RootChild();

    // Rapport achat vente
    void update_TotalAchatVente();

    // Rapport autres Produits
    void setRapportAutreProduitPage(QWidget*);
    void setTotalAutreProduit();

    
public slots:
    void on_clicke_chercher();
    void on_click_CalenderDate(QDate);
    void addDataRapportCaisseTable();
    void closeFen();
    void on_click_Restore();
    void on_click_addEchangeDialog();
    void add_echangeUSD();

    void showContextMenu(QPoint);
    void effacerDataRapport();

    void showContextMenuEchangeUSD(QPoint);
    void removeRowEchangeUSD();

    void on_click_restorUSD();
    void showDataUSDChange(QModelIndex,QModelIndex);

    //Rapport achat - vente
    void showContextMenutableInvestissement(QPoint);
    void effacerDataRapporttableInvestissement();
    void onDoubleClickedTableRowInvest(QModelIndex);


    // Constructor of fen_caisse class
    void changePage(QListWidgetItem*,QListWidgetItem*);

private slots:
    //Rapport achat-vente
    void onActivatedComboList(QString);
    void showAddInvestissementDialog();
    void showAddVersementDialog();
    void onValueMontantDoubleSpinChanged(double);
    void onValueTypeEspeceDoubleSpinChanged(double);
    void onTypeEspeceCombActived(int);
    void onClickedAjoutInvestissementBtn();
    void onClickedAjoutVersementBtn();
    void showPopMenuTableVersement(QPoint);
    void effacerDataTableVersement();

    // Rapport autres Produits
    void onClick_addAutreProduit();
    void OnCick_effAutreProduit();

private:
    QSqlQuery querry;
    QStackedWidget *pagesWidget;
    QListWidget *listWidget;

    QComboBox *investmentID_combo,*investmentComboList;
    QSqlTableModel *modelInvestissement;

    QDateEdit *date;
    QLabel *dateLabel,*depotLabel,*retraitLabel,*balanceLabel,*totalLabel;
    QSqlTableModel *modelRapport;
    QTableView *tableRapport ;
    QTableView *tableInvest;

    QLabel *totgeneral,*totDepot,*totRetrait,*diff;

    bool isReqExecute;

    QMdiSubWindow *fen_caisse;

    Fen_Caisse_Delegate *delegateModelRapport;
    fen_caisse_delegate2 *delegateModelUSD;

    QSqlTableModel *model_echangeUSD;
    QTableView *tableEchangeUSD;
    QDialog *diag;
    QDateEdit *dateEchange;
    QDoubleSpinBox *montantEchange;
    QDoubleSpinBox *tauxAchat;
    QDoubleSpinBox *tauxVente;

    QLabel *totalMontantUSD;
    QLabel *total_1;
    QLabel *total_2;
    QLabel *totalDiff;

    QLabel *totalMontantUSD_htg;
    QLabel *total_1_htg;
    QLabel *total_2_htg;
    QLabel *totalDiff_htg;

    QLabel *tauxAchat_moy;
    QLabel *tauxVente_moy;

    QSqlTableModel *model_achatVente;

    QLabel *lab_totalAchat;
    QLabel *lab_totalVente;
    QLabel *lab_diff,*lab_versements;



    //QList<QTreeWidgetItem*> listWidgetItemRoot;
    QList<QTreeWidgetItem*>list_ItemRoot;
    QList<QTreeWidgetItem*>list_ItemChild;
    QSpinBox *spin_idTransac;
    QLabel *lab_status;
    QDoubleSpinBox *doubleSpin_mtntVersment;

    int childCount, columnCount;
    QTreeWidgetItem *itemWidget;

    //QStandardItemModel *model_listVersement;
    QString itemChild;
    QLabel *lab_totalVersement,*lab_totalBalance;


    //....................
    // Rapport achat - vente --------------------------------
    //....................
    QSqlTableModel *modelInvest;
    QComboBox *emprunteur;
    QDateEdit *dateInvest;
    QLineEdit *descriptionInvestment;
    QDoubleSpinBox *sortiMontant;
    QDoubleSpinBox *entreeMontant;
    QDoubleSpinBox *differenceMontant;
    QComboBox *period;

    QDoubleSpinBox *montant_totInvest;
    QDoubleSpinBox *montant_doubleSpin;
    QDoubleSpinBox *typeEspece_doubleSpin;
    QComboBox *typeEspece_comb;
    QDateEdit *dateInvest_dateEdit;
    QTextEdit *descriptInvest_text;
    QComboBox *periodInvest_comb;
    QLineEdit *emprunteurInvest_edit;
    QDialog *diagInvestissement;

    QDateEdit *dateEdit_versement;
    QLineEdit *descriptInvest_edit;
    QDoubleSpinBox *mtntVersement;
    QSqlTableModel *model_listVersement;
    QTableView *tableVersement;
    QLabel *mtntInvestis;
    QLabel *totalVersement;
    QLabel *balanceVersement;
    QLabel *beneficeVersement;
    QDialog *diagAddVersement;
    QLabel *idInvestissement_label;
    QSpinBox *idParent_spinBox;


    //.....................
    //.....................
    QLabel *emprunteur_Label;
    QLabel *investID_Label;
    QLabel *totalsortis_Label,*totalentree_Label,*totalDiff_Label;
    QLabel *totalVersement_Label;
    QLabel *balanceVersement_Label;

    //......................
    QTableView *tableInvestissement;

    // Rapport autres Produits
    QDateEdit *dateProduit;
    QLineEdit *autreProduit_edit;
    QSqlTableModel *modelAutreProduit;
    QDoubleSpinBox *montantAutreProduit_dspin;
    QTableView *tableAutreProduit;
    QLabel *totalAutreProduit;



};

#endif // FEN_CAISSE_H
