#include "fen_transaction/fen_transaction.h"


Fen_Transaction::Fen_Transaction(QWidget *parent) :
    QWidget(parent)
{

}


Fen_Transaction::Fen_Transaction(QSqlQuery q)
{

    querry = q;
    db = new DataBaseClass("Fen_Transaction");

    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(5);
    this->setLayout(grid);

    QSqlQueryModel *modelQueryComboID = new QSqlQueryModel;
    modelQueryComboID->setQuery("SELECT ID FROM liste_client_6");

    QCompleter *complete = new QCompleter;
    complete->setModel(modelQueryComboID);

    comboID = new QLineEdit;
    comboID->setCompleter(complete);
    comboID->setPlaceholderText("Entrez l'ID ici");
    grid->setAlignment(comboID,Qt::AlignLeft | Qt::AlignTop);
    comboID->setFixedHeight(30);
    grid->addWidget(comboID,0,1,1,2);

    QPushButton *validID = new QPushButton;
    validID->setIcon(QIcon("Image/searchIcon.png"));
    validID->setIconSize(QSize(40,40));
    validID->setFlat(true);
    validID->setFixedWidth(90);
    grid->setAlignment(validID,Qt::AlignLeft | Qt::AlignTop);
    grid->addWidget(validID,0,3);

    memoButton = new QPushButton("Memo");
    memoButton->setEnabled(false);
    grid->addWidget(memoButton,0,4);

    timer = new QTimer(this);

    image = new QImage("Image/iconLogIn.png");
    image2 = image->scaled(300,200,Qt::KeepAspectRatio);

    img = new QLabel;
    img->setPixmap(QPixmap::fromImage(image2) );
    img->setStyleSheet("border: 2px solid black;");
    img->setFixedSize(390,220);
    grid->addWidget(img,0,0,2,1);
    grid->setAlignment(img,Qt::AlignLeft | Qt::AlignTop);


    update = add_WidgetStatus("Image/UPDATE.png");
    grid->addWidget(update,0,0,2,1);
    grid->setAlignment(update,Qt::AlignCenter);
    update->hide();


    closed = add_WidgetStatus("Image/closedStamp.png");
    grid->addWidget(closed,0,0,2,1);
    grid->setAlignment(closed,Qt::AlignCenter);
    closed->hide();

    QPushButton *zoomBte = new QPushButton;
    zoomBte->setMaximumSize(25,25);
    zoomBte->setIcon(QIcon("Image/zoom_in.png"));
    zoomBte->setIconSize(QSize(25,25));
    zoomBte->setToolTip("Zoom In Image");
    grid->addWidget(zoomBte,0,0,2,1);
    grid->setAlignment(zoomBte,Qt::AlignBottom | Qt::AlignRight);




    statut = new QLabel("---");
    statut->setFont(QFont("",10,10,false));


    for(int i=0;i<12;i++)
        tabInfo[i] = new QLabel("---");


    QWidget *wid_layout = new QWidget;
    wid_layout->setStyleSheet("background-color:#344956;");
    grid->addWidget(wid_layout,2,0,2,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setSpacing(0);
    vLayout->setMargin(2);
    wid_layout->setLayout(vLayout);

    vLayout->addWidget(add_styleWidget("Etat du compte",statut));
    vLayout->addWidget(add_styleWidget("ID",tabInfo[0]));
    vLayout->addWidget(add_styleWidget("Titre",tabInfo[1]));
    vLayout->addWidget(add_styleWidget("Nom",tabInfo[2]));
    vLayout->addWidget(add_styleWidget("Prenom",tabInfo[3]));
    vLayout->addWidget(add_styleWidget("Date de naissance",tabInfo[4]));
    vLayout->addWidget(add_styleWidget("Type de piece",tabInfo[5]));
    vLayout->addWidget(add_styleWidget("No de la piece",tabInfo[6]));
    vLayout->addWidget(add_styleWidget("Sexe",tabInfo[7]));



    QWidget *wid_layout2 = new QWidget;
    wid_layout2->setStyleSheet("background-color:#344956;");
    grid->addWidget(wid_layout2,4,0);

    QHBoxLayout *hlayout = new QHBoxLayout;
    wid_layout2->setLayout(hlayout);

    voirRef = new QPushButton("Voir la reference");
    voirRef->setFixedHeight(35);
    voirRef->setFixedWidth(150);
    voirRef->setEnabled(false);
    voirRef->setStyleSheet("background-color:white;color:#344956;");
    //voirRef->setFlat(true);
    hlayout->addWidget(voirRef);

    voirForm = new QPushButton("Voir le formulaire d'inscription");
    voirForm->setFixedHeight(35);
    voirForm->setFixedWidth(150);
    voirForm->setEnabled(false);
    //voirForm->setFlat(true);
    voirForm->setStyleSheet("background-color:white;color:#344956;");
    hlayout->addWidget(voirForm);


    noCompte = new QLCDNumber;
    noCompte->display(0);
    noCompte->setStyleSheet("background-color:#344956;color:white;");
    grid->addWidget(noCompte,0,6,1,1);



    model = new QSqlTableModel;
    model->setTable(QString("transaction_table_6"));
    model->setHeaderData(6,Qt::Horizontal,"QTE. JOURS");
    model->setHeaderData(8,Qt::Horizontal,"PAR QUI?");
    model->setHeaderData(9,Qt::Horizontal,"#RETRAIT");
    model->setHeaderData(10,Qt::Horizontal,"ID CLIENT");
    model->setHeaderData(12,Qt::Horizontal,"PHOTO DE LA FICHE DE RETRAIT");



    table = new QTableView;
    table->setModel(model);
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->resizeColumnsToContents();
    table->setColumnWidth(0,60);
    table->setColumnWidth(1,80);
    table->setColumnWidth(2,80);
    table->setColumnWidth(6,80);
    table->setColumnWidth(8,50);
    table->setColumnWidth(9,50);
    table->hideColumn(12);
    table->setItemDelegate(new Fen_Transaction_delegate(table));
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(table,1,1,2,6);


    debiter = new QPushButton("Debiter le compte");
    debiter->setIcon(QIcon("Image/debitIcon.png"));
    debiter->setFixedHeight(35);
    debiter->setFixedWidth(150);
    debiter->setEnabled(false);
    grid->addWidget(debiter,3,1);

    crediter = new QPushButton("Crediter le compte");
    crediter->setIcon(QIcon("Image/creditIcon.png"));
    crediter->setFixedHeight(35);
    crediter->setFixedWidth(150);
    crediter->setEnabled(false);
    grid->addWidget(crediter,4,1);


    QGroupBox *gp = new QGroupBox("Info sur le compte");
    grid->addWidget(gp,3,2,2,1);

    QFormLayout *form2 = new QFormLayout;
    gp->setLayout(form2);

    dateInscrip = new QLabel("---");
    form2->addRow("Date d'inscription:",dateInscrip);

    group = new QLabel("---");
    group->setFont(QFont("",15,15,false));
    form2->addRow("Groupe:",group);


    Jourspayee = new QLCDNumber;
    Jourspayee->display(0);
    grid->addWidget(add_styleHeader(QString::fromUtf8("Nombre de jours payé"),"#33A1C9",Jourspayee,"#344956"),3,3,2,1);


    JourRetirer = new QLCDNumber;
    JourRetirer->display(0);
    grid->addWidget(add_styleHeader("Nombre de retrait","#33A1C9",JourRetirer,"#344956"),3,4,2,1);
    JourRetirer->setStyleSheet("background-color:#344956;color:red;");



    QGroupBox *gpSolde = new QGroupBox("Solde du compte");
    grid->addWidget(gpSolde,3,5,2,1);

    QVBoxLayout *v1 = new QVBoxLayout;
    gpSolde->setLayout(v1);

    lcdSolde = new QLabel;
    lcdSolde->setFont(QFont("",12,12,false));
    lcdSolde->setText("0 HTG");
    v1->addWidget(lcdSolde);

    delaisJours = new QLCDNumber;
    delaisJours->display(0);
    grid->addWidget(add_styleHeader(QString::fromUtf8("Nombre de jours écoulé"),"#33A1C9",delaisJours,"#344956"),3,6,2,1);


    // .......,,,,,,,,,,,,,,,Load all the data,,,,,,,,,,,,,,,.........................

    querry.prepare("SELECT id FROM liste_client_6");
    if(querry.exec())
        while(querry.next())
            listID.append(querry.value(0).toString());

    querry.prepare("SELECT * FROM MemoTable");
    if(querry.exec())
        while(querry.next())
            listMemoMap.insert(querry.value(3).toInt(),querry.value(2).toString());
    //........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.........................

    QObject::connect(debiter,SIGNAL(clicked()),this,SLOT(afficheDebitDialog()));
    QObject::connect(crediter,SIGNAL(clicked()),this,SLOT(afficheCreditDialog()));
    QObject::connect(validID,SIGNAL(clicked()),this,SLOT(chercherClient()));
    QObject::connect(comboID,SIGNAL(returnPressed()),this,SLOT(chercherClient()));
    QObject::connect(voirRef,SIGNAL(clicked()),this,SLOT(showDialogRef()));
    QObject::connect(voirForm,SIGNAL(clicked()),this,SLOT(showDialogFormInscrip()));
    QObject::connect(table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onTriggered_showContextMenu(QPoint)));
    QObject::connect(zoomBte,SIGNAL(clicked()),this,SLOT(on_clicked_ZoomImage()));
    QObject::connect(timer ,  SIGNAL(timeout ()),this,SLOT(changeMemoButtonColor()));
    QObject::connect(memoButton,SIGNAL(pressed()),this,SLOT(onPressed_memoButton()));
    QObject::connect(memoButton,SIGNAL(clicked()),this,SLOT(showDialogMemo()));


}


QWidget* Fen_Transaction::add_styleWidget(QString dataname,QLabel *lab_Data)
{
    QWidget *wid = new QWidget;

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setSpacing(0);
    hlayout->setMargin(2);
    wid->setLayout(hlayout);

    QLabel *lab_dataName = new QLabel(dataname);
    lab_dataName->setFont(QFont("",10,QFont::Bold,false));
    lab_dataName->setMargin(5);
    lab_dataName->setMaximumHeight(40);
    lab_dataName->setStyleSheet("background-color:#33A1C9;color:white");
    hlayout->addWidget(lab_dataName);

    QLabel *lab_dataInfo = lab_Data;
    lab_dataInfo->setFont(QFont("",10,10,false));
    lab_dataInfo->setMargin(5);
    lab_dataInfo->setMaximumHeight(40);
    lab_dataInfo->setStyleSheet("background-color:#008080;color:white");
    hlayout->addWidget(lab_dataInfo);

    return wid;

}

QWidget* Fen_Transaction::add_styleHeader(QString titre,QString col_titre,QLCDNumber *data,QString col_data)
{
    QWidget *wid = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    wid->setLayout(v);


    QLabel *lab_titre = new QLabel(titre);
    lab_titre->setStyleSheet("background-color:"+col_titre+";color:white;");
    lab_titre->setFont(QFont("",8,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(25);
    v->addWidget(lab_titre);

    QLCDNumber *lcd_data = data;
    lcd_data->setStyleSheet("background-color:"+col_data+";color:white;");
    lcd_data->setFont(QFont("",12,12,false));
    v->addWidget(lcd_data);

    return wid;
}

QLabel *Fen_Transaction::add_WidgetStatus(QString pathImage)
{


    QImage *im1 = new QImage(pathImage);
    QImage im2 = im1->scaled(200,200,Qt::KeepAspectRatio);
    QLabel *lab_status = new QLabel;
    lab_status->setPixmap(QPixmap::fromImage(im2));
    return lab_status;
}

bool Fen_Transaction::checkID()
{
    //If ID_CLIENT exist and has memo
    if(listID.contains(comboID->text())){
        qDebug()<<"listID contains ID ";
        if(listMemoMap.keys().contains(comboID->text().toInt())){
            qDebug()<<"listMemoMap contains ID ";
            if(listMemoMap.value(comboID->text().toInt())=="Non"){
                qDebug()<<"listMemoMap contains Libelle";
                isMemoButtonNotPressed = true;
                //countTimer = 0;
                if(timer->isActive())
                    timer->stop();
                timer->start(1000);
                memoButton->setEnabled(true);
            }else{
                qDebug()<<"listMemoMap does not contains Libelle";
                if(timer->isActive())
                    timer->stop();
                memoButton->setStyleSheet("");
                memoButton->setEnabled(false);
            }
        }else{
            if(timer->isActive())
                timer->stop();
            memoButton->setStyleSheet("");
            memoButton->setEnabled(false);
        }
        return true;

        //If ID_CLIENT does not exist
    }else{
        QMessageBox::warning(this,"Error","Code n'existe pas dans la base");

        statut->setText("---");
        for(int i=0;i<12;i++)
            tabInfo[i]->setText("---");
        dateInscrip->setText("---");
        group->setText("---");
        lcdSolde->setText("0 HTG");

        debiter->setEnabled(false);
        crediter->setEnabled(false);
        delaisJours->display(0);
        model->setFilter("ID_CLIENT = -1");
        model->select();
        comboID->clear();

        voirRef->setEnabled(false);
        voirForm->setEnabled(false);

        image = new QImage("Image/iconLogIn.png");
        image2 = image->scaled(400,300,Qt::KeepAspectRatio);
        img->setPixmap(QPixmap::fromImage(image2));
        noCompte->display(0);
        Jourspayee->display(0);
        JourRetirer->display(0);
        update->hide();
        closed->hide();

        return false;
    }

}

void Fen_Transaction::chercherClient()
{
    etatcompte = false;
    if(checkID())
    {
        bool c = querry.exec("SELECT * FROM liste_client_6 WHERE id = "+comboID->text());

        if(!c){
            qDebug()<<"Not Selected info";

        }
        else{
            while(querry.next())
            {
                if(querry.value(33).toString()=="En cours")
                {
                    statut->setText(querry.value(33).toString());
                    statut->setStyleSheet("QLabel{background-color:green;color:white}");
                    etatcompte = true;
                }
                else
                {
                    statut->setText(querry.value(33).toString());
                    statut->setStyleSheet("QLabel{background-color:red;color:white}");
                }

                noCompte->display(querry.value(0).toString());
                tabInfo[0]->setText(querry.value(0).toString());
                tabInfo[1]->setText(querry.value(1).toString());
                tabInfo[2]->setText(querry.value(2).toString());
                tabInfo[3]->setText(querry.value(3).toString());
                tabInfo[4]->setText(querry.value(4).toString());
                tabInfo[5]->setText(querry.value(5).toString());
                tabInfo[6]->setText(querry.value(6).toString());
                tabInfo[7]->setText(querry.value(7).toString());
                tabInfo[8]->setText(querry.value(8).toString());
                tabInfo[9]->setText(querry.value(9).toString());
                tabInfo[10]->setText(querry.value(10).toString());
                tabInfo[11]->setText(querry.value(30).toString());

                dateInscrip->setText(querry.value(22).toString());
                group->setText(querry.value(23).toString());

                image = new QImage(querry.value(25).toString());
                image2 = image->scaled(400,300,Qt::KeepAspectRatio);
                img->setPixmap(QPixmap::fromImage(image2));

                lcdSolde->setText(QLocale(QLocale::English).toString(getSolde())+" HTG");
            }

            if(etatcompte == true)
            {
                model->setFilter("ID_CLIENT = "+comboID->text());
                model->setSort(0,Qt::AscendingOrder);
                model->select();
                debiter->setEnabled(true);
                crediter->setEnabled(true);
                voirRef->setEnabled(true);
                voirForm->setEnabled(true);
                delaisJours->display(setDelaisJour());
                table->scrollToBottom();
                setJoursPayee();
                setJoursRetirer();
                comboID->clear();
                closed->hide();

            }else
            {
                debiter->setEnabled(false);
                crediter->setEnabled(false);
                closed->show();
                model->setFilter("ID_CLIENT = "+comboID->text());
                model->select();
                comboID->clear();
                QMessageBox::warning(this,"Etat du compte","Le dossier de ce client est <closed>. Impossible d'effectuer des transactions.");

            }
        }
    }
}

void Fen_Transaction::afficheDebitDialog()
{
    debitDialog = new QDialog;
    debitDialog->setWindowIcon(QIcon("Image/debitIcon.png"));
    //debitDialog->setFixedSize(300,220);
    debitDialog->setMinimumWidth(400);
    debitDialog->setModal(true);
    debitDialog->setWindowTitle("Debiter le compte");


    QVBoxLayout *v = new QVBoxLayout;
    debitDialog->setLayout(v);

    QFormLayout *form = new QFormLayout;
    form->setSpacing(5);
    v->addLayout(form);

    date1 = new QDateEdit;
    date1->setFont(QFont("",10,10,false));
    date1->setCalendarPopup(true);
    date1->setDisplayFormat("dd/MM/yyyy");
    date1->setDateTime(QDateTime::currentDateTime());
    form->addRow("Date:",date1);

    int g = group->text().toInt();

    QLabel *groupDeb = new QLabel;
    groupDeb->setText(QString::number(g));
    form->addRow("Groupe:",groupDeb);


    QLabel *mtntMin = new QLabel(QString::number(g));
    form->addRow("Montant minimum:",mtntMin);

    spinDebit = new QSpinBox;
    spinDebit->setMinimum(1);
    spinDebit->setMaximum(9999999);
    form->addRow("Nombre de jour:",spinDebit);

    mtntTotal = new QSpinBox;
    mtntTotal->setFont(QFont("",20,20,false));
    mtntTotal->setMinimumHeight(20);
    mtntTotal->setMinimum(g);
    mtntTotal->setEnabled(false);
    mtntTotal->setMaximum(9999999);
    mtntTotal->setValue(g);
    form->addRow("Montant total (HTG):",mtntTotal);


    parQui = new QComboBox;
    parQui->addItem("Proprietaire");
    parQui->addItem("Reference");
    parQui->addItem("Autre");
    form->addRow("Par qui?:",parQui);

    delivre = new QComboBox;
    delivre->addItem("Oui");
    delivre->addItem("Non");
    form->addRow("Delivrer la transaction:",delivre);

    transacName = new QLineEdit();
    form->addRow("Nom du deposant:",transacName);


    QHBoxLayout *h = new QHBoxLayout;
    v->addLayout(h);

    deb = new QPushButton("Debiter");
    h->addWidget(deb);

    QPushButton *annuler = new QPushButton("fermer",debitDialog);
    h->addWidget(annuler);

    debitDialog->show();

    QObject::connect(annuler,SIGNAL(clicked()),SLOT(closeDebitDialog()));
    QObject::connect(deb,SIGNAL(clicked()),this,SLOT(debiterTransaction()));
    QObject::connect(spinDebit,SIGNAL(valueChanged(int)),SLOT(showMontantDeb(int)));

}

void Fen_Transaction::showMontantDeb(int i)
{

    mtntTotal->setValue(group->text().toInt() * i);
}

void Fen_Transaction::closeDebitDialog()
{
    debitDialog->close();
}

void Fen_Transaction::afficheCreditDialog()
{
    creditDialog = new QDialog;
    creditDialog->setWindowIcon(QIcon("Image/debitIcon.png"));
    //creditDialog->setFixedSize(300,250);
    creditDialog->setMinimumWidth(400);
    creditDialog->setModal(true);
    creditDialog->setWindowTitle("Credit le compte");


    QVBoxLayout *v = new QVBoxLayout;
    creditDialog->setLayout(v);

    QFormLayout *form = new QFormLayout;
    form->setSpacing(5);
    v->addLayout(form);

    date1 = new QDateEdit;
    date1->setFont(QFont("",10,10,false));
    date1->setCalendarPopup(true);
    date1->setDisplayFormat("dd/MM/yyyy");
    date1->setDateTime(QDateTime::currentDateTime());
    form->addRow("Date:",date1);

    noRetrait = new QSpinBox;
    noRetrait->setMaximum(99999);
    noRetrait->setEnabled(false);
    form->addRow("No de la fiche de retrait:",noRetrait);

    int g = group->text().toInt();

    QLabel *groupDeb = new QLabel;
    groupDeb->setText(QString::number(g));
    form->addRow("Groupe:",groupDeb);


    QLabel *mtntMin = new QLabel(QString::number(g));
    form->addRow("Montant minimum:",mtntMin);

    spinCredit = new QSpinBox;
    spinCredit->setMinimum(1);
    spinCredit->setMaximum(9999999);
    form->addRow("Nombre de jour:",spinCredit);

    mtntTotal = new QSpinBox;
    mtntTotal->setFont(QFont("",20,20,false));
    mtntTotal->setMinimumHeight(20);
    mtntTotal->setMinimum(g);
    mtntTotal->setEnabled(false);
    mtntTotal->setMaximum(9999999);
    mtntTotal->setValue(g);
    form->addRow("Montant total (HTG):",mtntTotal);

    QPushButton *balance = new QPushButton("Cliquer ici");
    form->addRow("Donner la balance apres frais:",balance);

    parQui = new QComboBox;
    parQui->addItem("Proprietaire");
    parQui->addItem("Reference");
    form->addRow("Par qui?:",parQui);

    delivre = new QComboBox;
    delivre->addItem("Oui");
    delivre->addItem("Non");
    form->addRow("Delivrer la transaction:",delivre);

    transacName = new QLineEdit();
    form->addRow("Par: ",transacName);

    QHBoxLayout *h = new QHBoxLayout;
    v->addLayout(h);

    cred = new QPushButton("Crediter");
    h->addWidget(cred);

    QPushButton *annuler = new QPushButton("fermer",creditDialog);
    h->addWidget(annuler);

    creditDialog->show();

    QObject::connect(annuler,SIGNAL(clicked()),SLOT(closeCreditDialog()));
    QObject::connect(cred,SIGNAL(clicked()),this,SLOT(crediterTransaction()));
    QObject::connect(spinCredit,SIGNAL(valueChanged(int)),SLOT(showMontantCred(int)));
    QObject::connect(balance,SIGNAL(clicked()),SLOT(activerBalance()));
}

void Fen_Transaction::activerBalance()
{
    mtntTotal->setMinimum(50);
    mtntTotal->setEnabled(true);
}

void Fen_Transaction::showMontantCred(int i)
{

    mtntTotal->setValue(group->text().toInt() * i);
}

void Fen_Transaction::closeCreditDialog()
{
    creditDialog->close();
}

bool Fen_Transaction::debiterTransaction()
{
        resBtn = QMessageBox::question( this,"Transaction: Debiter","Ce compte sera "+QString::fromUtf8("debité")+" de: "+mtntTotal->text()+" HTG. Cliquer sur Yes pour confirmer, ou No pour annuler",
                 QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

            if (resBtn == QMessageBox::Yes)
            {
                QString date = date1->date().toString("dd/MM/yyyy");
                if(mtntTotal->value()>0)
                {
                    qDebug()<<"Debiter le compte";
                    QString resultat2 = QString::number(getSolde()+ mtntTotal->value());


                    querry.prepare("INSERT INTO transaction_table_6"
                           "(DATE,HEURE,DESCRIPTION,DEPOTS,N_JOURS,SOLDE,PAR_QUI,ID_CLIENT,GROUPE,DELIVRE)"
                           "VALUES (:DATE,:HEURE,:DESCRIPTION,:DEPOTS,:N_JOURS,:SOLDE,:PAR_QUI,:ID_CLIENT,:GROUPE,:DELIVRE)");

                    querry.bindValue(":DATE",date);
                    querry.bindValue(":HEURE",QTime::currentTime().toString("hh:mm AP"));
                    querry.bindValue(":DESCRIPTION","DEPOT");
                    querry.bindValue(":DEPOTS",mtntTotal->text());
                    querry.bindValue(":N_JOURS",spinDebit->text());
                    querry.bindValue(":SOLDE",resultat2);
                    querry.bindValue(":PAR_QUI",parQui->currentText());
                    querry.bindValue(":ID_CLIENT",tabInfo[0]->text());
                    querry.bindValue(":GROUPE",group->text());
                    querry.bindValue(":DELIVRE",delivre->currentText());

                    bool c = querry.exec();

                    if(!c){
                        qDebug()<<"not Inserted debit";
                        qDebug()<< querry.lastError();
                    }
                    else
                    {
                        lastInsertID = querry.lastInsertId().toString();
                        transacType = "DEPOT";
                        balanceAccount = resultat2;
                        transacAmount = mtntTotal->text();
                        accountGroup = group->text();

                        model->setSort(0,Qt::AscendingOrder);
                        model->select();
                        table->scrollToBottom();
                        spinDebit->setValue(0);
                        lcdSolde->setText(QLocale(QLocale::English).toString(getSolde())+" HTG");
                        db->backupData();
                        setJoursPayee();
                        comboID->setFocus();
                        //querry.finish();

                        //printTransaction();
                        filePrint();
                        qDebug()<<"Inserted debit";
                    }
                }else
                    qDebug()<<"None";
                debitDialog->close();
            }else
                return false;


            return false;
}

bool Fen_Transaction::crediterTransaction()
{
    int checkSolde = getSolde()- mtntTotal->value();
    if(checkSolde<50)
    {
        QMessageBox::warning(this,"Montant insuffisant","Le solde est insuffisant pour faire ce retrait");
        return false;
    }
    else{
        resBtn = QMessageBox::question( this,"Transaction: Crediter","Ce compte sera "+QString::fromUtf8("credité")+" de: "+mtntTotal->text()\
                                        +" HTG. Cliquer sur Yes pour confirmer, ou No pour annuler",
                 QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

            if (resBtn == QMessageBox::Yes)
            {
                if(verifierAutorisation())
                {
                    QString date = date1->date().toString("dd/MM/yyyy");
                    if(mtntTotal->value()>0)
                    {
                        qDebug()<<"crediter le compte";
                        QString resultat2 = QString::number(getSolde()- mtntTotal->value());

                        querry.prepare("INSERT INTO transaction_table_6"
                               "(DATE,HEURE,DESCRIPTION,RETRAITS,N_JOURS,SOLDE,PAR_QUI,No_Retrait,ID_CLIENT,GROUPE,DELIVRE)"
                               "VALUES (:DATE,:HEURE,:DESCRIPTION,:RETRAITS,:N_JOURS,:SOLDE,:PAR_QUI,:No_Retrait,:ID_CLIENT,:GROUPE,:DELIVRE)");


                        querry.bindValue(":DATE",date);
                        querry.bindValue(":HEURE",QTime::currentTime().toString("hh:mm AP"));
                        querry.bindValue(":DESCRIPTION","RETRAIT");
                        querry.bindValue(":RETRAITS",mtntTotal->text());
                        querry.bindValue(":N_JOURS",spinCredit->text());
                        querry.bindValue(":SOLDE",resultat2);
                        querry.bindValue(":PAR_QUI",parQui->currentText());
                        querry.bindValue(":No_Retrait",noRetrait->text());
                        querry.bindValue(":ID_CLIENT",tabInfo[0]->text());
                        querry.bindValue(":GROUPE",group->text());
                        querry.bindValue(":DELIVRE",delivre->currentText());

                        bool c = querry.exec();
                        if(!c){
                            qDebug()<<"not Inserted credit";
                            qDebug()<<querry.lastError();
                        }
                        else
                        {
                            lastInsertID = querry.lastInsertId().toString();
                            transacType = "RETRAIT";
                            balanceAccount = resultat2;
                            transacAmount = mtntTotal->text();
                            accountGroup = group->text();

                            model->setSort(0,Qt::AscendingOrder);
                            model->select();
                            table->scrollToBottom();
                            spinCredit->setValue(0);
                            db->backupData();
                            setJoursRetirer();
                            lcdSolde->setText(QLocale(QLocale::English).toString(getSolde())+" HTG");
                            comboID->setFocus();
                            qDebug()<<"Inserted credit";

                            //printTransaction();
                            filePrint();

                        }
                    }
                    else
                        qDebug()<<"None";
                    creditDialog->close();
                }else{
                    QMessageBox::warning(this,"Pas de retrait","La reference n'a pas l'autorisation de faire des\nretraits sur le compte du proprietaire.");
                        return false;
                    }
            }
    }
    return true;
}

int Fen_Transaction::getSolde()
{

    solde = 0;
    totDebit = 0;
    totCredit = 0;
    querry.exec("SELECT SUM(DEPOTS),SUM(RETRAITS)"
                " FROM transaction_table_6 WHERE ID_CLIENT = "+tabInfo[0]->text()+" ");
    if(querry.next())
    {
        totCredit = querry.value(1).toInt();
        totDebit = querry.value(0).toInt();
    }

    solde = totDebit - totCredit;


    return solde;
}

QString Fen_Transaction::setDelaisJour()
{
    QString date1,nbreJours;
    bool c =querry.exec("SELECT * FROM liste_client_6 WHERE id = "+tabInfo[0]->text()+" ");

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

    querry.finish();

    return nbreJours;
}

void Fen_Transaction::showDialogRef()
{
    dialogReference = new QDialog;
    dialogReference->setMinimumSize(900,400);
    dialogReference->setModal(true);
    dialogReference->setWindowTitle("Information sur la reference");
    dialogReference->show();
    dialogReference->setStyleSheet("QDialog{background-color:white;}");

    QHBoxLayout *h = new QHBoxLayout;
    dialogReference->setLayout(h);

    QLabel *img = new QLabel;
    img->setStyleSheet("border: 2px solid black;");
    img->setMinimumSize(400,250);
    h->addWidget(img);

    for(int i=0;i<9;i++){
        tabRef[i] = new QLabel("--");
    }



    QWidget *wid_layout = new QWidget;
    wid_layout->setStyleSheet("background-color:#344956;");
    h->addWidget(wid_layout);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setSpacing(2);
    vLayout->setMargin(2);
    wid_layout->setLayout(vLayout);

    vLayout->addWidget(add_styleWidget("Titre",tabRef[0]));
    vLayout->addWidget(add_styleWidget("Nom",tabRef[1]));
    vLayout->addWidget(add_styleWidget("Prenom",tabRef[2]));
    vLayout->addWidget(add_styleWidget("Sexe",tabRef[3]));
    vLayout->addWidget(add_styleWidget("Adresse",tabRef[4]));
    vLayout->addWidget(add_styleWidget("Telephone",tabRef[5]));
    vLayout->addWidget(add_styleWidget("Type de piece",tabRef[6]));
    vLayout->addWidget(add_styleWidget("No de la piece",tabRef[7]));
    vLayout->addWidget(add_styleWidget("Autorisation de faire des retraits\nsur le compte du proprietaire",tabRef[8]));




    querry.exec("SELECT * FROM liste_client_6 WHERE id = "+tabInfo[0]->text()+" ");

    while(querry.next())
    {
        QImage *imgRef = new QImage(querry.value(26).toString());
        QImage img2 = imgRef->scaled(400,300,Qt::KeepAspectRatio);
        img->setPixmap(QPixmap::fromImage(img2));

        tabRef[0]->setText(querry.value(28).toString());
        tabRef[1]->setText(querry.value(16).toString());
        tabRef[2]->setText(querry.value(17).toString());
        tabRef[3]->setText(querry.value(29).toString());
        tabRef[4]->setText(querry.value(18).toString());
        tabRef[5]->setText(querry.value(19).toString());
        tabRef[6]->setText(querry.value(20).toString());
        tabRef[7]->setText(querry.value(21).toString());
        tabRef[8]->setText(querry.value(31).toString());

    }
}

void Fen_Transaction::showDialogFormInscrip()
{
    dialogFormInscrip = new QDialog;
    dialogFormInscrip->setFixedSize(600,650);
    dialogFormInscrip->setModal(true);
    dialogFormInscrip->setWindowTitle("Formulaire d'inscription");
    dialogFormInscrip->show();

    QVBoxLayout *v = new QVBoxLayout;
    dialogFormInscrip->setLayout(v);

    QLabel *img = new QLabel;
    img->setStyleSheet("border: 2px solid black;");
    img->setMinimumSize(500,500);
    img->setScaledContents(true);
    v->addWidget(img);

    querry.exec("SELECT * FROM liste_client_6 WHERE id = "+tabInfo[0]->text()+" ");

    while(querry.next())
    {
        QImage *imgRef = new QImage(querry.value(27).toString());
        QImage img2 = imgRef->scaled(1000,900,Qt::KeepAspectRatio);
        img->setPixmap(QPixmap::fromImage(img2));

    }
}

bool Fen_Transaction::verifierAutorisation()
{
    bool c = false;

    if(parQui->currentText()=="Proprietaire")
    {
        c = true;
        return c;
    }
    else
    {
        querry.exec("SELECT * FROM liste_client_6 WHERE id = "+tabInfo[0]->text()+" ");
        while(querry.next())
        {
            if(querry.value(31).toString()=="Oui")
                c = true;
        }
        return c;
    }
}

void Fen_Transaction::onTriggered_showContextMenu(QPoint p)
{
    QMenu contextMenu(tr("Context Menu"),table);

    QAction action("Supprimer la transaction",this);

    connect(&action,SIGNAL(triggered()),this,SLOT(supprimerData()));
    contextMenu.addAction(&action);
    contextMenu.exec(QCursor::pos());

}

void Fen_Transaction::supprimerData()
{
    int row = table->selectionModel()->currentIndex().row();
    QString iden = model->index(row,0).data().toString();

    if(!iden.isEmpty())
    {
        bool ok = false;
        QString nom = QInputDialog::getText(this, "Mots de passe", "Veuillez entrer le mots de passe pour la suppression.",QLineEdit::Normal, QString(), &ok);

        if (ok && !nom.isEmpty())
        {
            if(ok && nom=="1234")
            {

                QMessageBox::StandardButton resBtnYes = QMessageBox::question( this,"Close",tr("Voulez-vous vraiment supprimer ce donnee?\n"),
                         QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

                if(resBtnYes == QMessageBox::Yes)
                {
                    bool c = querry.exec("DELETE FROM transaction_table_6 WHERE ID = "+iden+"  ");
                    if(!c)
                        qDebug()<<"pas effacer";
                    else{
                            querry.finish();
                            qDebug()<<"effacer";
                            model->select();
                            lcdSolde->setText(QLocale(QLocale::English).toString(getSolde())+" HTG");
                            setJoursPayee();
                        }
                }
            }else
                QMessageBox::warning(this,"Erreur","Mots de passe incorrect.");
        }
    }
}

void Fen_Transaction::setJoursPayee()
{
    int somjour = 0;
    querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+tabInfo[0]->text()+" AND DESCRIPTION ='DEPOT' ");

    while(querry.next())
    {
        somjour += querry.value(6).toInt();
    }

    Jourspayee->display(somjour);
    querry.finish();
}

void Fen_Transaction::setJoursRetirer()
{
    int somjour = 0;
    querry.exec("SELECT * FROM transaction_table_6 WHERE ID_CLIENT = "+tabInfo[0]->text()+" AND DESCRIPTION ='RETRAIT' ");

    while(querry.next())
    {
        somjour += querry.value(6).toInt();
    }

    JourRetirer->display(somjour);
    querry.finish();
}

void Fen_Transaction::on_clicked_ZoomImage()
{

    QDialog *diag = new QDialog(this);
    diag->setFixedSize(800,400);

    QVBoxLayout *v = new QVBoxLayout;
    diag->setLayout(v);
    diag->setModal(true);

    QImage *im1 = image;
    QImage im2 = im1->scaled(900,600,Qt::KeepAspectRatio);
    QLabel *zoomIn = new QLabel;
    zoomIn->setPixmap(QPixmap::fromImage(im2));

    v->addWidget(zoomIn);

    diag->show();

}

void Fen_Transaction::onPressed_memoButton()
{
    timer->stop();
    memoButton->setStyleSheet("");
}

void Fen_Transaction::showDialogMemo()
{
    QDialog *diagMemo = new QDialog;
    diagMemo->setModal(true);
    diagMemo->setMinimumWidth(500);
    diagMemo->setWindowTitle("Memo");

    QVBoxLayout *vbox = new QVBoxLayout;
    diagMemo->setLayout(vbox);

    QSqlTableModel *modelMemo = new QSqlTableModel;
    modelMemo->setTable("MemoTable");
    modelMemo->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelMemo->select();

    QTableView *tableMemo = new QTableView;
    tableMemo->setModel(modelMemo);
    tableMemo->setAlternatingRowColors(true);
    tableMemo->resizeRowsToContents();
    tableMemo->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableMemo->setItemDelegate(new Fen_ClientProfil_document_delegate(tableMemo));
    vbox->addWidget(tableMemo);

    modelMemo->setFilter("ID_CLIENT = "+tabInfo[0]->text());



    diagMemo->show();
}

void Fen_Transaction::changeMemoButtonColor()
{

    if(isMemoButtonNotPressed){
        memoButton->setStyleSheet("background-color:red;color:white;");
        isMemoButtonNotPressed = false;
    }else{
        memoButton->setStyleSheet("background-color:green;color:white;");
        isMemoButtonNotPressed = true;
    }

    //qDebug()<<" Timer is on "<<countTimer++;

}

void Fen_Transaction::printTransaction() {
    QPrinter *printer = new QPrinter(QPrinter::HighResolution );

    QPrintPreviewDialog *preview = new QPrintPreviewDialog(printer,this);
    preview->setMinimumWidth(800);

    connect(preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    preview->exec();

}

void Fen_Transaction::filePrint()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer,this);
    print(&printer);
    dialog.accept();

}

void Fen_Transaction::print(QPrinter *printer)
{
    QPainter painter;
    painter.begin(printer);

    int      w = printer->pageRect().width();
    int      h = printer->pageRect().height();
    QRect    page( 0, 0, w, h );

    // create a font appropriate to page size
    QFont    font = painter.font();
    font.setPixelSize( (w+h) / 150 );
    painter.setFont( font );

    addHeader(&painter,page,printer);
    // draw simulated landscape
    page.adjust( w/20, h/20, -w/20, -h/20 );

    painter.end();

}

void Fen_Transaction::addHeader(QPainter *painter, QRect page,QPrinter *printer)
{
    painter->drawImage(80, 80,QImage("Image/logo1.jpg").scaled(400,400,Qt::KeepAspectRatio));
    painter->drawText(50,250,date1->date().toString("dd/MM/yyyy") + "   " + QTime::currentTime().toString("hh:mm AP"));
    painter->drawText(50,280,"ACCOUNT# " + tabInfo[0]->text());
    painter->drawText(50,310,"GROUPE: " + accountGroup);
    painter->drawText(50,340,"TRANSAC. TYPE: " + transacType);


    addText(painter, printer);
}

void Fen_Transaction::addText(QPainter *painter,QPrinter *printer)
{
    painter->drawLine(50,350,500,350);
    painter->drawText(50,400,"TRANSAC. AMOUNT: " + transacAmount + " HTG");
    painter->drawText(50,420,"BALANCE: " + balanceAccount + " HTG");

    painter->drawText(50,1150,transacName->text());
    addFooter(painter);
}

void Fen_Transaction::addFooter(QPainter *painter) {
    painter->drawLine(50,1200,500,1200);
    painter->drawText(250,1250,"#" + lastInsertID);

}
