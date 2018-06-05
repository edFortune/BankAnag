#include "fen_caisse.h"



void Fen_Caisse::set_EchangeUSDPage(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    model_echangeUSD = new QSqlTableModel;
    model_echangeUSD->setTable("rapportEchangeUSDTable");
    model_echangeUSD->select();

    delegateModelUSD = new fen_caisse_delegate2;

    tableEchangeUSD = new QTableView;
    tableEchangeUSD->setModel(model_echangeUSD);
    tableEchangeUSD->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableEchangeUSD->setAlternatingRowColors(true);
    tableEchangeUSD->setItemDelegate(delegateModelUSD);
    tableEchangeUSD->setContextMenuPolicy(Qt::CustomContextMenu);
    grid->addWidget(tableEchangeUSD,0,0,5,1);

    QPushButton *addEchangeDialogBte = new QPushButton(QString::fromUtf8("Ajouter un échange"));
    addEchangeDialogBte->setStyleSheet("background-color:#344956;color:white;");
    addEchangeDialogBte->setMinimumHeight(50);
    grid->addWidget(addEchangeDialogBte,0,1);

    //-------------------------------------------------

    QVBoxLayout *vboxhtg = new QVBoxLayout;
    vboxhtg->addSpacing(0);
    vboxhtg->setMargin(0);
    grid->addLayout(vboxhtg,1,1);

    QLabel *labTitle = new QLabel(QString::fromUtf8("Résultat en gourde"));
    labTitle->setMargin(15);
    labTitle->setFont(QFont("Datus",12,QFont::Bold,false));
    labTitle->setStyleSheet("background-color:#6A5ACD;color:white;");
    labTitle->setMinimumWidth(250);
    vboxhtg->addWidget(labTitle);

    QFormLayout *formResult_htg = new QFormLayout;
    formResult_htg->setSpacing(10);
    vboxhtg->addLayout(formResult_htg);

    total_1_htg = new QLabel("---");
    total_1_htg->setFont(QFont("",8,QFont::Bold,false));
    total_1_htg->setStyleSheet("color:blue;");
    formResult_htg->addRow("Total d'achat (HTG): ",total_1_htg);

    total_2_htg = new QLabel("---");
    total_2_htg->setFont(QFont("",8,QFont::Bold,false));
    total_2_htg->setStyleSheet("color:blue;");
    formResult_htg->addRow("Total de vente (HTG): ",total_2_htg);

    totalDiff_htg = new QLabel("---");
    totalDiff_htg->setFont(QFont("",8,QFont::Bold,false));
    totalDiff_htg->setStyleSheet("color:blue;");
    formResult_htg->addRow(QString::fromUtf8("Différence (HTG): "),totalDiff_htg);

    //-------------------------------------------------------------------

    QVBoxLayout *vboxhtd = new QVBoxLayout;
    vboxhtd->addSpacing(0);
    vboxhtd->setMargin(0);
    grid->addLayout(vboxhtd,2,1);

    QLabel *labTitle2 = new QLabel(QString::fromUtf8("Résultat en dollar"));
    labTitle2->setMargin(15);
    labTitle2->setFont(QFont("Datus",12,QFont::Bold,false));
    labTitle2->setStyleSheet("background-color:#6A5ACD;color:white;");
    vboxhtd->addWidget(labTitle2);

    QFormLayout *formResult = new QFormLayout;
    formResult->setSpacing(10);
    vboxhtd->addLayout(formResult);

    totalMontantUSD = new QLabel("---");
    formResult->addRow("Total du Montant (USD): ",totalMontantUSD);

    total_1 = new QLabel("---");
    formResult->addRow("Total d'achat: ",total_1);

    total_2 = new QLabel("---");
    formResult->addRow("Total de vente: ",total_2);

    totalDiff = new QLabel("---");
    formResult->addRow(QString::fromUtf8("Différence: "),totalDiff);

    //--------------------------------------------------------------------

    QPushButton *b_restorTotalUSD = new QPushButton("Restorer les totaux");
    b_restorTotalUSD->setStyleSheet("background-color:#344956;color:white;");
    b_restorTotalUSD->setMinimumHeight(50);
    //grid->addWidget(b_restorTotalUSD,3,1);

    QGroupBox *grpMoy = new QGroupBox("Moyenne des taux");
    grid->addWidget(grpMoy,4,1);

    QFormLayout *formMoy = new QFormLayout;
    formMoy->setSpacing(10);
    grpMoy->setLayout(formMoy);

    tauxAchat_moy = new QLabel("---");
    formMoy->addRow("Taux d'achat: ",tauxAchat_moy);

    tauxVente_moy = new QLabel("---");
    formMoy->addRow("Taux de vente: ",tauxVente_moy);

    set_totalGeneralUSD();

    connect(addEchangeDialogBte,SIGNAL(clicked()),this,SLOT(on_click_addEchangeDialog()));
    connect(tableEchangeUSD,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenuEchangeUSD(QPoint)));
    connect(b_restorTotalUSD,SIGNAL(clicked()),this,SLOT(on_click_restorUSD()));
    connect(model_echangeUSD,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(showDataUSDChange(QModelIndex,QModelIndex)));
}
void Fen_Caisse::showDataUSDChange(QModelIndex i1, QModelIndex i2)
{
    set_totalGeneralUSD();

    if(i1.row()==-1 || i2.row()==-1)
        return;
}

void Fen_Caisse::on_click_restorUSD()
{
    set_totalGeneralUSD();
}

void Fen_Caisse::showContextMenuEchangeUSD(QPoint p)
{
    Q_UNUSED(p);

    QMenu contextMenu(tr("Menu"),this);
    QAction action(tr("Remove row"),this);

    contextMenu.addAction(&action);
    connect(&action,SIGNAL(triggered()),this,SLOT(removeRowEchangeUSD()));
    contextMenu.exec(QCursor::pos());
}

void Fen_Caisse::removeRowEchangeUSD()
{
    int row = tableEchangeUSD->selectionModel()->currentIndex().row();
    model_echangeUSD->removeRow(row,QModelIndex());
    set_totalGeneralUSD();
}

void Fen_Caisse::on_click_addEchangeDialog()
{
    diag = new QDialog;
    diag->setModal(true);

    QFormLayout *form = new QFormLayout;
    diag->setLayout(form);

    dateEchange = new QDateEdit;
    dateEchange->setCalendarPopup(true);
    dateEchange->setDate(QDate::currentDate());
    dateEchange->setDisplayFormat("dd/MM/yyyy");
    form->addRow("Date: ",dateEchange);

    montantEchange = new QDoubleSpinBox;
    montantEchange->setMinimum(0);
    montantEchange->setMaximum(100000);
    form->addRow("Montant: ",montantEchange);

    tauxAchat = new QDoubleSpinBox;
    form->addRow("Taux d'achat: ",tauxAchat);
    tauxVente = new QDoubleSpinBox;
    form->addRow("Taux de vente: ",tauxVente);

    QPushButton *soumettreBte = new QPushButton("Soumettre");
    form->addRow("Soumettre: ",soumettreBte);

    diag->show();

    connect(soumettreBte,SIGNAL(clicked()),this,SLOT(add_echangeUSD()));

}

void Fen_Caisse::add_echangeUSD()
{
    double diff = (montantEchange->value()*tauxVente->value()) - (montantEchange->value()*tauxAchat->value());
    querry.prepare("INSERT INTO rapportEchangeUSDTable (DATE,MONTANT,TAUX_ACHAT,TOTAL_1,TAUX_VENTE,TOTAL_2,DIFFERENCE) VALUES"
                   "('"+dateEchange->date().toString("dd/MM/yyyy")+"',"
                   "  "+montantEchange->text()+", "
                   "  "+tauxAchat->text()+", "
                   "  "+QString::number(montantEchange->value()*tauxAchat->value())+", "
                   "  "+tauxVente->text()+", "
                   "  "+QString::number(montantEchange->value()*tauxVente->value())+", "
                   "  "+QString::number(diff)+") ");

    bool c = querry.exec();
    if(c){
        model_echangeUSD->select();
        diag->close();
        querry.finish();
        set_totalGeneralUSD();
        QMessageBox::about(this,"Enregistrement","Enregistrer avec succes!!!");
    }else
        qDebug()<<querry.lastError();
}

void Fen_Caisse::set_totalGeneralUSD()
{
    double totMtnt = 0, totAchat = 0, totVente = 0, totDiff = 0;
    double moyTA = 0, moyTV = 0;



    querry.prepare("SELECT * FROM rapportEchangeUSDTable");

    bool c = querry.exec();

    if(c){
        while(querry.next())
        {
            totMtnt += querry.value(2).toDouble();
            totAchat += querry.value(4).toDouble();
            totVente += querry.value(6).toDouble();
            totDiff += querry.value(7).toDouble();

            moyTA += querry.value(3).toDouble();
            moyTV += querry.value(5).toDouble();
        }

        totalMontantUSD->setText(QLocale(QLocale::English).toString((int)totMtnt));
        total_1->setText(QLocale(QLocale::English).toString((int)totAchat));
        total_2->setText(QLocale(QLocale::English).toString((int)totVente));
        totalDiff->setText(QLocale(QLocale::English).toString((int)totVente-totAchat));


        total_1_htg->setText(QLocale(QLocale::English).toString((int)totAchat*5));
        total_2_htg->setText(QLocale(QLocale::English).toString((int)totVente*5));
        totalDiff_htg->setText(QLocale(QLocale::English).toString((int)totDiff*5));

        if(model_echangeUSD->rowCount(QModelIndex())<=0){
            tauxAchat_moy->setText(QString::number(moyTA/1));
            tauxVente_moy->setText(QString::number(moyTV/1));
        }else{
            tauxAchat_moy->setText(QString::number(moyTA/model_echangeUSD->rowCount(QModelIndex())));
            tauxVente_moy->setText(QString::number(moyTV/model_echangeUSD->rowCount(QModelIndex())));

            qDebug()<<model_echangeUSD->rowCount(QModelIndex());
        }

    }
}
