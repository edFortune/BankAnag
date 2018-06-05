#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

//#include <widgetStyleHeader.h>

#include "databaseclass.h"
#include "fen_homepage.h"
#include "fen_settingsOptions/fen_settings.h"
#include "firestorerestapimanager.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QStatusBar>
#include <QMenuBar>
#include <QCloseEvent>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class Fenprincipale : public QMainWindow
{
    Q_OBJECT
public:
    explicit Fenprincipale(QWidget *parent = 0);
    void setFenetreInfoListe();
    void setMenu();
    void setZoneCentral();
    void creerConnection();
    void setClientProfile();
    void afficherClientProfile();

    void setBarreDoutil();


signals:
    
public slots:
    void getPassword();
    void closeDialogLogin();
    void logOutDialog();
    void creerCompte();
    void creerBackUp();
    void afficherSettings();
    void closeFenSettings();

private slots:
    void dataFiresotreResponse(QByteArray data);


private:
    void closeEvent(QCloseEvent *bar);
    DataBaseClass *dataBase;

    FirestoreRestApiManager *fram;

    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;

    QWidget *zoneCentral;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayoutOption;
    QWidget *widgetOption;

    QMdiArea *widgetWindow;
    QMdiSubWindow *fenHomePage,*fen_Settings;


    QWidget *frame_Inscrip;
    QScrollArea *scrollInfo;


    //--------------SUBWINDOW 2 ------------
    QMdiSubWindow *fenLister,*fenListTransac;
    QSqlDatabase db;
    QSqlQuery q;

    QMessageBox::StandardButton resBtn;

    //--------------------------------------
    QToolBar *toolbar;
    QAction *actionTransact;
    QAction *actionHome;
    QAction *actionInscrip;
    QAction *actionListeClient;
    QAction *actionListeTransac;
    QAction *actionLogin;
    QAction *actionSettings;

    QStatusBar *barrEtat;
    QPushButton *b_transac;

    //----------------- ToolBar ------------


    //----------------- Liste transaction --------
    QGridLayout *gridTransaction;
    QTableView *transac_table1;
    QSqlTableModel *modelTransaction1;
    QMdiSubWindow *transac_fen;

    Fen_HOMEPAGE *HOMEPAGE;
    Fen_Settings *subFen_Settings;

    QDialog *dialogLogIn;
    QPushButton *boutonOk;
    QComboBox *user;
    QLineEdit *pass;

    QDialog *dialogSetting;
    QLineEdit *pass1;
    QLineEdit *pass2;
    QLineEdit *username;


};

#endif // FENPRINCIPALE_H
