#include "fen_settings.h"




QWidget* Fen_Settings::add_SettingsListeClient()
{
    QWidget *widParent = new QWidget;

    QVBoxLayout *vbox = new QVBoxLayout;
    widParent->setLayout(vbox);

    splitter = new QSplitter;
    vbox->addWidget(splitter);

    QTabWidget *tabParent = new QTabWidget;
    vbox->addWidget(tabParent);


    widDossierATraiter = new QWidget;
    setPageDossierATraiter();
    tabParent->addTab(widDossierATraiter,"Dossier "+QString::fromUtf8("à")+" traiter");

    widDossierAScanner = new QWidget;
    setPageDossierAScanner();
    tabParent->addTab(widDossierAScanner,"Dossier "+QString::fromUtf8("à")+" scanner");

    widStatutClient = new QWidget;
    setPageStatutClient(widStatutClient);
    tabParent->addTab(widStatutClient,"Statut du client");


    return widParent;


}


void Fen_Settings ::setPageDossierATraiter()
{
    QGridLayout *gridL = new QGridLayout;
    widDossierATraiter->setLayout(gridL);

    model = new QSqlTableModel;
    model->setTable(QString("liste_client_6"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Titre");
    model->setHeaderData(2,Qt::Horizontal,"Nom");
    model->setHeaderData(3,Qt::Horizontal,"Prenom");
    model->setHeaderData(4,Qt::Horizontal,"Date de naissance");
    model->setHeaderData(5,Qt::Horizontal,"Type de piece");
    model->setHeaderData(6,Qt::Horizontal,"No de la piece");
    model->setHeaderData(7,Qt::Horizontal,"Sexe");
    model->setHeaderData(8,Qt::Horizontal,"Domaine d'activite");
    model->setHeaderData(9,Qt::Horizontal,"Telephone 1");
    model->setHeaderData(10,Qt::Horizontal,"Telephone 2");
    model->setHeaderData(15,Qt::Horizontal,"Code Postal");
    model->setHeaderData(16,Qt::Horizontal,"Nom Ref");
    model->setHeaderData(17,Qt::Horizontal,"Prenom Ref");
    model->setHeaderData(18,Qt::Horizontal,"Adresse Ref");
    model->setHeaderData(19,Qt::Horizontal,"Telephone Ref");

    model->select();

    QTableView *table = new QTableView;
    table->setModel(model);
    gridL->addWidget(table,0,0,3,1);

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->resizeColumnsToContents();
    table->setColumnWidth(1,70);
    table->setColumnWidth(2,80);
    table->setColumnWidth(8,80);

    editID = new QSpinBox;
    editID->setMinimum(0);
    editID->setMaximum(9999);
    editID->setMaximumWidth(200);
    gridL->addWidget(editID,0,1,1,2);

    modelTabCode = new QSqlTableModel;
    modelTabCode->setTable("liste_clientpara1");
    modelTabCode->select();

    tabCode = new QTableView;
    tabCode->setMaximumWidth(200);
    tabCode->setModel(modelTabCode);
    tabCode->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabCode->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabCode->setColumnWidth(0,60);
    tabCode->setColumnWidth(1,90);
    gridL->addWidget(tabCode,1,1,1,2);

    QPushButton *ajoutB = new QPushButton("Ajouter");
    gridL->addWidget(ajoutB,2,1);

    QPushButton *suppB = new QPushButton("Supprimer");
    gridL->addWidget(suppB,2,2);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,1);

    get_listcode();

    QObject::connect(ajoutB,SIGNAL(clicked()),this,SLOT(addCode()));
    QObject::connect(suppB,SIGNAL(clicked()),this,SLOT(deleteCode()));
}



void Fen_Settings ::get_listcode()
{
    listID.clear();
    bool b = querry.exec("SELECT * FROM liste_clientpara1");
    if(b)
    {
        while(querry.next())
        {
            listID.append(querry.value(0).toString());
        }

        querry.finish();
    }
}

void Fen_Settings ::addCode()
{
    bool b = querry.exec("SELECT * FROM liste_client_6");
    bool checkID = false;
    if(b){
        while(querry.next())
        {
            if(querry.value(0).toString()==editID->text())
                checkID = true;
        }
    }

    if(checkID){
        if(!listID.contains(editID->text()))
        {
            querry.finish();

            bool c = querry.exec("INSERT INTO liste_clientpara1 (CODE,ETAT)"
                                 "VALUES ("+editID->text()+",'Non') ");
            if(!c)
                QMessageBox::warning(this,"Erreur","Enregistrement echoue!!!");
            else
            {
               editID->clear();
               modelTabCode->select();
               QMessageBox::about(this,"Succes","Enregistrement reussit!!!");
            }
        }else
        {
            QMessageBox::warning(this,"Erreur","La liste contient deja ce code.");
        }
    }else{
        QMessageBox::warning(this,"Erreur","Ce code n'existe pas dans la base.");
        editID->clear();
    }
}


void Fen_Settings ::deleteCode()
{
    int row = tabCode->selectionModel()->currentIndex().row();
    QString id = modelTabCode->index(row,0).data().toString();

    QMessageBox::StandardButton resBtnYes = QMessageBox::question( this,"Close",tr("Voulez-vous vraiment supprimer ce code?"),
             QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

    if(resBtnYes == QMessageBox::Yes)
    {
        bool c = querry.exec("DELETE FROM liste_clientpara1 WHERE CODE = "+id+"  ");
        if(!c)
            qDebug()<<"pas effacer";
        else{
                qDebug()<<"effacer";
                modelTabCode->select();
                listID.removeAt(row);
            }
    }
}

void Fen_Settings ::setPageDossierAScanner()
{
    QGridLayout *gridScan = new QGridLayout;
    widDossierAScanner->setLayout(gridScan);

    QFormLayout *f = new QFormLayout;
    gridScan->addLayout(f,0,0,2,1);

    QComboBox *trieComb = new QComboBox;
    trieComb->addItem("Proprietaire");
    trieComb->addItem("Reference");
    trieComb->addItem("Formulaire");
    f->addRow("Trier par image:",trieComb);

    addphotoPro = new QPushButton("Ajouter");
    f->addRow("Image du proprietaire:",addphotoPro);

    addphotoRef = new QPushButton("Ajouter");
    f->addRow("Image de la reference:",addphotoRef);

    addphotoForm = new QPushButton("Ajouter");
    f->addRow("Image du formulaire:",addphotoForm);

    addphotoPro->setEnabled(false);
    addphotoRef->setEnabled(false);
    addphotoForm->setEnabled(false);

    modelScan = new QSqlTableModel;
    modelScan->setTable(QString("liste_client_6"));
    modelScan->setEditStrategy(QSqlTableModel::OnManualSubmit);

    modelScan->setFilter("Photo = '' OR PhotoRef = '' OR FormeInscription = '' ");
    modelScan->select();

    tableScan = new QTableView;
    tableScan->setModel(modelScan);
    tableScan->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableScan->setSelectionBehavior(QAbstractItemView::SelectRows);
    gridScan->addWidget(tableScan,2,0,1,4);

    QFormLayout *f1 = new QFormLayout;
    gridScan->addLayout(f1,0,1,2,1);

    idC = new QLabel("---");
    f1->addRow("ID du client:",idC);

    titre = new QLabel("---");
    f1->addRow("Titre:",titre);

    nom = new QLabel("---");
    f1->addRow("Nom:",nom);

    prenom = new QLabel("---");
    f1->addRow("Prenom:",prenom);

    groupe = new QLabel("---");
    f1->addRow("Groupe:",groupe);

    editSearch = new QLineEdit;
    editSearch->setPlaceholderText("Chercher l'ID d'un client ici");
    gridScan->addWidget(editSearch,3,0,1,2);

    QPushButton *btnrefresh = new QPushButton;
    btnrefresh->setToolTip("Rechercher");
    btnrefresh->setIcon(QIcon("Image/refresh.png"));
    btnrefresh->setIconSize(QSize(30,30));
    btnrefresh->setFlat(true);
    gridScan->addWidget(btnrefresh,3,3);

    lcd_QteNoScan = new QLCDNumber;
    gridScan->addWidget(lcd_QteNoScan,0,3,2,1);

    update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE Photo = '' OR PhotoRef = '' OR FormeInscription = '' ");


    QObject::connect(trieComb,SIGNAL(currentIndexChanged(int)),this,SLOT(setTriage(int)));
    QObject::connect(tableScan,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(setChangeScan()));
    QObject::connect(addphotoPro,SIGNAL(clicked()),this,SLOT(addPicdialogBox()));
    QObject::connect(addphotoRef,SIGNAL(clicked()),this,SLOT(addPicRef_dialogBox()));
    QObject::connect(addphotoForm,SIGNAL(clicked()),this,SLOT(addPicForm_dialogBox()));
    QObject::connect(btnrefresh,SIGNAL(clicked()),this,SLOT(refreshlisteScan()));
    QObject::connect(editSearch,SIGNAL(returnPressed()),this,SLOT(chercherIDScan()));
}


void Fen_Settings ::setTriage(int i)
{
    if(i==0)
    {
        modelScan->setFilter("Photo = '' ");
        update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE Photo = '' ");
    }else if(i==1)
    {
        modelScan->setFilter("PhotoRef = '' ");
        update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE PhotoRef = '' ");
    }else if(i==2)
    {
        modelScan->setFilter("FormeInscription = '' ");
        update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE FormeInscription = '' ");
    }
}

void Fen_Settings ::setChangeScan()
{
    int row = tableScan->selectionModel()->currentIndex().row();
    QString id = modelScan->index(row,0).data().toString();
    IDCLIENT = id;

    addphotoPro->setEnabled(false);
    addphotoRef->setEnabled(false);
    addphotoForm->setEnabled(false);

    if(modelScan->index(row,25).data().toString().isEmpty())
        addphotoPro->setEnabled(true);
    else if(modelScan->index(row,26).data().toString().isEmpty())
        addphotoRef->setEnabled(true);
    else if(modelScan->index(row,27).data().toString().isEmpty())
        addphotoForm->setEnabled(true);

    idC->setText(modelScan->index(row,0).data().toString());
    titre->setText(modelScan->index(row,1).data().toString());
    nom->setText(modelScan->index(row,2).data().toString());
    prenom->setText(modelScan->index(row,3).data().toString());
    groupe->setText(modelScan->index(row,23).data().toString());
}



void Fen_Settings ::addPicdialogBox()
{
    if(!IDCLIENT.isEmpty())
    {
        PicName = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

        if(!PicName.isEmpty())
        {

            querry.prepare("UPDATE liste_client_6 SET  Photo = '"+PicName+"' WHERE id = "+IDCLIENT+" ");

            bool c = querry.exec();
            if(c){
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
                modelScan->setFilter("Photo = '' ");
                update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE Photo = '' ");
            }
            else
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");
        }
    }else
        QMessageBox::warning(this,"Selection vide","Veuillez sectionner un element dans la liste");
}



void Fen_Settings ::addPicRef_dialogBox()
{
    if(!IDCLIENT.isEmpty())
    {
        PicName_ref = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

        if(!PicName_ref.isEmpty())
        {

            querry.prepare("UPDATE liste_client_6 SET  PhotoRef = '"+PicName_ref+"' WHERE id = "+IDCLIENT+" ");

            bool c = querry.exec();
            if(c){
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
                modelScan->setFilter("PhotoRef = '' ");
                update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE PhotoRef = '' ");
            }
            else
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");
        }
    }else
        QMessageBox::warning(this,"Selection vide","Veuillez sectionner un element dans la liste");
}



void Fen_Settings ::addPicForm_dialogBox()
{
    if(!IDCLIENT.isEmpty())
    {
        PicName_form = QFileDialog::getOpenFileName(this,tr("Open image"), "FormulaireInscription",tr("*.png *.jpg *.bmp"));
        if(PicName_form.isEmpty())
            return;
        else
        {

            querry.prepare("UPDATE liste_client_6 SET  FormeInscription = '"+PicName_form+"' WHERE id = "+IDCLIENT+" ");

            bool c = querry.exec();
            if(c){
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
                modelScan->setFilter("FormeInscription = '' ");
                update_LCD_nonScan("SELECT * FROM liste_client_6 WHERE FormeInscription = '' ");
            }
            else
                QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");
        }
    }else
        QMessageBox::warning(this,"Selection vide","Veuillez sectionner un element dans la liste");

}

void Fen_Settings ::chercherIDScan()
{
    if(!editSearch->text().isEmpty())
    {
        modelScan->setFilter("id ="+editSearch->text());
        modelScan->select();
    }
}

void Fen_Settings ::refreshlisteScan()
{
    modelScan->setFilter("Photo = '' OR PhotoRef = '' OR FormeInscription = '' ");
    modelScan->select();
}

void Fen_Settings ::update_LCD_nonScan(QString req)
{
    int qte = 0;
    querry.prepare(req);
    bool c = querry.exec();

    if(c)
        while(querry.next())
            qte++;

    lcd_QteNoScan->display(qte);
}


void Fen_Settings::setPageStatutClient(QWidget *wid)
{
    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QSqlQueryModel *modelQuery = new QSqlQueryModel;
    modelQuery->setQuery("SELECT statut FROM StatutClient");

    QCompleter *complete = new QCompleter;
    complete->setModel(modelQuery);
    complete->setCaseSensitivity(Qt::CaseInsensitive);

    statut_edit = new QLineEdit;
    statut_edit->setCompleter(complete);
    grid->addWidget(statut_edit,0,0);

    QPushButton *ajoutBtn = new QPushButton("Ajouter");
    grid->addWidget(ajoutBtn,0,1);

    modelStatut = new QSqlTableModel;
    modelStatut->setTable("StatutClient");
    modelStatut->select();

    tableStatut = new QTableView;
    tableStatut->setModel(modelStatut);
    tableStatut->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableStatut->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableStatut->setAlternatingRowColors(true);
    grid->addWidget(tableStatut,1,0,2,1);

    QPushButton *effacerBtn = new QPushButton("Effacer");
    grid->addWidget(effacerBtn,1,1);

    connect(ajoutBtn,SIGNAL(clicked()),this,SLOT(onPress_ajouterBtn()));
    connect(effacerBtn,SIGNAL(clicked()),this,SLOT(onPress_effacerStatutBtn()));

}

bool Fen_Settings::isInStatutClient()
{
    if(querry.exec("SELECT * FROM StatutClient")){
        while(querry.next())
            if(statut_edit->text()==querry.value(1).toString())
                return true;
    }else
        QMessageBox::warning(this,"Scan echoue",QString::fromUtf8("Echec de la vérification des statuts"));

    return false;
}

void Fen_Settings::onPress_ajouterBtn()
{
    if(!isInStatutClient()){
        querry.prepare("INSERT INTO StatutClient (statut) VALUES (:statut)");
        querry.bindValue(":statut",statut_edit->text());

        if(querry.exec()){
            qDebug()<<"Insert statut succeed";
            statut_edit->clear();
            modelStatut->select();
        }
        else
            qDebug()<<"Insert statut failed";
    }else
        QMessageBox::warning(this,"Erreur d'insertion",QString::fromUtf8("Ce statut est déjà dans la liste"));
}


void Fen_Settings::onPress_effacerStatutBtn()
{

    int row = tableStatut->selectionModel()->currentIndex().row();
    QString id = modelStatut->index(row,0).data().toString();

    if(querry.exec("DELETE FROM StatutClient WHERE ID = "+id)){
        QMessageBox::about(this,"Success","Suppression reussite");
        modelStatut->select();

    }
    else
        QMessageBox::warning(this,"Echec","Suppression echoue");
}

