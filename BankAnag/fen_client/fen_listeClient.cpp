#include "fen_listeClient.h"

Fen_ListeClient::Fen_ListeClient(QWidget *parent) :
    QWidget(parent)
{



}



Fen_ListeClient::Fen_ListeClient(QSqlQuery q,QMdiArea *c)
{
    querry = q;
    central = c;

    LayoutLister = new QGridLayout;
    this->setLayout(LayoutLister);


    QGroupBox *grp = new QGroupBox("Quantite de compte");
    LayoutLister->addWidget(grp,0,3,3,2);

    QVBoxLayout *vl = new QVBoxLayout;
    grp->setLayout(vl);

    lcdclient = new QLCDNumber;
    vl->addWidget(lcdclient);
    lcdclient->display(0);


    group25 = new QLabel("---");
    group25->setFont(QFont("",10,10,false));
    LayoutLister->addWidget(add_styleWidget("Groupe 25",group25),4,3,1,2);


    group50 = new QLabel("---");
    group50->setFont(QFont("",10,10,false));
    LayoutLister->addWidget(add_styleWidget("Groupe 50",group50),5,3,1,2);


    group100 = new QLabel("---");
    group100->setFont(QFont("",10,10,false));
    LayoutLister->addWidget(add_styleWidget("Groupe 100",group100),6,3,1,2);

    group250 = new QLabel("---");
    group250->setFont(QFont("",10,10,false));
    LayoutLister->addWidget(add_styleWidget("Groupe 250",group250),7,3,1,2);

    remplirListe();

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

    table = new QTableView;
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->resizeColumnsToContents();
    table->setMinimumWidth(1050);

    //table->resizeColumnsToContents();
    LayoutLister->addWidget(table,0,1,9,2);

    QVBoxLayout *vLayout_bouton = new QVBoxLayout;
    LayoutLister->addLayout(vLayout_bouton,0,0,9,1);

    bajout = new QPushButton;
    bajout->setToolTip("Rechercher");
    bajout->setFixedSize(40,40);
    bajout->setIcon(QIcon("Image/searchIcon.png"));
    bajout->setIconSize(QSize(30,30));
    bajout->setFlat(true);
    vLayout_bouton->addWidget(bajout);

    bmodifier = new QPushButton;
    bmodifier->setToolTip("Modifier");
    bmodifier->setFixedSize(40,40);
    bmodifier->setIcon(QIcon("Image/modifyIcon.png"));
    bmodifier->setIconSize(QSize(30,30));
    bmodifier->setFlat(true);
    vLayout_bouton->addWidget(bmodifier);

    bimprimer = new QPushButton;
    bimprimer->setToolTip("Imprimer");
    bimprimer->setFixedSize(40,40);
    bimprimer->setIcon(QIcon("Image/printIcon.png"));
    bimprimer->setIconSize(QSize(30,30));
    bimprimer->setFlat(true);
    vLayout_bouton->addWidget(bimprimer);

    bsupprimer = new QPushButton;
    bsupprimer->setToolTip("Supprimer");
    bsupprimer->setFixedSize(40,40);
    bsupprimer->setIcon(QIcon("Image/deleteIcon.png"));
    bsupprimer->setIconSize(QSize(30,30));
    bsupprimer->setFlat(true);
    vLayout_bouton->addWidget(bsupprimer);

    QPushButton *refresh = new QPushButton;
    refresh->setToolTip("Refresh");
    refresh->setFixedSize(40,40);
    refresh->setIcon(QIcon("Image/refresh.png"));
    refresh->setIconSize(QSize(30,30));
    refresh->setFlat(true);
    vLayout_bouton->addWidget(refresh);


    QObject::connect(bajout,SIGNAL(clicked()),this,SLOT(chercherData()));
    QObject::connect(bsupprimer,SIGNAL(clicked()),this,SLOT(supprimerData()));
    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showClientAccount()));
    QObject::connect(refresh,SIGNAL(clicked()),this,SLOT(refreshListe()));
}

void Fen_ListeClient::chercherData()
{
    dialogRecherche = new QDialog;
    dialogRecherche->setFixedSize(QSize(250,100));
    dialogRecherche->setModal(true);
    dialogRecherche->show();


    QVBoxLayout *v = new QVBoxLayout;
    dialogRecherche->setLayout(v);

    comRecherche = new QComboBox;
    comRecherche->addItem("id");
    comRecherche->addItem("Titre");
    comRecherche->addItem("Nom");
    comRecherche->addItem("Prenom");
    comRecherche->addItem("Date_De_Naissance");
    comRecherche->addItem("typePiece");
    comRecherche->addItem("No_piece");
    comRecherche->addItem("Sexe");
    comRecherche->addItem("Domaine_Activite");
    comRecherche->addItem("Telephone_1");
    comRecherche->addItem("Telephone_2");
    comRecherche->addItem("Adresse");
    comRecherche->addItem("Email");
    comRecherche->addItem("Pays");
    comRecherche->addItem("Provence");
    comRecherche->addItem("Code_postal");
    comRecherche->addItem("Nom_ref");
    comRecherche->addItem("Prenom_ref");
    comRecherche->addItem("Adresse_ref");
    comRecherche->addItem("Telephone_ref");
    comRecherche->addItem("typePiece_ref");
    comRecherche->addItem("No_piece_ref");
    comRecherche->addItem("Date_inscription");
    comRecherche->addItem("Groupe");
    comRecherche->addItem("Montant_com");
    comRecherche->addItem("Photo");
    comRecherche->addItem("PhotoRef");
    comRecherche->addItem("FormeInscription");
    comRecherche->addItem("TitreRef");
    comRecherche->addItem("SexeRef");
    comRecherche->addItem("NomMere");
    comRecherche->addItem("AutorisationRef");
    comRecherche->addItem("Nationalite");
    comRecherche->addItem("Statut");

    v->addWidget(comRecherche);

    editRecherch = new QLineEdit;
    v->addWidget(editRecherch);


    QPushButton *btnChercher = new QPushButton("Chercher");
    v->addWidget(btnChercher);

    editRecherch->setFocus();

    QObject::connect(btnChercher,SIGNAL(clicked()),this,SLOT(filtrerData()));
    QObject::connect(editRecherch,SIGNAL(returnPressed()),this,SLOT(filtrerData()));

}

QWidget* Fen_ListeClient::add_styleWidget(QString titre,QLabel * data)
{
    QWidget *wid = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    wid->setLayout(v);


    QLabel *lab_titre = new QLabel(titre);
    lab_titre->setStyleSheet("background-color:#8B8B7A;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    v->addWidget(lab_titre);

    QLabel *lab_data = data;
    lab_data->setStyleSheet("background-color:#344956;color:white;");
    lab_data->setAlignment(Qt::AlignCenter);
    lab_data->setFont(QFont("",20,20,false));
    lab_data->setMargin(5);
    v->addWidget(lab_data);

    return wid;
}

void Fen_ListeClient::filtrerData()
{
    int c = 0;
    int cpt = 0;
    qteClient = 0;

    int qte25=0,qte50=0,qte100=0,qte250=0;


     for(int i = 0; i<editRecherch->text().size();i++){
         if(editRecherch->text()[i]>='0' && editRecherch->text()[i]<='9'){
             c++;
         }
     }

     if(editRecherch->text().isEmpty())
         return;
     else if(c == editRecherch->text().size())
     {
         model->setFilter(" "+comRecherche->currentText()+" = " +editRecherch->text()+ " ");
         model->select();


         querry.exec("SELECT * FROM liste_client_6 WHERE "+comRecherche->currentText()+" = " +editRecherch->text()+ " ");
         while(querry.next())
         {
             cpt++;
             qteClient++;
             if(querry.value(23).toString()=="25")
             {
                 qte25++;


             }else if(querry.value(23)=="50")
             {
                 qte50++;

             }else if(querry.value(23)=="100")
             {
                 qte100++;

             }else if(querry.value(23)=="250")
             {
                 qte250++;

             }
         }

         lcdclient->display(cpt);
         dialogRecherche->close();

     }else
     {
        model->setFilter(" "+comRecherche->currentText()+" = '"+editRecherch->text()+"' ");
        model->select();


        querry.exec("SELECT * FROM liste_client_6 WHERE "+comRecherche->currentText()+" = '" +editRecherch->text()+ "' ");
        while(querry.next())
        {
            cpt++;
            qteClient++;
            if(querry.value(23).toString()=="25")
            {
                qte25++;


            }else if(querry.value(23)=="50")
            {
                qte50++;

            }else if(querry.value(23)=="100")
            {
                qte100++;

            }else if(querry.value(23)=="250")
            {
                qte250++;

            }
        }

        lcdclient->display(cpt);
        dialogRecherche->close();
     }

     lcdclient->display(qteClient);

     group25->setText(QString::number(qte25));
     group50->setText(QString::number(qte50));
     group100->setText(QString::number(qte100));
     group250->setText(QString::number(qte250));
}



void Fen_ListeClient::supprimerData()
{
    int row = table->selectionModel()->currentIndex().row();
    QString id = model->index(row,0).data().toString();


    if(id.isEmpty())
    {
        QMessageBox::warning(this,"Erreur","Selectionnez un element dans le tableau pour le supprimer.");
        return;
    }else
    {
        bool ok = false;
        QString nom = QInputDialog::getText(this, "Mots de passe", "Veuillez entrer le mots de passe pour supprimer le client.",QLineEdit::Normal, QString(), &ok);

        if (ok && !nom.isEmpty())
        {
            if(ok && nom=="1234")
            {

                QMessageBox::StandardButton resBtnYes = QMessageBox::question( this,"Close",tr("Voulez-vous vraiment supprimer ce donnee?\n"),
                         QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

                if(resBtnYes == QMessageBox::Yes)
                {
                    bool c = querry.exec("DELETE FROM liste_client_6 WHERE id = "+id+"  ");
                    if(!c)
                        qDebug()<<"pas effacer";
                    else{
                            qDebug()<<"effacer";
                            model->select();
                            remplirListe();
                        }
                }
            }else
                QMessageBox::warning(this,"Erreur","Mots de passe incorrect.");
        }
    }
}


void Fen_ListeClient::showClientAccount()
{
    QWidget *w = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    w->setLayout(v);

    int row = table->selectionModel()->currentIndex().row();
    QString id = model->index(row,0).data().toString();

    ClientAccount = new Fen_ClientProfile(id,querry);
    v->addWidget(ClientAccount);

    QPushButton *close = new QPushButton("Fermer");
    close->setFixedHeight(30);
    close->setIcon(QIcon("Image/bclose.png"));
    v->addWidget(close);
    v->setAlignment(close,Qt::AlignRight);

    fenClientProfil = central->addSubWindow(w);
    fenClientProfil->setWindowTitle("Compte du client");
    fenClientProfil->setMinimumSize(central->size());
    fenClientProfil->show();

    QObject::connect(close,SIGNAL(clicked()),this,SLOT(fermerFenClientProfil()));
}

void Fen_ListeClient::fermerFenClientProfil()
{
    fenClientProfil->close();
}


void Fen_ListeClient::chercherClient()
{
    model->setFilter("ID = "+searchEdit->text() );
    model->select();
    searchEdit->clear();

    remplirListe();
}

void Fen_ListeClient::refreshListe()
{
    model->setFilter("ID >0 " );
    model->select();
    lcdclient->display(qteClient);
    remplirListe();
}


void Fen_ListeClient::remplirListe()
{
    qteClient = 0;
    querry.prepare("SELECT COUNT(id),SUM(Groupe='25'),SUM(Groupe='50'),SUM(Groupe='100'),SUM(Groupe='250') FROM liste_client_6");
    if(querry.exec())
        if(querry.first())
        {
            //qDebug()<<querry.value(0).toString();

            qteClient = querry.value(0).toInt();
            lcdclient->display(qteClient);

            group25->setText(QString::number(querry.value(1).toInt()));
            group50->setText(QString::number(querry.value(2).toInt()));
            group100->setText(QString::number(querry.value(3).toInt()));
            group250->setText(QString::number(querry.value(4).toInt()));

        }

}
