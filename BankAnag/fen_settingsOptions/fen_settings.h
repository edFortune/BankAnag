#ifndef FEN_SETTINGS_H
#define FEN_SETTINGS_H


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

#include <QCompleter>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

#include <QStringList>
#include <QStringListModel>
#include <QSplitter>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>

class Fen_Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Settings(QWidget *parent = 0);
    Fen_Settings(QSqlQuery q);


    //--------------settings liste client public functions ----------
    void setParametrelisteClient();
    void setPageDossierATraiter();
    void setPageDossierAScanner();
    void setPageStatutClient(QWidget *wid);
    void get_listcode();
    bool isInStatutClient();



    //--------------settings liste transaction public functions -----
    void setParametrelisteTransaction();
    void setPageTransfertTransaction(QWidget*);
    void setPageModificationTransaction(QWidget*);
    void setPageChangementGroup(QWidget*);
    
signals:

    
public slots:
    void onChangeItem(QListWidgetItem*,QListWidgetItem*);


    //--------------settings liste client slots ----------
    void addCode();
    void deleteCode();
    void setTriage(int);
    void setChangeScan();
    void addPicdialogBox();
    void addPicRef_dialogBox();
    void addPicForm_dialogBox();
    void refreshlisteScan();
    void chercherIDScan();
    void onPress_ajouterBtn();
    void onPress_effacerStatutBtn();

    //--------------settings liste transaction public functions ----------
    void searchAcCode(QString);
    void searchNcCode(QString);
    void on_press_bTransfertTransaction();
    void text_IdClient_Change(QString);
    void getTransactionAmodifier();
    void changeDataTransaction();



protected:
    //--------------settings liste client public functions ----------
    QWidget* add_SettingsListeClient();
    void update_LCD_nonScan(QString);
    //--------------settings liste transaction public functions ----------
    QWidget* add_SettingsListeTransaction();

    void changePage(QModelIndex i);

private:

    QStackedWidget *pagesWidget;
    QListWidget *listWidget;

    //---------------------------settings liste clients-------------------
    QSqlQuery querry;
    QSplitter *splitter;
    QSqlTableModel *model,* modelTabCode,*modelScan;
    QSpinBox *editID;
    QComboBox *combState;
    QTableView *tabCode;

    QWidget *liste_clientTab;
    QList<QString> listID;
    QLabel *image,*imageRef,*imageForm;

    QWidget *widDossierATraiter,*widDossierAScanner,*widStatutClient;

    QTableView *tableScan;

    QPushButton *addphotoPro,*addphotoRef,*addphotoForm;
    QString PicName,PicName_ref,PicName_form,IDCLIENT;

    QLCDNumber *lcd_QteNoScan;

    QLabel *idC,*titre,*nom,*prenom,*groupe;
    QLineEdit *editSearch;

    QLineEdit *statut_edit;

    QSqlTableModel *modelStatut;
    QTableView *tableStatut;

    //---------------------------settings liste transaction-------------------
    QSplitter *splitter_listeTransacTab;
    QSqlTableModel *modelModifierTransac;

    QWidget *transactionTab,*liste_transactionTab;

    QStackedWidget *pagesWidget_listeTransac;

    QSqlTableModel *modalAC,*modalNC;

    QLineEdit *acEdit,*ncEdit;
    QDateEdit *dateTransac;
    QTimeEdit *timeTransac;
    QLineEdit *idTransac;

    QTableView *tableModifierTransac;


};

#endif // FEN_SETTINGS_H
