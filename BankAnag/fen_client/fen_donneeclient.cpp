#include "fen_donneeclient.h"

Fen_DonneeClient::Fen_DonneeClient(QWidget *parent) :
    QWidget(parent)
{

}

Fen_DonneeClient::Fen_DonneeClient(QSqlQuery q)
{
    querry = q;

    QVBoxLayout *v = new QVBoxLayout;
    this->setLayout(v);

    QHBoxLayout *h = new QHBoxLayout;
    v->addLayout(h);

    search = new QLineEdit;
    search->clear();
    h->addWidget(search);

    validID = new QPushButton;
    validID->setIcon(QIcon("Image/searchIcon.png"));
    validID->setIconSize(QSize(40,40));
    validID->setFlat(true);
    validID->setFixedWidth(90);
    h->addWidget(validID);


    tabWid = new QTabWidget;
    tabWid->setEnabled(false);
    v->addWidget(tabWid);

    QWidget *infoPersoTab = new QWidget;
    tabWid->addTab(infoPersoTab,"Information personnelle");

    QWidget *refTab = new QWidget;
    tabWid->addTab(refTab,"Reference");

    QWidget *infoComptTab = new QWidget;
    tabWid->addTab(infoComptTab,"Information sur le compte");

    QWidget *formulaireTab = new QWidget;
    tabWid->addTab(formulaireTab,"Formulaire d'inscription");


    QGridLayout *layPrincip = new QGridLayout;
    infoPersoTab->setLayout(layPrincip);

    QImage *img = new QImage("Image/iconLogIn.png");
    QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);

    image = new QLabel;
    image->setMinimumSize(400,240);
    image->setPixmap(QPixmap::fromImage(image2));
    layPrincip->setAlignment(image,Qt::AlignLeft | Qt::AlignTop);
    image->setStyleSheet("border: 2px solid black;");
    layPrincip->addWidget(image,0,0,2,1);

    QPushButton *addphoto = new QPushButton;
    addphoto->setIcon(QIcon("Image/addIcon1.png"));
    addphoto->setIconSize(QSize(50,50));
    addphoto->setFlat(true);
    layPrincip->addWidget(addphoto,2,0);


    groupInfoPerso = new QGroupBox("Information personnelle");
    //groupInfoPerso->setEnabled(false);
    layPrincip->addWidget(groupInfoPerso,0,2,1,1);

    QFormLayout *f1 = new QFormLayout;
    groupInfoPerso->setLayout(f1);

    idd = new QSpinBox;
    idd->setEnabled(false);
    idd->setMinimum(1000);
    idd->setMaximum(9999);
    idd->clear();
    f1->addRow("ID:",idd);

    titre = new QComboBox;
    titre->addItem("Mr.");
    titre->addItem("Mme");
    titre->addItem("Mlle");
    f1->addRow("Titre:",titre);

    nom = new QLineEdit;
    f1->addRow("Nom:",nom);

    prenom = new QLineEdit;
    f1->addRow("Prenom:",prenom);

    dateNaiss = new QDateEdit;
    f1->addRow("Date de naissance:",dateNaiss);

    nomMere = new QLineEdit;
    f1->addRow("Nom de la mere:",nomMere);


    QGroupBox *g2 = new QGroupBox;
    layPrincip->addWidget(g2,0,3,1,1);


    QFormLayout *f11 = new QFormLayout;
    g2->setLayout(f11);

    typePiece = new QComboBox;
    typePiece->addItem("NIF");
    typePiece->addItem("CIN");
    typePiece->addItem("Passport");
    typePiece->addItem("Matricule");
    typePiece->addItem("Permis de conduire");
    f11->addRow("Type de piece:",typePiece);

    nif = new QLineEdit;
    f11->addRow("No. de la piece:",nif);

    sexe = new QComboBox;
    sexe->addItem("Masculin");
    sexe->addItem("Feminin");
    f11->addRow("Sexe:",sexe);

    domAct = new QLineEdit;
    f11->addRow("Domaine d'activite",domAct);

    nationalite = new QComboBox;
    nationalite->addItem("Haitienne");
    nationalite->addItem("Americaine");
    nationalite->addItem("Canadienne");
    nationalite->addItem("Francaise");
    f11->addRow("Nationalite:",nationalite);

    //.......................................................

    grouptel = new QGroupBox("Telephone / Adresse");
    //grouptel->setEnabled(false);
    layPrincip->addWidget(grouptel,1,2,2,1);


    QFormLayout *f2 = new QFormLayout;
    grouptel->setLayout(f2);

    telMaison = new QSpinBox;
    telMaison->setMaximum(99999999);
    f2->addRow("Telephone 1:",telMaison);

    teltravail = new QSpinBox;
    teltravail->setMaximum(99999999);
    f2->addRow("Telephone 2:",teltravail);

    adress = new QLineEdit;
    f2->addRow("Adresse:",adress);

    email = new QLineEdit;
    f2->addRow("Email:",email);

    pays = new QComboBox;
    pays->addItem("Haiti");
    f2->addRow("Pays:",pays);

    departement = new QComboBox;
    departement->addItem("Ouest");
    departement->addItem("Artibonite");
    departement->addItem("Grande Anse");
    departement->addItem("Nippes");
    departement->addItem("Centre");
    departement->addItem("Nord");
    departement->addItem(QString::fromUtf8("Nord’Est",10));
    departement->addItem("Nord-Ouest");
    departement->addItem("Sud");
    departement->addItem(QString::fromUtf8("Sud’Est",10));
    f2->addRow("Departement",departement);

    //.................................................

    QGridLayout *gridLayout2 = new QGridLayout;
    refTab->setLayout(gridLayout2);


    imageRef = new QLabel;
    imageRef->setMinimumSize(400,240);
    imageRef->setPixmap(QPixmap("Image/iconLogIn.png"));
    imageRef->setStyleSheet("border: 2px solid black;");
    gridLayout2->addWidget(imageRef,0,0);

    QPushButton *addphoto_ref = new QPushButton;
    addphoto_ref->setIcon(QIcon("Image/addIcon1.png"));
    addphoto_ref->setIconSize(QSize(50,50));
    addphoto_ref->setFlat(true);
    gridLayout2->addWidget(addphoto_ref,1,0);


    groupRef = new QGroupBox("References");
    groupRef->setStyleSheet("QGroupBox{background-color:white}");
    gridLayout2->addWidget(groupRef,0,1,2,1);

    QFormLayout *f3 = new QFormLayout;
    groupRef->setLayout(f3);

    titreRef = new QComboBox;
    titreRef->addItem("Mr.");
    titreRef->addItem("Mme");
    titreRef->addItem("Mlle");

    nomReference = new QLineEdit;
    prenomReference = new QLineEdit;

    sexeRef = new QComboBox;
    sexeRef->addItem("Masculin");
    sexeRef->addItem("Feminin");

    adressReference = new QLineEdit;

    telReference = new QSpinBox;
    telReference->setMaximum(99999999);

    typePiece_ref = new QComboBox;
    typePiece_ref->addItem("NIF");
    typePiece_ref->addItem("CIN");
    typePiece_ref->addItem("Passport");
    typePiece_ref->addItem("Matricule");
    typePiece_ref->addItem("Permis de conduire");

    nifRef = new QLineEdit;

    autorisation = new QComboBox;
    autorisation->setMinimumHeight(35);
    autorisation->addItem("Aucun");
    autorisation->addItem("Oui");
    autorisation->addItem("Non");

    f3->addRow("Titre: ", titreRef);
    f3->addRow("Nom: ", nomReference);
    f3->addRow("Prenom: ", prenomReference);
    f3->addRow("Sexe: ", sexeRef);
    f3->addRow("Adresse: ", adressReference);
    f3->addRow("Telephone: ", telReference);
    f3->addRow("Type de piece:", typePiece_ref);
    f3->addRow("No de la piece: ", nifRef);
    f3->addRow("Autorisation de faire des retraits\nsur le compte du proprietaire: ", autorisation);

    //................................................

    QGridLayout *gridLayout3 = new QGridLayout;
    infoComptTab->setLayout(gridLayout3);

    groupCompte = new QGroupBox("Info sur le compte");
    //groupCompte->setEnabled(false);
    gridLayout3->addWidget(groupCompte,0,0,1,1);


    QFormLayout *f4 = new QFormLayout;
    groupCompte->setLayout(f4);

    dateInscrip = new QDateEdit;
    dateInscrip->setCalendarPopup(true);
    dateInscrip->setDisplayFormat("dd/MM/yyyy");
    f4->addRow("Date d'inscription",dateInscrip);

    type = new QComboBox;
    type->addItem("25");
    type->addItem("50");
    type->addItem("100");
    type->addItem("250");
    f4->addRow("Type de groupe",type);


    mtntCom = new QSpinBox;
    mtntCom->setMinimum(1);
    mtntCom->setMaximum(100000);
    f4->addRow("Montant a deposer:",mtntCom);

    QSqlQueryModel *modelQuery = new QSqlQueryModel;
    modelQuery->setQuery("SELECT statut FROM StatutClient");

    statut = new QComboBox;
    statut->setModel(modelQuery);
    f4->addRow("Etat du compte:",statut);
    //............................................

    QHBoxLayout *hForm = new QHBoxLayout;
    formulaireTab->setLayout(hForm);

    imgForm = new QLabel;
    imgForm->setStyleSheet("border: 2px solid black;");
    imgForm->setMinimumSize(300,400);
    imgForm->setScaledContents(true);
    //hForm->setAlignment(imgForm,Qt::AlignCenter);
    hForm->addWidget(imgForm);

    QPushButton *ajouFormulaire = new QPushButton;
    ajouFormulaire->setIcon(QIcon("Image/addIcon1.png"));
    ajouFormulaire->setIconSize(QSize(50,50));
    ajouFormulaire->setFlat(true);
    hForm->addWidget(ajouFormulaire);

    //............................................

    modif = new QPushButton("Modifier les donnees");
    modif->setIcon(QIcon("Image/modifyIcon.png"));
    modif->setIconSize(QSize(30,30));
    modif->setFlat(true);
    v->addWidget(modif);

    //..............................................

    QObject::connect(validID,SIGNAL(clicked()),this,SLOT(getData()));
    QObject::connect(search,SIGNAL(returnPressed()),this,SLOT(getData()));
    QObject::connect(modif,SIGNAL(clicked()),this,SLOT(modifierData()));
    QObject::connect(addphoto,SIGNAL(clicked()),this,SLOT(addPicdialogBox()));
    QObject::connect(addphoto_ref,SIGNAL(clicked()),this,SLOT(addPicRef_dialogBox()));
    QObject::connect(ajouFormulaire,SIGNAL(clicked()),this,SLOT(addPicFormInscrip_dialogBox()));
}


void Fen_DonneeClient::addPicdialogBox()
{
    PicName = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName);
    QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);
    image->setPixmap(QPixmap::fromImage(image2));
    qDebug()<<PicName;
}

void Fen_DonneeClient::addPicRef_dialogBox()
{
    PicName_ref = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName_ref);
    QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);
    imageRef->setPixmap(QPixmap::fromImage(image2));
    qDebug()<<PicName_ref;
}


void Fen_DonneeClient::addPicFormInscrip_dialogBox()
{
    PicName_form = QFileDialog::getOpenFileName(this,tr("Open image"), "FormulaireInscription",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName_form);
    QImage image2 = img->scaled(600,390,Qt::KeepAspectRatio);
    imgForm->setPixmap(QPixmap::fromImage(image2));
    qDebug()<<PicName_form;
}


void Fen_DonneeClient::getData()
{
    if(verifierCode())
    {
        querry.prepare("SELECT * FROM liste_client_6 WHERE id = "+search->text());
        bool c = querry.exec();
        if(!c)
            qDebug()<<"Failed";
        else
        {
            qDebug()<<"Succeed";

            while(querry.next())
            {
                //--------- Information personnelle ---------
                idd->setValue(querry.value(0).toInt());

                if(querry.value(1).toString().operator ==("Mr."))
                    titre->setCurrentIndex(0);
                else if(querry.value(1).toString().operator ==("Mme"))
                    titre->setCurrentIndex(1);
                else if(querry.value(1).toString().operator ==("Mlle"))
                    titre->setCurrentIndex(2);

                nom->setText(querry.value(2).toString());
                prenom->setText(querry.value(3).toString());
                dateNaiss->setDate(QDate::fromString(querry.value(4).toString(),"d/MM/yyyy"));

                nomMere->setText(querry.value(30).toString());


                //-----------------autre-------------------------

                //typepiece
                nif->setText(querry.value(6).toString());

                if(querry.value(7).toString().operator ==("Masculin"))
                    sexe->setCurrentIndex(0);
                else
                    sexe->setCurrentIndex(1);

                domAct->setText(querry.value(8).toString());

                nationalite->setCurrentIndex(0);


                //----------------telephone et add --------------

                telMaison->setValue(querry.value(9).toInt());
                teltravail->setValue(querry.value(10).toInt());
                adress->setText(querry.value(11).toString());
                email->setText(querry.value(12).toString());
                pays->setCurrentIndex(0);
                departement->setCurrentIndex(0);

                //---------------- reference -------------------------

                if(querry.value(28).toString().operator ==("Mr."))
                    titreRef->setCurrentIndex(0);
                else if(querry.value(28).toString().operator ==("Mme"))
                    titreRef->setCurrentIndex(1);
                else if(querry.value(28).toString().operator ==("Mlle"))
                    titreRef->setCurrentIndex(2);

                nomReference->setText(querry.value(16).toString());
                prenomReference->setText(querry.value(17).toString());

                if(querry.value(29).toString().operator ==("Masculin"))
                    sexeRef->setCurrentIndex(0);
                else
                    sexeRef->setCurrentIndex(1);


                adressReference->setText(querry.value(18).toString());
                telReference->setValue(querry.value(19).toInt());
                typePiece_ref->setCurrentIndex(0);
                nifRef->setText(querry.value(21).toString());

                if(querry.value(31).toString()=="Aucun")
                    autorisation->setCurrentIndex(0);
                else if(querry.value(31).toString()=="Oui")
                    autorisation->setCurrentIndex(1);
                else if(querry.value(31).toString()=="Non")
                    autorisation->setCurrentIndex(2);

                //--------------information sur le compte---------------------------

                dateInscrip->setDate(QDate::fromString(querry.value(22).toString(),"dd/MM/yyyy"));

                if(querry.value(23).toString()=="25")
                    type->setCurrentIndex(0);
                else if(querry.value(23).toString()=="50")
                    type->setCurrentIndex(1);
                else if(querry.value(23).toString()=="100")
                    type->setCurrentIndex(2);
                else if(querry.value(23).toString()=="250")
                    type->setCurrentIndex(3);

                mtntCom->setValue(querry.value(24).toInt());

//                if(querry.value(33).toString()=="En cours")
//                    statut->setCurrentIndex(0);
//                else if(querry.value(33).toString()=="Perdu")
//                    statut->setCurrentIndex(1);
//                else if(querry.value(33).toString()=="Close")
//                    statut->setCurrentIndex(2);

                PicName = querry.value(25).toString();
                QImage *img = new QImage(querry.value(25).toString());
                QImage img2 = img->scaled(350,250,Qt::KeepAspectRatio);
                image->setPixmap(QPixmap::fromImage(img2));

                PicName_ref = querry.value(26).toString();
                QImage *imgRef = new QImage(querry.value(26).toString());
                QImage im2 = imgRef->scaled(400,300,Qt::KeepAspectRatio);
                imageRef->setPixmap(QPixmap::fromImage(im2));

                PicName_form = querry.value(27).toString();
                QImage *imgform = new QImage(querry.value(27).toString());
                QImage imgform2 = imgform->scaled(300,400,Qt::KeepAspectRatio);
                imgForm->setPixmap(QPixmap::fromImage(imgform2));


            }
            search->clear();
            tabWid->setEnabled(true);
        }
    }
}

bool Fen_DonneeClient::verifierCode()
{

    bool v = false;

    querry.prepare("SELECT * FROM liste_client_6");
    bool c = querry.exec();
    if(!c)
    {
        QMessageBox::warning(this,"Erreur","Research code failed");
        return false;
    }
    else
    {
        while(querry.next())
        {
            if(querry.value(0).toString()==search->text())
            {
                v = true;
            }
        }
    }

    if(v)
        return v;
    else
    {
        QMessageBox::warning(this,"Erreur","Ce code n'existe pas dans la base.");
        tabWid->setEnabled(false);
        return v;
    }

}



void Fen_DonneeClient::modifierData()
{

    querry.prepare("UPDATE liste_client_6 SET Titre = '"+titre->currentText()+"',"
                   " Nom = '"+nom->text()+"',"
                   " Prenom = '"+prenom->text()+"',"
                   " Date_De_Naissance = '"+dateNaiss->text()+"',"
                   " typePiece = '"+typePiece->currentText()+"',"
                   " No_piece = '"+nif->text()+"',"
                   " Sexe = '"+sexe->currentText()+"',"
                   " Domaine_Activite = '"+domAct->text()+"',"
                   " Telephone_1 = '"+telMaison->text()+"',"
                   " Telephone_2 = '"+teltravail->text()+"',"
                   " Adresse = '"+adress->text()+"',"
                   " Email = '"+email->text()+"',"
                   " Pays = '"+pays->currentText()+"',"
                   " Provence = '"+departement->currentText()+"',"
                   " Nom_ref = '"+nomReference->text()+"',"
                   " Prenom_ref = '"+prenomReference->text()+"',"
                   " Adresse_ref = '"+adressReference->text()+"',"
                   " Telephone_ref = '"+telReference->text()+"',"
                   " typePiece_ref = '"+typePiece_ref->currentText()+"',"
                   " No_piece_ref = '"+nifRef->text()+"',"
                   " Date_inscription = '"+dateInscrip->text()+"',"
                   " Groupe = '"+type->currentText()+"',"
                   " Montant_com = "+mtntCom->text()+","
                   " Photo = '"+PicName+"',"
                   " PhotoRef = '"+PicName_ref+"',"
                   " FormeInscription = '"+PicName_form+"',"
                   " TitreRef = '"+titreRef->currentText()+"',"
                   " SexeRef = '"+sexeRef->currentText()+"',"
                   " NomMere = '"+nomMere->text()+"',"
                   " AutorisationRef = '"+autorisation->currentText()+"',"
                   " Nationalite = '"+nationalite->currentText()+"',"
                   " Statut = '"+statut->currentText()+"' WHERE id = "+idd->text()+" ");


    bool c = querry.exec();

    if(!c)
        qDebug()<<"Not updated";
    else
    {
        QMessageBox::about(this,"Result","Modification reussite!!!");
        search->clear();
        tabWid->setEnabled(false);
    }
}



QString Fen_DonneeClient::setDelaisJour()
{
    QString date1;
    QString nbreJours;
    bool c =querry.exec("SELECT * FROM liste_client_6 WHERE id = "+idd->text()+" ");

    if(!c)
        qDebug()<<"NOT Get delai";
    else
        qDebug()<<"Get delai";

    while(querry.next())
    {
        date1 = querry.value(20).toString();
    }

    nbreJours = QString::number(QDateTime::fromString(date1,"dd/MM/yyyy")\
                                .daysTo(QDateTime::fromString(QDate::currentDate()\
                                                              .toString("dd/MM/yyyy"),"dd/MM/yyyy")));

    return nbreJours;
}
