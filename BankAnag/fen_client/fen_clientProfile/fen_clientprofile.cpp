#include "fen_clientprofile.h"

Fen_ClientProfile::Fen_ClientProfile(QString d,QSqlQuery q)
{
    querry = q;
    foreign_id = d;


    pVLayout = new QVBoxLayout;
    this->setLayout(pVLayout);

    state = new QLabel("Etat du compte: ");
    state->setFont(QFont("",15,15,false));
    pVLayout->addWidget(state);

    QTabWidget *tabWid = new QTabWidget;
    pVLayout->addWidget(tabWid);

    QWidget *profilTab = new QWidget;
    tabWid->addTab(profilTab,"Profile");

    pGLayout1 = new QGridLayout;
    profilTab->setLayout(pGLayout1);

    QImage *image = new QImage("PhotoClient/1511.jpg");
    QImage image2 = image->scaled(300,200,Qt::KeepAspectRatio);

    pPhoto = new QLabel;
    pPhoto->setPixmap(QPixmap::fromImage(image2));
    pPhoto->setStyleSheet("border: 2px solid black;");
    pPhoto->setMargin(0);
    pGLayout1->addWidget(pPhoto,0,0,2,1);

    QPushButton *addphoto = new QPushButton;
    addphoto->setIcon(QIcon("Image/addIcon1.png"));
    addphoto->setIconSize(QSize(40,40));
    addphoto->setFlat(true);
    pGLayout1->addWidget(addphoto,0,0,2,1);

    QPushButton *voirForm = new QPushButton("Cliquer ici");


    grouProfInfo = new QGroupBox("Information personnelle");
    pGLayout1->addWidget(grouProfInfo,0,1,2,1);

    pFormLayout = new QFormLayout;
    grouProfInfo->setLayout(pFormLayout);

    for(int i=0;i<10;i++)
        pTableauInfo[i] = new QLabel("---");

    pFormLayout->addRow("ID: ",pTableauInfo[0]);
    pFormLayout->addRow("Titre: ",pTableauInfo[1]);
    pFormLayout->addRow("Nom: ",pTableauInfo[2]);
    pFormLayout->addRow("Prenom: ",pTableauInfo[3]);
    pFormLayout->addRow("Date de naissance: ",pTableauInfo[4]);
    pFormLayout->addRow("Type de piece: ",pTableauInfo[5]);
    pFormLayout->addRow("No de la piece: ",pTableauInfo[6]);
    pFormLayout->addRow("Sexe: ",pTableauInfo[7]);
    pFormLayout->addRow("Domaine d'activite: ",pTableauInfo[8]);
    pFormLayout->addRow("Nom de la mere: ",pTableauInfo[9]);
    pFormLayout->addRow("Voir le formulaire d'inscription",voirForm);

    //.........................................................
    QGroupBox *groupTelInfo = new QGroupBox("Telephone et Adresse");
    pGLayout1->addWidget(groupTelInfo,0,2,2,1);

    QFormLayout *TelFormLayout = new QFormLayout;
    groupTelInfo->setLayout(TelFormLayout);

    for(int i=0;i<8;i++)
        tel_TableauInfo[i] = new QLabel("---");

    TelFormLayout->addRow("Telephone 1: ",tel_TableauInfo[0]);
    TelFormLayout->addRow("Telephone 2: ",tel_TableauInfo[1]);
    TelFormLayout->addRow("Adresse: ",tel_TableauInfo[2]);
    TelFormLayout->addRow("Email: ",tel_TableauInfo[3]);
    TelFormLayout->addRow("Pays: ",tel_TableauInfo[4]);
    TelFormLayout->addRow("Departement: ",tel_TableauInfo[5]);
    TelFormLayout->addRow("Code postal: ",tel_TableauInfo[6]);

    //...........................................................
    QImage *image1 = new QImage("PhotoClient/1511.jpg");
    QImage image3 = image1->scaled(350,250,Qt::KeepAspectRatio);

    pPhoto1 = new QLabel;
    pPhoto1->setPixmap(QPixmap::fromImage(image3));
    pPhoto1->setStyleSheet("border: 2px solid black;");
    pPhoto1->setMargin(0);
    pGLayout1->addWidget(pPhoto1,2,0,1,1);

    QPushButton *addphotoRef = new QPushButton;
    addphotoRef->setIcon(QIcon("Image/addIcon1.png"));
    addphotoRef->setIconSize(QSize(40,40));
    addphotoRef->setFlat(true);
    pGLayout1->addWidget(addphotoRef,2,0,1,1);

    QGroupBox *groupRefInfo = new QGroupBox("Reference");
    pGLayout1->addWidget(groupRefInfo,2,1,1,1);

    QFormLayout *RefFormLayout = new QFormLayout;
    groupRefInfo->setLayout(RefFormLayout);

    for(int i=0;i<9;i++)
        ref_TableauInfo[i] = new QLabel("---");

    RefFormLayout->addRow("Titre:",ref_TableauInfo[0]);
    RefFormLayout->addRow("Nom:",ref_TableauInfo[1]);
    RefFormLayout->addRow("Prenom:",ref_TableauInfo[2]);
    RefFormLayout->addRow("Sexe:",ref_TableauInfo[3]);
    RefFormLayout->addRow("Adresse:",ref_TableauInfo[4]);
    RefFormLayout->addRow("Telephone:",ref_TableauInfo[5]);
    RefFormLayout->addRow("Type de piece:",ref_TableauInfo[6]);
    RefFormLayout->addRow("No de la piece:",ref_TableauInfo[7]);
    RefFormLayout->addRow("Autorisation de faire des retraits\nsur le compte du proprietaire:",ref_TableauInfo[8]);

    //----------------------------------------------------------
    tabWid->addTab(setTransactionTab(),"Liste des transactions");
    //----------------------------------------------------------
    tabWid->addTab(setDocumentClientTab(),"Documents");


    req = "";
    qDebug()<<d;

    setCLientInfo(foreign_id);

    QObject::connect(voirForm,SIGNAL(clicked()),this,SLOT(showDialogFormInscrip()));
    QObject::connect(addphoto,SIGNAL(clicked()),this,SLOT(addPicdialogBox()));
    QObject::connect(addphotoRef,SIGNAL(clicked()),this,SLOT(addPicRef_dialogBox()));
    QObject::connect(tabWid,SIGNAL(tabBarClicked(int)),this,SLOT(onTabBarClicked(int)));


}

void Fen_ClientProfile::onTabBarClicked(int i)
{
    switch (i) {
    case 0:
        setCLientInfo(foreign_id);
        break;
    case 1:
        setDataTransaction();
        break;
    default:
        break;
    }

}

void Fen_ClientProfile::setCLientInfo(QString id)
{

    querry.prepare("SELECT * FROM liste_client_6 WHERE id = "+id);
    bool c = querry.exec();

    if(c){
           IDCLIENT = id;
        while(querry.next())
        {

            if(querry.value(33).toString()=="En cours")
            {
                state->setText("Etat du compte: "+querry.value(33).toString());
                state->setStyleSheet("QLabel{color:green}");
            }else
            {
                state->setText("Etat du compte: "+querry.value(33).toString());
                state->setStyleSheet("QLabel{color:red}");
            }


            pTableauInfo[0]->setText(querry.value(0).toString());
            pTableauInfo[1]->setText(querry.value(1).toString());
            pTableauInfo[2]->setText(querry.value(2).toString());
            pTableauInfo[3]->setText(querry.value(3).toString());
            pTableauInfo[4]->setText(querry.value(4).toString());
            pTableauInfo[5]->setText(querry.value(5).toString());
            pTableauInfo[6]->setText(querry.value(6).toString());
            pTableauInfo[7]->setText(querry.value(7).toString());
            pTableauInfo[8]->setText(querry.value(8).toString());
            pTableauInfo[9]->setText(querry.value(30).toString());

            tel_TableauInfo[0]->setText(querry.value(9).toString());
            tel_TableauInfo[1]->setText(querry.value(10).toString());
            tel_TableauInfo[2]->setText(querry.value(11).toString());
            tel_TableauInfo[3]->setText(querry.value(12).toString());
            tel_TableauInfo[4]->setText(querry.value(13).toString());
            tel_TableauInfo[5]->setText(querry.value(14).toString());
            tel_TableauInfo[6]->setText(querry.value(15).toString());
            tel_TableauInfo[7]->setText(querry.value(16).toString());

            ref_TableauInfo[0]->setText(querry.value(28).toString());
            ref_TableauInfo[1]->setText(querry.value(16).toString());
            ref_TableauInfo[2]->setText(querry.value(17).toString());
            ref_TableauInfo[3]->setText(querry.value(29).toString());
            ref_TableauInfo[4]->setText(querry.value(18).toString());
            ref_TableauInfo[5]->setText(querry.value(19).toString());
            ref_TableauInfo[6]->setText(querry.value(20).toString());
            ref_TableauInfo[7]->setText(querry.value(21).toString());
            ref_TableauInfo[8]->setText(querry.value(31).toString());

            QImage *image = new QImage(querry.value(25).toString());
            QImage image2 = image->scaled(350,250,Qt::KeepAspectRatio);
            pPhoto->setPixmap(QPixmap::fromImage(image2));
            PicName = querry.value(25).toString();

            QImage *image1 = new QImage(querry.value(26).toString());
            QImage image3 = image1->scaled(350,250,Qt::KeepAspectRatio);
            pPhoto1->setPixmap(QPixmap::fromImage(image3));

            dateInscrip->setText(querry.value(22).toString());
            group->setText(querry.value(23).toString());
            mtnt->setText(querry.value(24).toString());
        }

    }

}

void Fen_ClientProfile::addPicdialogBox()
{

    PicName = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    if(PicName.isEmpty())
        return;
    else
    {
        QImage *img = new QImage(PicName);
        QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);
        pPhoto->setPixmap(QPixmap::fromImage(image2));
        qDebug()<<PicName;

        QFile f(PicName);
        QFileInfo fileInfo(f);
        QString fileName(fileInfo.fileName());
        QString path ="PhotoClient/Groupe "+group->text()+"/Pro/"+fileName;

        querry.prepare("UPDATE liste_client_6 SET  Photo = '"+path+"' WHERE id = "+IDCLIENT+" ");

        bool c = querry.exec();
        if(c){
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
            image2.save(path,0,100);
        }
        else
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");

    }

}



void Fen_ClientProfile::addPicRef_dialogBox()
{
    PicName_ref = QFileDialog::getOpenFileName(this,tr("Open image"), "PhotoClient",tr("*.png *.jpg *.bmp"));

    if(PicName_ref.isEmpty())
        return;
    else
    {
        QImage *img = new QImage(PicName_ref);
        QImage image2 = img->scaled(400,300,Qt::KeepAspectRatio);
        pPhoto1->setPixmap(QPixmap::fromImage(image2));
        qDebug()<<PicName_ref;

        QFile f(PicName_ref);
        QFileInfo fileInfo(f);
        QString fileName(fileInfo.fileName());
        QString path = "PhotoClient/Groupe "+group->text()+"/Ref/"+fileName;

        querry.prepare("UPDATE liste_client_6 SET  PhotoRef = '"+path+"' WHERE id = "+IDCLIENT+" ");

        bool c = querry.exec();
        if(c){
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
            image2.save(path,0,100);
        }
        else
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");
    }


}

QString Fen_ClientProfile::setDelaisJour()
{
    QString date1;
    QString nbreJours;
    bool c =querry.exec("SELECT * FROM liste_client_6 WHERE id = "+foreign_id+" ");

    if(!c)
        qDebug()<<"NOT Get delai";
    else
        qDebug()<<"Get delai";

    while(querry.next())
    {
        date1 = querry.value(22).toString();
    }

    nbreJours = QString::number(QDate::fromString(date1,"dd/MM/yyyy")\
                                .daysTo(QDate::fromString(QDate::currentDate().toString("dd/MM/yyyy"),"dd/MM/yyyy")));

    return nbreJours;
}




void Fen_ClientProfile::showDialogFormInscrip()
{
    dialogFormInscrip = new QDialog;
    dialogFormInscrip->setFixedSize(600,650);
    dialogFormInscrip->setModal(true);
    dialogFormInscrip->setWindowTitle("Formulaire d'inscription");
    dialogFormInscrip->show();

    QVBoxLayout *v = new QVBoxLayout;
    dialogFormInscrip->setLayout(v);

    imgForm = new QLabel;
    imgForm->setStyleSheet("border: 2px solid black;");
    imgForm->setMinimumSize(500,500);
    imgForm->setScaledContents(true);
    v->addWidget(imgForm);

    QPushButton *addphoto = new QPushButton;
    addphoto->setIcon(QIcon("Image/addIcon1.png"));
    addphoto->setIconSize(QSize(30,30));
    addphoto->setFlat(true);
    v->addWidget(addphoto);

    querry.exec("SELECT * FROM liste_client_6 WHERE id = "+pTableauInfo[0]->text()+" ");

    while(querry.next())
    {
        QImage *imgRef = new QImage(querry.value(27).toString());
        QImage img2 = imgRef->scaled(1000,900,Qt::KeepAspectRatio);
        imgForm->setPixmap(QPixmap::fromImage(img2));

    }

    QObject::connect(addphoto,SIGNAL(clicked()),this,SLOT(addPicForm_dialogBox()));
}


void Fen_ClientProfile::addPicForm_dialogBox()
{
    PicName_form = QFileDialog::getOpenFileName(this,tr("Open image"), "FormulaireInscription",tr("*.png *.jpg *.bmp"));

    if(PicName_form.isEmpty())
        return;
    else
    {
        QImage *imgRef = new QImage(PicName_form);
        QImage img2 = imgRef->scaled(1000,900,Qt::KeepAspectRatio);
        imgForm->setPixmap(QPixmap::fromImage(img2));
        qDebug()<<PicName_form;

        QFile f(PicName_form);
        QFileInfo fileInfo(f);
        QString fileName(fileInfo.fileName());
        QString path = "FormulaireInscription/Groupe "+group->text()+"/"+fileName;

        querry.prepare("UPDATE liste_client_6 SET  FormeInscription = '"+path+"' WHERE id = "+IDCLIENT+" ");

        bool c = querry.exec();
        if(c){
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE reussi.");
            img2.save(path,0,100);

        }
        else
            QMessageBox::about(this,"Mise a jour","UPDATE PICTURE echoue.");
    }


}


