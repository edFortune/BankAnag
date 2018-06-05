#include "fenprincipale.h"
#include <QSqlQuery>
#include <QDate>

Fenprincipale::Fenprincipale(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowIcon(QIcon("Image/WindowIcon.ico"));
    //this->setMinimumSize(QSize(1000,600));

    barrEtat = this->statusBar();
    barrEtat->showMessage("Started",2000);
    toolbar = this->addToolBar("Toolbar");

    //----------------- Barre de menu ----------------------------
    setMenu();

    //------------------------creation de la base de donnee---------------------------------------
    creerConnection();

    //------------------Zone Centrale-----------------------------
    setZoneCentral();

    //------------------------Barre de menu---------------------------------------
    setBarreDoutil();

    //
    fram = new FirestoreRestApiManager(this);
    fram->postRequest("http://api.geonames.org/citiesJSON?");
    QObject::connect(fram, SIGNAL(dataReadyRead(QByteArray)), this, SLOT(dataFiresotreResponse(QByteArray)));

}

void Fenprincipale::setMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");


    QAction *backup = new QAction(QString::fromUtf8("Back up les données"),this);
    menuFichier->addAction(backup);


    QObject::connect(backup,SIGNAL(triggered()),this,SLOT(creerBackUp()));
}

void Fenprincipale::creerBackUp()
{
    dataBase->backupData();
}

void Fenprincipale::setBarreDoutil()
{

    toolbar->setIconSize(QSize(30,30));

    //--------------------------------------
    actionLogin = new QAction("Login",this);
    actionLogin->setIcon(QIcon("Image/login.png"));
    toolbar->addAction(actionLogin);
    toolbar->addSeparator();
    //--------------------------------------
    actionSettings = new QAction("Settings",this);
    actionSettings->setIcon(QIcon("Image/settings.ico"));
    toolbar->addAction(actionSettings);
    toolbar->addSeparator();

    QObject::connect(actionSettings,SIGNAL(triggered()),this,SLOT(afficherSettings()));
}



void Fenprincipale::getPassword()
{
    bool c = false;
    q.exec("SELECT * FROM compteTable");
    while(q.next())
    {
        if(q.value(1).toString()==user->currentText() && q.value(2).toString()==pass->text())
            c = true;
    }

    if(c == false)
    {

        actionSettings->setEnabled(true);
        widgetWindow->setEnabled(true);
        dialogLogIn->close();
    }
    else
    {
          QMessageBox::critical(this, "Erreur", "Mot de passe incorrect");
    }

}

void Fenprincipale::logOutDialog()
{
    actionSettings->setEnabled(false);
    widgetWindow->setEnabled(false);
}


void Fenprincipale::closeDialogLogin()
{
    dialogLogIn->close();
}



void Fenprincipale::creerCompte()
{
    if((!username->text().isEmpty() || !pass1->text().isEmpty() || !pass2->text().isEmpty()) && pass1->text()==pass2->text())
    {
        QMessageBox::about(this,"Message","Mots de passe correct.");
        bool c = q.exec("INSERT INTO compteTable(username,password) values('"+username->text()+"','"+pass1->text()+"')");
        if(c)
            qDebug()<<"new account";
        else
            qDebug()<<"no account";
    }
}


void Fenprincipale::setZoneCentral()
{
    zoneCentral = new QWidget;
    setCentralWidget(zoneCentral);

    hLayout = new QHBoxLayout;
    zoneCentral->setLayout(hLayout);

    vLayoutOption = new QVBoxLayout;


    widgetOption = new QWidget;
    hLayout->addWidget(widgetOption);
    //----------------------------------------------------------
    QScrollArea *scroll = new QScrollArea;

    widgetWindow = new QMdiArea;
    scroll->setWidget(widgetWindow);

    //widgetWindow->setFixedSize(1250,600);
    widgetWindow->setMinimumWidth(1320);
    widgetWindow->setMinimumHeight(600);

    hLayout->addWidget(scroll);

    HOMEPAGE = new Fen_HOMEPAGE(widgetWindow,q,toolbar);

    //actionSettings->setEnabled(false);
    //widgetWindow->setEnabled(false);


}


void Fenprincipale::creerConnection()
{
    barrEtat->showMessage("Activation de la base de donnee",2000);
    dataBase = new DataBaseClass;
    q = dataBase->getSqlQuerry();

    QString request1 = "CREATE TABLE IF NOT EXISTS liste_client_6"
                        "(id INTEGER PRIMARY KEY,"
                        "Titre varchar(20),"
                        "Nom varchar(20),"
                        "Prenom varchar(20),"
                        "Date_De_Naissance varchar(20),"
                        "typePiece varchar(20)," //5
                        "No_piece varchar(20),"
                        "Sexe varchar(20),"
                        "Domaine_Activite varchar(20),"
                        "Telephone_1 varchar(20),"
                        "Telephone_2 varchar(20)," //10
                        "Adresse varchar(20),"
                        "Email varchar(20),"
                        "Pays varchar(20),"
                        "Provence varchar(20),"
                        "Code_postal varchar(20),"
                        "Nom_ref varchar(20),"  //16
                        "Prenom_ref varchar(20),"
                        "Adresse_ref varchar(20),"
                        "Telephone_ref varchar(20),"
                        "typePiece_ref varchar(20),"
                        "No_piece_ref varchar(20),"
                        "Date_inscription varchar(20),"
                        "Groupe varchar(20),"
                        "Montant_com INTEGER," //24
                        "Photo varchar(50),"
                        "PhotoRef varchar(50),"
                        "FormeInscription varchar(50),"//27
                        "TitreRef varchar(20),"
                        "SexeRef varchar(20),"
                        "NomMere varchar(20)," //30
                        "AutorisationRef varchar(20),"
                        "Nationalite varchar(20),"
                        "Statut varchar(20))";

    dataBase->createTable(request1,"Client table");

    dataBase->setEnablePragma(true);


    QString request2 = "CREATE TABLE IF NOT EXISTS transaction_table_6"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "DATE varchar(20),"
                           "HEURE varchar(20),"
                           "DESCRIPTION varchar(20),"
                           "RETRAITS INTEGER,"
                           "DEPOTS INTEGER,"
                           "N_JOURS INTEGER,"
                           "SOLDE INTEGER,"
                           "PAR_QUI varchar(20),"
                           "No_Retrait INTEGER,"
                           "ID_CLIENT INTEGER,"
                           "GROUPE INTEGER,"
                           "Photo_Fiche_Retrait varchar(20),"
                           "FOREIGN KEY (ID_CLIENT) REFERENCES liste_client_6(id) )";

    dataBase->createTable(request2,"Transaction table");

    //dataBase->alterTable_AddColumn("transaction_table_6","DELIVRE","varchar(20)");

    QString request3 = "CREATE TABLE IF NOT EXISTS compteTable"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "username varchar(20),"
                           "password varchar(20) )";
    dataBase->createTable(request3,"compte table");



    QString request4 = "CREATE TABLE IF NOT EXISTS depenseTable"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "DATE DATE,"
                           "DESCRIPTION varchar(20),"
                           "MONTANT INTEGER )";
    dataBase->createTable(request4,"depense table");


    QString request5 = "CREATE TABLE IF NOT EXISTS liste_clientpara1"
                           "(CODE INTEGER,"
                           "ETAT varchar(20) )";
    dataBase->createTable(request5,"liste_clientpara1 table");

    QString request6 = "CREATE TABLE IF NOT EXISTS rapportCaisseTable_1"
                            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "DATE varchar(20),"
                            "DEPOTS INTEGER,"
                            "RETRAITS INTEGER,"
                            "BALANCE INTEGER,"
                            "DIFFERENCE INTEGER,"
                            "TOTAL INTEGER)";
    dataBase->createTable(request6,"rapportCaisseTable_1");

    QString request7 = "CREATE TABLE IF NOT EXISTS rapportEchangeUSDTable"
                            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "DATE varchar(20),"
                            "MONTANT INTEGER,"
                            "TAUX_ACHAT DOUBLE,"
                            "TOTAL_1 DOUBLE,"
                            "TAUX_VENTE DOUBLE,"
                            "TOTAL_2 DOUBLE,"
                            "DIFFERENCE DOUBLE)";
    dataBase->createTable(request7,"rapportEchangeUSDTable");


    QString request10 = "CREATE TABLE IF NOT EXISTS depensePayerTable"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "DATE DATE,"
                           "DESCRIPTION varchar(20),"
                           "MONTANT INTEGER )";
    dataBase->createTable(request10,"depensePayer table");


    QString request11_2 = "CREATE TABLE IF NOT EXISTS investmentTable2"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "DATE DATE,"
                           "DESCRIPTION varchar(20),"
                           "[MONTANT D'INVESTISSEMENT] DOUBLE, "
                           "PERIOD varchar(20),"
                           "EMPRUNTEUR varchar(20),"
                           "[MONTANT USD] DOUBLE,"
                           "TAUX DOUBLE)";
    dataBase->createTable(request11_2,"investmentTable2 table");


    //dataBase->deleteTable("versementInvestment");
    QString request12 = "CREATE TABLE IF NOT EXISTS versementInvestment"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           " DATE DATE,"
                           " DESCRIPTION varchar(20),"
                           " MONTANT DOUBLE,"
                           " ID_PARENT INTEGER,"
                           " FOREIGN KEY (ID_PARENT) REFERENCES investmentTable2(ID) )";
    dataBase->createTable(request12,"versementInvestment");


    QString request13 = "CREATE TABLE IF NOT EXISTS StatutClient"
                            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            " statut varchar(20) )";
    dataBase->createTable(request13,"statutClient");

    //dataBase->deleteTable("MemoTable");
    QString request14 = "CREATE TABLE IF NOT EXISTS MemoTable"
                            "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            " memo varchar(20),"
                            " check_memo varchar(20),"
                            " ID_CLIENT INTEGER,"
                            " FOREIGN KEY (ID_CLIENT) REFERENCES liste_client_6(id) )";
    dataBase->createTable(request14,"MemoTable ");

    QString request15 = "CREATE TABLE IF NOT EXISTS AutreProduits"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        " _DATE DATE,"
                        " lbl_autreProduit varchar(20),"
                        " montant DOUBLE)";

    dataBase->createTable(request15,"AutreProduits ");

    //---------------------------------------------------------------------------------------------------
    //-----------------------------------Investment parts tables-----------------------------------------
    //---------------------------------------------------------------------------------------------------
    qDebug()<<endl;

    QString request16 = "CREATE TABLE IF NOT EXISTS Fournisseurs"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Nom varchar(20),"
                        "Prenom varchar(20),"
                        "Sexe varchar(20),"
                        "NomCompany varchar(20),"
                        "Adresse varchar(20),"
                        "Telephone varchar(20),"
                        "Email varchar(20),"
                        "cr_Date DATE)";
    dataBase->createTable(request16,"Fournisseurs ");



    QString request17 = "CREATE TABLE IF NOT EXISTS Produits"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Nom varchar(20),"
                        "Description varchar(20),"
                        "Attribute varchar(20),"
                        "Size varchar(20),"
                        "[Qantite en stock] DOUBLE,"
                        "PrixAchat DOUBLE,"
                        "PrixVente DOUBLE,"
                        "cr_Date DATE,"
                        "idFournisseur INTEGER,"
                        "FOREIGN KEY (idFournisseur) REFERENCES Fournisseurs(ID) ON DELETE CASCADE )";
    dataBase->createTable(request17,"Produits ");



    QString request18 = "CREATE TABLE IF NOT EXISTS HistoryProduits"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Description varchar(20),"
                        "QteAV DOUBLE,"
                        "PrixAchat DOUBLE,"
                        "PrixVente DOUBLE,"
                        "idProduit INTEGER,"
                        "FOREIGN KEY (idProduit) REFERENCES Produits(ID) ON DELETE CASCADE )";
    dataBase->createTable(request18,"HistoryProduits ");



    QString request19 = "CREATE TABLE IF NOT EXISTS ProduitInvestment"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "[Quantite achat] DOUBLE,"
                        "idProduit INTEGER,"
                        "PrixAchat DOUBLE,"
                        "Description varchar(20),"
                        "idFournisseur INTEGER,"
                        "cr_Date DATE,"
                        "Statut INTEGER,"
                        "FOREIGN KEY (idFournisseur) REFERENCES Fournisseurs(ID) ON DELETE CASCADE,"
                        "FOREIGN KEY (idProduit) REFERENCES Produits(ID) ON DELETE CASCADE )";
    dataBase->createTable(request19,"ProduitInvestment ");



    QString request20 = "CREATE TABLE IF NOT EXISTS CreditInvestment"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "cr_Date DATE,"
                        "id_PI INTEGER,"
                        "MontantDu DOUBLE,"                        
                        "FOREIGN KEY (id_PI) REFERENCES ProduitInvestment(ID) ON DELETE CASCADE )";
    dataBase->createTable(request20,"CreditInvestment ");


//    dataBase->deleteTable("Versement_CI");
    QString request21 = "CREATE TABLE IF NOT EXISTS Versement_CI"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dateVersement DATE,"
                        "Description varchar(20),"
                        "MontantVerse DOUBLE,"
                        "id_CI INTEGER,"
                        "FOREIGN KEY (id_CI) REFERENCES CreditInvestment(ID) ON DELETE CASCADE )";
    dataBase->createTable(request21,"Versement_CI ");


    QString request21_1 = "CREATE TABLE IF NOT EXISTS Client"
                          "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "Company varchar(20),"
                          "Titre varchar(20),"
                          "Nom varchar(20),"
                          "Prenom varchar(20),"
                          "Email varchar(20),"
                          "Phone varchar(20),"
                          "Adresse varchar(20) )";
    dataBase->createTable(request21_1,"Client ");


//    dataBase->deleteTable("Sales_Details");
//    dataBase->deleteTable("Sales_Transaction");
    QString request22 = "CREATE TABLE IF NOT EXISTS Sales_Transaction"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Date DATE,"
                        "[Type Vente] varchar(20),"
                        "[Nom Complet] varchar(20),"
                        "Qte DOUBLE,"
                        "Total DOUBLE,"
                        "Payment varchar(20),"
                        "Return INTEGER )";
    dataBase->createTable(request22,"Sales_Transaction ");
    QString request22_1 = "CREATE TABLE IF NOT EXISTS Versement_CreditST"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "dateVersement DATE,"
                        "Description varchar(20),"
                        "MontantVerse DOUBLE,"
                        "id_ST INTEGER,"
                        "FOREIGN KEY (id_ST) REFERENCES Sales_Transaction(ID) ON DELETE CASCADE )";
    dataBase->createTable(request22_1,"Versement_CreditST ");


    //dataBase->deleteTable("Sales_Details");
    QString request23 = "CREATE TABLE IF NOT EXISTS Sales_Details"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "idProduit INTEGER,"
                        "[Nom Produit] varchar(20),"
                        "Qte DOUBLE,"
                        "PrixAchat DOUBLE,"
                        "PrixVente DOUBLE,"
                        "idSales_T INTEGER,"
                        "FOREIGN KEY (idSales_T) REFERENCES Sales_Transaction(ID) ON DELETE CASCADE) ";
    dataBase->createTable(request23,"Sales_Details ");




    //---------------------------------------------------------------------------------------------------
    //-----------------------------------Service Investment parts tables---------------------------------

    QString request24 = "CREATE TABLE IF NOT EXISTS Emprunteur"
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Nom varchar(20),"
                        "Prenom varchar(20),"
                        "Sexe varchar(20),"
                        "NomCompany varchar(20),"
                        "Adresse varchar(20),"
                        "Telephone varchar(20),"
                        "Email varchar(20),"
                        "cr_Date DATE)";
    dataBase->createTable(request24,"Emprunteur ");

    QString request25 = "CREATE TABLE IF NOT EXISTS ServiceInvestment "
                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        " DATE DATE,"
                        " DESCRIPTION varchar(20),"
                        " [TYPE ARGENT] varchar(20),"
                        " [MONTANT INVESTISSEMENT] DOUBLE,"
                        " TAUX DOUBLE,"
                        " EMPRUNTEUR INTEGER,"
                        " FOREIGN KEY (EMPRUNTEUR) REFERENCES Emprunteur(ID) )";
    dataBase->createTable(request25,"ServiceInvestment ");

    //dataBase->deleteTable("Versement_SInvestment");
    QString request26 = "CREATE TABLE IF NOT EXISTS Versement_SInvestment"
                           "(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                           " DATE DATE,"
                           " DESCRIPTION varchar(20),"
                           " MONTANT DOUBLE,"
                           " TAUX DOUBLE,"
                           " ID_PARENT INTEGER,"
                           " FOREIGN KEY (ID_PARENT) REFERENCES ServiceInvestment(ID) ON DELETE CASCADE )";
    dataBase->createTable(request26,"Versement_SInvestment ");


}



void Fenprincipale::closeEvent(QCloseEvent *event)
{
    resBtn = QMessageBox::question( this,"Quitter l'application",tr("Voulez-vous vraiment quitter l'application?\n"),
             QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
            dataBase->closeDataBase();
        }

}


void Fenprincipale::afficherSettings()
{
    QWidget *w = new QWidget;
//    w->setStyleSheet("background-color:white;");

    QVBoxLayout *v = new QVBoxLayout;
    w->setLayout(v);

    subFen_Settings = new Fen_Settings(q);
    v->addWidget(subFen_Settings);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fen_Settings = widgetWindow->addSubWindow(w);
    fen_Settings->setWindowTitle("Settings");
    fen_Settings->setMinimumSize(widgetWindow->size());
    fen_Settings->setWindowIcon(QIcon("Image/contact.png"));
    fen_Settings->setStyleSheet("QMdiSubWindow{background-color:white;}");
    fen_Settings->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(closeFenSettings()));
}

void Fenprincipale::closeFenSettings()
{
    fen_Settings->close();
}

void Fenprincipale::dataFiresotreResponse(QByteArray data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject rootObj = document.object();

    qDebug() << rootObj.empty();
}

