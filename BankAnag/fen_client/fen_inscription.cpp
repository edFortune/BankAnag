#include "fen_inscription.h"

Fen_Inscription::Fen_Inscription(QWidget *parent) :
    QWidget(parent)
{

}

Fen_Inscription::Fen_Inscription(QSqlQuery req)
{
    q = req;

    QVBoxLayout *lay = new QVBoxLayout;
    this->setLayout(lay);

    titre = new QLabel("Formulaire d'ouverture d'un compte");
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("",10,QFont::Bold,false));
    lay->addWidget(titre);

    centre = new QTabWidget;
    lay->addWidget(centre);

    gridLayout = new QGridLayout;

    QWidget *wid = new QWidget;
    wid->setLayout(gridLayout);

    centre->addTab(wid,"Information personnelle");

    QImage *img = new QImage("Image/iconLogIn.png");
    QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);

    image = new QLabel;
    image->setMinimumSize(400,240);
    image->setPixmap(QPixmap::fromImage(image2));
    gridLayout->setAlignment(image,Qt::AlignLeft | Qt::AlignTop);
    image->setStyleSheet("border: 2px solid black;");
    gridLayout->addWidget(image,0,0,2,1);

    QPushButton *addphoto = new QPushButton;
    addphoto->setIcon(QIcon("Image/addIcon1.png"));
    addphoto->setIconSize(QSize(50,50));
    addphoto->setFlat(true);
    gridLayout->addWidget(addphoto,2,0);


    groupbox = new QGroupBox("Information personnelle");
    //groupbox->setStyleSheet("QGroupBox{background-color:white}");
    form_Inscrip = new QFormLayout;
    groupbox->setLayout(form_Inscrip);

    gridLayout->addWidget(groupbox,0,1,1,1);

    idd = new QSpinBox;
    idd->setMinimum(1000);
    idd->setMaximum(99999);
    form_Inscrip->addRow("ID:",idd);

    titreEdit = new QComboBox;
    titreEdit->addItem("Mr.");
    titreEdit->addItem("Mme");
    titreEdit->addItem("Mlle");
    form_Inscrip->addRow("Titre: ",titreEdit);

    nomEdit = new QLineEdit;
    nomEdit->setCompleter(this->setCompleterQuery("SELECT Nom FROM liste_client_6"));
    form_Inscrip->addRow("Nom:",nomEdit);

    prenomEdit = new QLineEdit;
    prenomEdit->setCompleter(this->setCompleterQuery("SELECT Prenom FROM liste_client_6"));
    form_Inscrip->addRow("Prenom:",prenomEdit);

    dateNaiss = new QDateEdit;
    dateNaiss->setCalendarPopup(true);
    dateNaiss->setDate(QDate(1970, 01, 01));
    dateNaiss->setDisplayFormat("dd/MM/yyyy");
    form_Inscrip->addRow("Date de naissance:",dateNaiss);

    nomMere = new QLineEdit;
    nomMere->setCompleter(this->setCompleterQuery("SELECT NomMere FROM liste_client_6"));
    form_Inscrip->addRow("Nom de la mere:",nomMere);

    QGroupBox *groupe = new QGroupBox;
    gridLayout->addWidget(groupe,0,2,1,1);

    QFormLayout *ff = new QFormLayout;
    groupe->setLayout(ff);

    typePiece = new QComboBox;
    typePiece->addItem("NIF");
    typePiece->addItem("CIN");
    typePiece->addItem("Passport");
    typePiece->addItem("Matricule");
    typePiece->addItem("Permis de conduire");
    typePiece->addItem("Autre");
    ff->addRow("Type de piece:",typePiece);

    nif = new QLineEdit;
    ff->addRow("No de la piece:",nif);

    sexe = new QComboBox;
    sexe->addItem("Masculin");
    sexe->addItem("Feminin");
    ff->addRow("Sexe:",sexe);

    domAct = new QLineEdit;
    domAct->setCompleter(this->setCompleterQuery("SELECT DISTINCT(Domaine_Activite) FROM liste_client_6"));
    ff->addRow("Domaine d'activite:",domAct);

    nationalite = new QComboBox;
    nationalite->addItem("Haitienne");
    nationalite->addItem("Americaine");
    nationalite->addItem("Canadienne");
    nationalite->addItem("Francaise");
    ff->addRow("Nationalite:",nationalite);



    groupboxTel = new QGroupBox("Telephones et Adresses: (509)");
    form_Tel = new QFormLayout;
    groupboxTel->setLayout(form_Tel);

    tel1 = new QSpinBox;
    tel1->setMaximum(99999999);
    form_Tel->addRow("Telephone 1:",tel1);

    tel2 = new QSpinBox;
    tel2->setMaximum(99999999);
    form_Tel->addRow("Telephone 2:",tel2);

    adress = new QLineEdit;
    adress->setCompleter(this->setCompleterQuery("SELECT Adresse FROM liste_client_6"));
    form_Tel->addRow("Adresse:",adress);

    email = new QLineEdit;
    email->setCompleter(this->setCompleterQuery("SELECT Email FROM liste_client_6"));
    form_Tel->addRow("Email:",email);

    country = new QComboBox;
    country->addItem("Haiti");
    form_Tel->addRow("Pays: ",country);

    provence = new QComboBox;
    provence->addItem("Ouest");
    provence->addItem("Artibonite");
    provence->addItem("Grande Anse");
    provence->addItem("Nippes");
    provence->addItem("Centre");
    provence->addItem("Nord");
    provence->addItem("Nord Est");
    provence->addItem("Nord-Ouest");
    provence->addItem("Sud");
    provence->addItem("Sud Est");

    form_Tel->addRow("Departement:",provence);

    gridLayout->addWidget(groupboxTel,1,1,1,1);

    //----------------------------------------------------------------------------------------------------

    QWidget *wid2 = new QWidget;
    centre->addTab(wid2,"Reference");

    QGridLayout *gridLayout2 = new QGridLayout;
    wid2->setLayout(gridLayout2);


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

    groupbox2 = new QGroupBox("Reference");
    groupbox2->setStyleSheet("QGroupBox{background-color:white}");
    form_Inscrip2 = new QFormLayout;
    groupbox2->setLayout(form_Inscrip2);

    titreRef = new QComboBox;
    titreRef->addItem("Mr.");
    titreRef->addItem("Mme");
    titreRef->addItem("Mlle");
    titreRef->addItem("Aucun");

    nomReference = new QLineEdit;
    nomReference->setCompleter(this->setCompleterQuery("SELECT Nom_ref FROM liste_client_6"));

    prenomReference = new QLineEdit;
    prenomReference->setCompleter(this->setCompleterQuery("SELECT Prenom_ref FROM liste_client_6"));

    sexeRef = new QComboBox;
    sexeRef->addItem("Masculin");
    sexeRef->addItem("Feminin");
    sexeRef->addItem("Aucun");

    adressReference = new QLineEdit;
    adressReference->setCompleter(this->setCompleterQuery("SELECT Adresse_ref FROM liste_client_6"));

    telReference = new QSpinBox;
    telReference->setMaximum(99999999);

    typePiece_ref = new QComboBox;
    typePiece_ref->addItem("NIF");
    typePiece_ref->addItem("CIN");
    typePiece_ref->addItem("Passport");
    typePiece_ref->addItem("Matricule");
    typePiece_ref->addItem("Permis de conduire");
    typePiece_ref->addItem("Autre");
    typePiece_ref->addItem("Aucun");

    nifRef = new QLineEdit;

    autorisation = new QComboBox;
    autorisation->setMinimumHeight(35);
    autorisation->addItem("Aucun");
    autorisation->addItem("Oui");
    autorisation->addItem("Non");

    form_Inscrip2->addRow("Titre: ", titreRef);
    form_Inscrip2->addRow("Nom: ", nomReference);
    form_Inscrip2->addRow("Prenom: ", prenomReference);
    form_Inscrip2->addRow("Sexe: ", sexeRef);
    form_Inscrip2->addRow("Adresse: ", adressReference);
    form_Inscrip2->addRow("Telephone: ", telReference);
    form_Inscrip2->addRow("Type de piece:", typePiece_ref);
    form_Inscrip2->addRow("No de la piece: ", nifRef);
    form_Inscrip2->addRow("Autorisation de faire des retraits\nsur le compte du proprietaire: ", autorisation);

    gridLayout2->addWidget(groupbox2,0,1,1,1);

    //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,



    //-------------------------------------------------------------------------------------


    QWidget *wid3 = new QWidget;
    centre->addTab(wid3,"Information sur le compte");

    QGridLayout *gridLayout3 = new QGridLayout;
    wid3->setLayout(gridLayout3);

    groupbox3 = new QGroupBox("Information sur le compte");
    groupbox3->setStyleSheet("QGroupBox{background-color:white}");
    form_Inscrip3 = new QFormLayout;

    dateInscrip = new QDateEdit;
    dateInscrip->setDisplayFormat("dd/MM/yyyy");
    dateInscrip->setCalendarPopup(true);
    dateInscrip->setDate(QDate::currentDate());
    form_Inscrip3->addRow("Date d'inscription:",dateInscrip);


    groupCombo = new QComboBox;
    groupCombo->addItem("25");
    groupCombo->addItem("50");
    groupCombo->addItem("100");
    groupCombo->addItem("250");
    form_Inscrip3->addRow("Groupe:",groupCombo);

    //......................................

    montantCom = new QSpinBox;
    montantCom->setMaximum(99999);
    form_Inscrip3->addRow("Montant d'ouverture:",montantCom);
    //.......................................

    statut = new QComboBox;
    statut->addItem("En cours");
    statut->addItem("Close");
    form_Inscrip3->addRow("Status du compte:",statut);

    groupbox3->setLayout(form_Inscrip3);
    gridLayout3->addWidget(groupbox3,1,2,2,1);

    //--------------------------------------------------------------------

    QHBoxLayout *hForm = new QHBoxLayout;

    QWidget *widd = new QWidget;
    widd->setLayout(hForm);

    centre->addTab(widd,"Formulaire d'inscription");


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


    //--------------------------------------------------------------------

    benreg = new QPushButton("Enregistrer");
    benreg->setIcon(QIcon("Image/Floopy.png"));
    benreg->setIconSize(QSize(35,35));
    benreg->setFlat(true);

    lay->addWidget(benreg);

    //-----------------------------------------------------------------------

    QObject::connect(benreg,SIGNAL(clicked()),this,SLOT(enregistrer()));
    QObject::connect(addphoto,SIGNAL(clicked()),this,SLOT(addPicdialogBox()));
    QObject::connect(addphoto_ref,SIGNAL(clicked()),this,SLOT(addPicRef_dialogBox()));
    QObject::connect(ajouFormulaire,SIGNAL(clicked()),this,SLOT(addPicFormInscrip_dialogBox()));


}


QCompleter* Fen_Inscription::setCompleterQuery(QString query)
{
    QSqlQueryModel *modelQueryComboID = new QSqlQueryModel;
    modelQueryComboID->setQuery(query);

    QCompleter *complete = new QCompleter;
    complete->setModel(modelQueryComboID);

    return complete;
}

void Fen_Inscription::addPicdialogBox()
{
    PicName = "";
    PicName = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName);
    imagePic = img->scaled(400,300,Qt::KeepAspectRatio);
    image->setPixmap(QPixmap::fromImage(imagePic));
    qDebug()<<PicName;

    QFile f(PicName);
    QFileInfo fileInfo(f);
    QString fileName(fileInfo.fileName());
    QString path = "PhotoClient/Groupe "+groupCombo->currentText()+"/Pro/"+fileName;

    PicName = path;
}

void Fen_Inscription::addPicRef_dialogBox()
{
    PicName_ref = "";
    PicName_ref = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName_ref);
    imagePicRef = img->scaled(400,300,Qt::KeepAspectRatio);
    imageRef->setPixmap(QPixmap::fromImage(imagePicRef));
    qDebug()<<PicName_ref;

    QFile f(PicName_ref);
    QFileInfo fileInfo(f);
    QString fileName(fileInfo.fileName());
    QString path = "PhotoClient/Groupe "+groupCombo->currentText()+"/Ref/"+fileName;

    PicName_ref = path;
}

void Fen_Inscription::addPicFormInscrip_dialogBox()
{
    PicName_form = "";
    PicName_form = QFileDialog::getOpenFileName(this,tr("Open image"), "FormulaireInscription",tr("*.png *.jpg *.bmp"));

    QImage *img = new QImage(PicName_form);
    imagePicform = img->scaled(600,400,Qt::KeepAspectRatio);
    imgForm->setPixmap(QPixmap::fromImage(imagePicform));
    qDebug()<<PicName_form;

    QFile f(PicName_form);
    QFileInfo fileInfo(f);
    QString fileName(fileInfo.fileName());
    QString path = "FormulaireInscription/Groupe "+groupCombo->currentText()+"/"+fileName;

    PicName_form = path;
}



void Fen_Inscription::enregistrer()
{
    if(verification()==false)
        return;
    else{
        qDebug()<<"Saving...";

        if(nomEdit->text()=="" || nomEdit->text()==" ")
            return;

        q.prepare("insert into liste_client_6"
                  "(id,Titre,Nom,Prenom,Date_De_Naissance,typePiece,No_piece,Sexe,Domaine_Activite,"
                  "Telephone_1,Telephone_2,Adresse,Email,Pays,Provence,Code_postal,"
                  "Nom_ref,Prenom_ref,Adresse_ref,Telephone_ref,typePiece_ref,No_piece_ref,"
                  "Date_inscription,Groupe,Montant_com,Photo,PhotoRef,FormeInscription,TitreRef,"
                  "SexeRef,NomMere,AutorisationRef,Nationalite,Statut)"
                  "VALUES(:id,:Titre,:Nom,:Prenom,:Date_De_Naissance,:typePiece,:No_piece,:Sexe,:Domaine_Activite,"
                  ":Telephone_1,:Telephone_2,:Adresse,:Email,:Pays,:Provence,:Code_postal,"
                  ":Nom_ref,:Prenom_ref,:Adresse_ref,:Telephone_ref,:typePiece_ref,:No_piece_ref,"
                  ":Date_inscription,:Groupe,:Montant_com,:Photo,:PhotoRef,:FormeInscription,:TitreRef,"
                  ":SexeRef,:NomMere,:AutorisationRef,:Nationalite,:Statut)");

        q.bindValue(":id",idd->text());
        q.bindValue(":Titre",titreEdit->currentText());
        q.bindValue(":Nom",nomEdit->text());
        q.bindValue(":Prenom",prenomEdit->text());
        q.bindValue(":Date_De_Naissance",dateNaiss->text());
        q.bindValue(":typePiece",typePiece->currentText());
        q.bindValue(":No_piece",nif->text());
        q.bindValue(":Sexe",sexe->currentText());
        q.bindValue(":Domaine_Activite",domAct->text());
        q.bindValue(":Telephone_1",tel1->text());
        q.bindValue(":Telephone_2",tel2->text());
        q.bindValue(":Adresse",adress->text());
        q.bindValue(":Email",email->text());
        q.bindValue(":Pays",country->currentText());
        q.bindValue(":Provence",provence->currentText());
        q.bindValue(":Code_postal","509");
        q.bindValue(":Nom_ref",nomReference->text());
        q.bindValue(":Prenom_ref",prenomReference->text());
        q.bindValue(":Adresse_ref",adressReference->text());
        q.bindValue(":Telephone_ref",telReference->text());
        q.bindValue(":typePiece_ref",typePiece_ref->currentText());
        q.bindValue(":No_piece_ref",nifRef->text());
        q.bindValue(":Date_inscription",dateInscrip->dateTime().toString("dd/MM/yyyy"));
        q.bindValue(":Groupe",groupCombo->currentText());
        q.bindValue(":Montant_com",montantCom->text());
        q.bindValue(":Photo",PicName);
        q.bindValue(":PhotoRef",PicName_ref);
        q.bindValue(":FormeInscription",PicName_form);
        q.bindValue(":TitreRef",titreRef->currentText());
        q.bindValue(":SexeRef",sexeRef->currentText());
        q.bindValue(":NomMere",nomMere->text());
        q.bindValue(":AutorisationRef",autorisation->currentText());
        q.bindValue(":Nationalite",nationalite->currentText());
        q.bindValue(":Statut",statut->currentText());

        bool check = q.exec();

        if(check){
            imagePic.save(PicName,0,100);
            imagePicRef.save(PicName_ref,0,100);
            imagePicform.save(PicName_form,0,100);

            image->clear();
            idd->clear();
            nomEdit->clear();
            prenomEdit->clear();
            adress->clear();
            nif->clear();
            domAct->clear();
            nomMere->clear();

            tel1->clear();
            tel2->clear();
            email->clear();

            imageRef->clear();
            nomReference->clear();
            prenomReference->clear();
            adressReference->clear();
            nifRef->clear();
            telReference->clear();
            centre->setCurrentIndex(0);

            imgForm->clear();
            q.finish();

            QMessageBox::about(this,"Enregistrement","Enregistrer avec succes!!!");
        }else{
            qDebug()<<"Not registed";
            q.finish();
            QMessageBox::warning(this,"Enregistrement","Enregistrement echoue!!!");

        }
    }
}


bool Fen_Inscription::verification()
{
    q.prepare("SELECT * FROM liste_client_6");
    bool c = q.exec();
    if(!c)
    {
        QMessageBox::warning(this,"Erreur","Research code failed");
        return false;
    }
    else
    {
        while(q.next())
        {
            if(q.value(0).toInt()==idd->value())
            {
                QMessageBox::warning(this,"Erreur","Ce code existe deja dans la base.");
                return false;
            }
        }
    }


    if(nomEdit->text().isEmpty()){
        QMessageBox::warning(this,"Erreur","Veuillez entrer un nom svp.");
        return false;
    }
    for(int i = 0; i<nomEdit->text().size();i++){
        if(nomEdit->text()[i]>='0' && nomEdit->text()[i]<='9'){
            QMessageBox::warning(this,"Erreur","Le nom ne doit pas avoir de chiffre.");
            return false;
        }

    }

    if(prenomEdit->text().isEmpty()){
        QMessageBox::warning(this,"Erreur","Veuillez entrer un prenom svp.");
        return false;
    }

    for(int i = 0; i<prenomEdit->text().size();i++){
        if(prenomEdit->text()[i]>='0' && prenomEdit->text()[i]<='9'){
            QMessageBox::warning(this,"Erreur","Le prenom ne doit pas avoir de chiffre.");
            return false;
        }
    }

    for(int i = 0; i<nomReference->text().size();i++){
        if(nomReference->text()[i]>='0' && nomReference->text()[i]<='9'){
            QMessageBox::warning(this,"Erreur","Le nom du reference ne doit pas avoir de chiffre.");
            return false;
        }
    }

    for(int i = 0; i<prenomReference->text().size();i++){
        if(prenomReference->text()[i]>='0' && prenomReference->text()[i]<='9'){
            QMessageBox::warning(this,"Erreur","Le prenom du reference ne doit pas avoir de chiffre.");
            return false;
        }
    }

    if(nif->text().isEmpty())
    {
        QMessageBox::warning(this,"Erreur","Veuillez entrer le numero de la piece svp.");
        return false;
    }

    if(montantCom->value()<groupCombo->currentText().toInt())
    {
        QMessageBox::warning(this,"Erreur","Le montant d'ouverture doit etre superieur ou egal au montant du groupe choisi.");
        return false;
    }

    return true;
}


