#include "fen_caisse.h"


void Fen_Caisse::set_AchatVenteMarchandisePage(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);


    QHBoxLayout *hwd = new QHBoxLayout;
    hwd->setMargin(0);
    grid->addLayout(hwd,0,0,1,2);
    grid->setColumnStretch(0,2);

    QLabel *nomWd = new QLabel("Emprunteur: ");
    nomWd->setStyleSheet("background-color:lightgray;color:#344956;");
    nomWd->setFont(QFont("Dotum",12,12,false));
    nomWd->setMargin(5);
    hwd->addWidget(nomWd,0);

    investmentComboList = new QComboBox;
    investmentComboList->setMinimumHeight(30);
    hwd->addWidget(investmentComboList,5);

    modelInvestissement = new QSqlTableModel;
    modelInvestissement->setTable("investmentTable2");
    modelInvestissement->select();

    tableInvestissement = new QTableView;
    tableInvestissement->setMinimumWidth(800);
    tableInvestissement->setModel(modelInvestissement);
    tableInvestissement->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableInvestissement->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableInvestissement->setAlternatingRowColors(true);
    tableInvestissement->setContextMenuPolicy(Qt::CustomContextMenu);
    tableInvestissement->setColumnWidth(0,50);
    tableInvestissement->setColumnWidth(1,100);
    tableInvestissement->setColumnWidth(2,300);
    tableInvestissement->setColumnWidth(3,200);
    tableInvestissement->hideColumn(6);
    tableInvestissement->hideColumn(7);
    grid->addWidget(tableInvestissement,1,0,1,3);


    QWidget *wid_layout1 = new QWidget;
    wid_layout1->setMinimumSize(QSize(200,200));
    wid_layout1->setStyleSheet("background-color:#efefef;");
    grid->addWidget(wid_layout1,0,3,2,1);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    wid_layout1->setLayout(vLayout1);

    QPushButton *b_addInvestissement = new QPushButton("Ajouter un nouveau\ninvestissement");
    b_addInvestissement->setStyleSheet("background-color:#344956;color:white;");
    b_addInvestissement->setMinimumHeight(25);
    vLayout1->addWidget(b_addInvestissement);

    QLabel *lab_titre1 = new QLabel("Bilan sur les investissements");
    lab_titre1->setFont(QFont("",10,QFont::Bold,false));
    lab_titre1->setMaximumHeight(30);
    lab_titre1->setMargin(5);
    lab_titre1->setStyleSheet("background-color:#DB532B;color:white;");
    lab_titre1->setAlignment(Qt::AlignCenter);
    vLayout1->addWidget(lab_titre1);

    QWidget *wid_layout2 = new QWidget;
    wid_layout2->setStyleSheet("background-color:#27ae60;color:white");
    vLayout1->addWidget(wid_layout2);

    QFormLayout *form_achaVente = new QFormLayout;
    wid_layout2->setLayout(form_achaVente);

    lab_totalAchat = new QLabel("---");
    lab_totalAchat->setFont(QFont("",9,QFont::Bold,false));
    form_achaVente->addRow("Total des OUTs: ",lab_totalAchat);

    lab_totalVente = new QLabel("---");
    lab_totalVente->setFont(QFont("",9,QFont::Bold,false));
    form_achaVente->addRow("Total des INs: ",lab_totalVente);

    lab_diff = new QLabel("---");
    lab_diff->setFont(QFont("",9,QFont::Bold,false));
    form_achaVente->addRow("Difference: ",lab_diff);

    lab_versements = new QLabel("---");
    lab_versements->setFont(QFont("",9,QFont::Bold,false));
    form_achaVente->addRow("Profit: ",lab_versements);


    connect(investmentComboList,SIGNAL(activated(QString)),this,SLOT(onActivatedComboList(QString)));
    connect(tableInvestissement,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenutableInvestissement(QPoint)));
    connect(b_addInvestissement,SIGNAL(clicked()),this,SLOT(showAddInvestissementDialog()));
    connect(tableInvestissement,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onDoubleClickedTableRowInvest(QModelIndex)));

}

void Fen_Caisse::onActivatedComboList(QString item)
{
    modelInvestissement->setFilter("EMPRUNTEUR = '"+item+"' ");
}

void Fen_Caisse::showContextMenutableInvestissement(QPoint p)
{
    Q_UNUSED(p);

    QMenu contextMenu(tr("Context Menu"),tableInvestissement);

    QAction action("effacer l'investissement",this);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerDataRapporttableInvestissement()));
    contextMenu.addAction(&action);
    contextMenu.exec(QCursor::pos());
}


void Fen_Caisse::effacerDataRapporttableInvestissement()
{
    int row = tableInvestissement->selectionModel()->currentIndex().row();
    modelInvestissement->removeRow(row,QModelIndex());
    modelInvestissement->select();
    actualiseData();
}


void Fen_Caisse::showAddInvestissementDialog()
{
    diagInvestissement = new QDialog(this);
    diagInvestissement->setModal(true);
    diagInvestissement->setMinimumWidth(600);
    diagInvestissement->setWindowTitle("Ajouter un nouveau investissement");

    QGridLayout *grid = new QGridLayout;
    diagInvestissement->setLayout(grid);

    QLabel *emprunteur_lab = new QLabel("Emprunteur");
    grid->addWidget(emprunteur_lab,0,0);

    emprunteurInvest_edit = new QLineEdit;
    emprunteurInvest_edit->setPlaceholderText("Nom et Prenom");
    grid->addWidget(emprunteurInvest_edit,1,0);

    QLabel *date_lab = new QLabel("Date de l'investissement");
    grid->addWidget(date_lab,0,1);

    dateInvest_dateEdit = new QDateEdit;
    dateInvest_dateEdit->setCalendarPopup(true);
    dateInvest_dateEdit->setDate(QDate::currentDate());
    grid->addWidget(dateInvest_dateEdit,1,1);

    QLabel *montant_lab = new QLabel("Montant de l'investissement");
    grid->addWidget(montant_lab,2,0);

    montant_doubleSpin = new QDoubleSpinBox;
    montant_doubleSpin->setMaximum(999999.99);
    grid->addWidget(montant_doubleSpin,3,0);

    typeEspece_comb = new QComboBox;
    typeEspece_comb->addItem("--Type d'espece--");
    typeEspece_comb->addItem("HTG");
    typeEspece_comb->addItem("USD");
    grid->addWidget(typeEspece_comb,2,1);

    QHBoxLayout *hbox = new QHBoxLayout;
    grid->addLayout(hbox,3,1);

    QLabel *taux_lab = new QLabel("Taux:");
    hbox->addWidget(taux_lab);

    typeEspece_doubleSpin = new QDoubleSpinBox;
    typeEspece_doubleSpin->setMaximum(9999.99);
    typeEspece_doubleSpin->setEnabled(false);
    hbox->addWidget(typeEspece_doubleSpin);

    montant_totInvest = new QDoubleSpinBox;
    montant_totInvest->setFont(QFont("Datus",12,12,false));
    montant_totInvest->setEnabled(false);
    montant_totInvest->setMaximum(999999.99);
    grid->addWidget(montant_totInvest,4,0,1,1);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    grid->addLayout(hbox2,4,1,1,1);

    QLabel *period_lab = new QLabel("Periode de versement");
    hbox2->addWidget(period_lab);

    periodInvest_comb = new QComboBox;
    periodInvest_comb->addItem("Par semaine");
    periodInvest_comb->addItem("Par mois");
    periodInvest_comb->addItem("Par trimestre");
    periodInvest_comb->addItem("Par semetre");
    periodInvest_comb->addItem("Par annee");
    periodInvest_comb->addItem("Par occasion");
    hbox2->addWidget(periodInvest_comb);

    QLabel *descript_lab = new QLabel("Description de l'investissement");
    grid->addWidget(descript_lab,5,0);

    descriptInvest_text = new QTextEdit;
    grid->addWidget(descriptInvest_text,6,0,1,2);

    QPushButton *ajout_pushBte = new QPushButton("Ajouter");
    grid->addWidget(ajout_pushBte,7,0,1,2);

    diagInvestissement->show();

    connect(montant_doubleSpin,SIGNAL(valueChanged(double)),this,SLOT(onValueMontantDoubleSpinChanged(double)));
    connect(typeEspece_doubleSpin,SIGNAL(valueChanged(double)),this,SLOT(onValueTypeEspeceDoubleSpinChanged(double)));
    connect(typeEspece_comb,SIGNAL(activated(int)),this,SLOT(onTypeEspeceCombActived(int)));
    connect(ajout_pushBte,SIGNAL(clicked()),this,SLOT(onClickedAjoutInvestissementBtn()));
}


void Fen_Caisse::onTypeEspeceCombActived(int idx)
{
    if(idx==0 || idx==1)
        typeEspece_doubleSpin->setEnabled(false);
    else if(typeEspece_comb->currentIndex()==2)
        typeEspece_doubleSpin->setEnabled(true);
}

void Fen_Caisse::onValueMontantDoubleSpinChanged(double d)
{
    if(typeEspece_comb->currentIndex()==0 || typeEspece_comb->currentIndex()==1)
        montant_totInvest->setValue(d);
    else if(typeEspece_comb->currentIndex()==2)
        montant_totInvest->setValue(d*typeEspece_doubleSpin->value());
}


void Fen_Caisse::onValueTypeEspeceDoubleSpinChanged(double d)
{
    if(typeEspece_comb->currentIndex()==0 || typeEspece_comb->currentIndex()==1)
        montant_totInvest->setValue(d*montant_doubleSpin->value());
    else if(typeEspece_comb->currentIndex()==2)
        montant_totInvest->setValue(d*montant_doubleSpin->value());
}

void Fen_Caisse::onClickedAjoutInvestissementBtn()
{
    querry.prepare("INSERT INTO investmentTable2 (DATE,DESCRIPTION,[MONTANT D'INVESTISSEMENT],"
                   "PERIOD,EMPRUNTEUR,[MONTANT USD],TAUX)"
                   "VALUES (:date,:description,:montant,:period,:emprunteur,:montantUSD,:taux)");

    querry.bindValue(":date",dateInvest_dateEdit->date());
    querry.bindValue(":description",descriptInvest_text->toPlainText());
    querry.bindValue(":montant",montant_totInvest->value());
    querry.bindValue(":period",periodInvest_comb->currentText());
    querry.bindValue(":emprunteur",emprunteurInvest_edit->text());

    if(typeEspece_comb->currentIndex()==2){
        querry.bindValue(":montantUSD",montant_doubleSpin->value());
        querry.bindValue(":taux",typeEspece_doubleSpin->value());
    }else{
        querry.bindValue(":montantUSD",0.00);
        querry.bindValue(":taux",0.00);
    }

    if(querry.exec())
    {
        descriptInvest_text->clear();
        montant_totInvest->setValue(0.00);
        periodInvest_comb->setCurrentIndex(0);
        emprunteurInvest_edit->clear();
        modelInvestissement->select();
        diagInvestissement->close();
        actualiseData();

    }else{
        qDebug()<<querry.lastError();
    }

}


void Fen_Caisse::actualiseData()
{
    double totInvest = 0, totVersement = 0;
    QStringList listEmprunteur;
    investmentComboList->clear();

    querry.prepare("SELECT * FROM investmentTable2");
    if(querry.exec()){
        while(querry.next()){
            totInvest += querry.value(3).toDouble();

            if(!listEmprunteur.contains(querry.value(5).toString()))
                listEmprunteur.append(querry.value(5).toString());
        }
    }

    querry.finish();

    querry.prepare("SELECT * FROM versementInvestment");
    if(querry.exec())
        while(querry.next()){
            totVersement += querry.value(3).toDouble();

        }


    lab_totalAchat->setText(QLocale(QLocale::English).toString(totInvest));
    investmentComboList->addItems(listEmprunteur);

    lab_totalVente->setText(QLocale(QLocale::English).toString(totVersement));

    if((totInvest-totVersement)>0)
        lab_diff->setText(QLocale(QLocale::English).toString(totInvest-totVersement));
    else
        lab_diff->setText("0");




    if((totInvest-totVersement)<=0)
        lab_versements->setText(QLocale(QLocale::English).toString((totInvest-totVersement)*-1));
    else
        lab_versements->setText("0");
}


void Fen_Caisse::onDoubleClickedTableRowInvest(QModelIndex idx)
{
    QDialog *diag = new QDialog;
    diag->setWindowTitle("Liste des versements");
    diag->setModal(true);

    QGridLayout *grid = new QGridLayout;
    diag->setLayout(grid);

    QFormLayout *form1 = new QFormLayout;
    grid->addLayout(form1,0,0);

    QString id = modelInvestissement->data(modelInvestissement->index(idx.row(),0,QModelIndex())).toString();
    idInvestissement_label = new QLabel(id);
    form1->addRow("ID:",idInvestissement_label);

    QString date = modelInvestissement->data(modelInvestissement->index(idx.row(),1,QModelIndex())).toString();
    QLabel *date_label = new QLabel(date);
    form1->addRow("DATE:",date_label);

    QString emprunteur = modelInvestissement->data(modelInvestissement->index(idx.row(),5,QModelIndex())).toString();
    QLabel *emprunteur_label = new QLabel(emprunteur);
    form1->addRow("EMPRUNTEUR:",emprunteur_label);

    QFormLayout *form2 = new QFormLayout;
    grid->addLayout(form2,0,1);

    QString descrip = modelInvestissement->data(modelInvestissement->index(idx.row(),2,QModelIndex())).toString();
    QLabel *description_label = new QLabel(descrip);
    form2->addRow("DESCRIPTION:",description_label);

    QString mtntUSD = modelInvestissement->data(modelInvestissement->index(idx.row(),6,QModelIndex())).toString();
    QLabel *mtntUSD_label = new QLabel(mtntUSD);
    form2->addRow("MONTANT EN USD:",mtntUSD_label);

    QString taux = modelInvestissement->data(modelInvestissement->index(idx.row(),7,QModelIndex())).toString();
    QLabel *taux_label = new QLabel(taux);
    form2->addRow("TAUX (HTG):",taux_label);

    QString mtnt = modelInvestissement->data(modelInvestissement->index(idx.row(),3,QModelIndex())).toString();
    QLabel *mtnt_label = new QLabel(mtnt);
    form2->addRow("MONTANT D'INVESTISSEMENT (HTG):",mtnt_label);

    QString period = modelInvestissement->data(modelInvestissement->index(idx.row(),4,QModelIndex())).toString();
    QLabel *period_label = new QLabel(period);
    form2->addRow("PERIODE DE VERSEMENT:",period_label);

    model_listVersement = new QSqlTableModel;
    model_listVersement->setTable("versementInvestment");
    model_listVersement->select();

    tableVersement = new QTableView;
    tableVersement->setModel(model_listVersement);
    tableVersement->setMinimumWidth(650);
    tableVersement->setMinimumHeight(300);
    tableVersement->setAlternatingRowColors(true);
    tableVersement->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVersement->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableVersement->setColumnWidth(2,200);
    tableVersement->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableVersement,1,0,1,2);

    model_listVersement->setFilter("ID_PARENT = "+id);


    QFormLayout *formResultat = new QFormLayout;
    grid->addLayout(formResultat,2,0);

    mtntInvestis = new QLabel(mtnt);
    formResultat->addRow("Montant d'investissement:",mtntInvestis);

    totalVersement = new QLabel("---");
    formResultat->addRow("Total des versements",totalVersement);

    balanceVersement = new QLabel("---");
    formResultat->addRow("Balance",balanceVersement);

    beneficeVersement = new QLabel("---");
    beneficeVersement->setFont(QFont("Datus",12,QFont::Bold,false));
    beneficeVersement->setStyleSheet("color:blue;");
    formResultat->addRow(QString::fromUtf8("Bénéfice"),beneficeVersement);

    QPushButton *ajoutVersementBtn = new QPushButton("Ajouter un nouveau versement");
    grid->addWidget(ajoutVersementBtn,2,1);

    diag->show();

    connect(ajoutVersementBtn,SIGNAL(clicked()),this,SLOT(showAddVersementDialog()));
    connect(tableVersement,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showPopMenuTableVersement(QPoint)));

    actualiseDataVersement();
}

void Fen_Caisse::showPopMenuTableVersement(QPoint p)
{
    Q_UNUSED(p);

    QMenu contextMenu(tr("Context Menu"),tableVersement);
    QAction action("effacer le versement",this);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerDataTableVersement()));
    contextMenu.addAction(&action);
    contextMenu.exec(QCursor::pos());
}


void Fen_Caisse::effacerDataTableVersement()
{
    int row = tableVersement->selectionModel()->currentIndex().row();
    QString id_vers = model_listVersement->data(model_listVersement->index(row,0),Qt::EditRole).toString();

    querry.prepare("DELETE FROM versementInvestment WHERE ID = "+id_vers+" ");
    if(querry.exec()){
        qDebug()<<"Yes the versement was deleted";
        model_listVersement->removeRow(row,QModelIndex());
        model_listVersement->select();
        actualiseDataVersement();
        actualiseData();
    }
    else
        qDebug()<<"No the versement was not deleted:"<<querry.lastError();
}

void Fen_Caisse::showAddVersementDialog()
{
    diagAddVersement = new QDialog;
    diagAddVersement->setWindowTitle("Ajouter un versement");
    diagAddVersement->setModal(true);

    QFormLayout *form = new QFormLayout;
    diagAddVersement->setLayout(form);

    idParent_spinBox = new QSpinBox;
    idParent_spinBox->setMaximum(999999);
    idParent_spinBox->setValue(idInvestissement_label->text().toInt());
    idParent_spinBox->setEnabled(false);
    form->addRow("ID PARENT:",idParent_spinBox);


    dateEdit_versement = new QDateEdit;
    dateEdit_versement->setCalendarPopup(true);
    dateEdit_versement->setDate(QDate::currentDate());
    form->addRow("DATE:",dateEdit_versement);

    descriptInvest_edit = new QLineEdit;
    descriptInvest_edit->setText("Versement");
    form->addRow("DESCRIPTION:",descriptInvest_edit);

    mtntVersement = new QDoubleSpinBox;
    mtntVersement->setMaximum(99999999.99);
    form->addRow("MONTANT DU VERSEMENT:",mtntVersement);

    QPushButton *validerBtn = new QPushButton("Cliquer ici");
    form->addRow("Valider",validerBtn);

    diagAddVersement->show();

    connect(validerBtn,SIGNAL(clicked()),this,SLOT(onClickedAjoutVersementBtn()));
}

void Fen_Caisse::onClickedAjoutVersementBtn()
{
    querry.prepare("INSERT INTO versementInvestment (DATE,DESCRIPTION,MONTANT,ID_PARENT)"
                   "VALUES (:date,:description,:montant,:id_parent)");

    querry.bindValue(":date",dateEdit_versement->date());
    querry.bindValue(":description",descriptInvest_edit->text());
    querry.bindValue(":montant",mtntVersement->value());
    querry.bindValue(":id_parent",idParent_spinBox->value());

    if(querry.exec()){
        diagAddVersement->close();
        model_listVersement->select();
        actualiseDataVersement();
        actualiseData();
    }else
        qDebug()<<querry.lastError();
}


void Fen_Caisse::actualiseDataVersement()
{
    int row = tableInvestissement->selectionModel()->currentIndex().row();

    QString id_vers = modelInvestissement->data(modelInvestissement->index(row,0),Qt::EditRole).toString();
    double mtntInvest = modelInvestissement->data(modelInvestissement->index(row,3),Qt::EditRole).toDouble();
    double mtntVers = 0,balance = 0;


    querry.prepare("SELECT * FROM versementInvestment WHERE ID_PARENT = "+id_vers);

    if(querry.exec()){
        while(querry.next()){
            mtntVers += querry.value(3).toDouble();
        }
    }else
        qDebug()<<querry.lastError();

    balance = (mtntInvest-mtntVers>=0) ? mtntInvest-mtntVers : 0;

    totalVersement->setText(QString::number(mtntVers));
    balanceVersement->setText(QString::number(balance));

    if(balance<=0)
        beneficeVersement->setText(QString::number((mtntInvest-mtntVers)*-1));
    else
        beneficeVersement->setText("---");

}




















