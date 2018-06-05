#include "fen_caisse.h"


void Fen_Caisse::setrapportCaissePage(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    delegateModelRapport = new Fen_Caisse_Delegate;

    modelRapport = new QSqlTableModel;
    modelRapport->setTable("rapportCaisseTable_1");
    modelRapport->select();

    tableRapport = new QTableView;
    tableRapport->setModel(modelRapport);
    tableRapport->setItemDelegate(delegateModelRapport);
    tableRapport->setContextMenuPolicy(Qt::CustomContextMenu);
    tableRapport->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableRapport->setAlternatingRowColors(true);
    grid->addWidget(tableRapport,0,0,6,1);

    QGroupBox *group1 = new QGroupBox;
    grid->addWidget(group1,0,1);

    QFormLayout *form1 = new QFormLayout;
    group1->setLayout(form1);

    date = new QDateEdit;
    date->setCalendarPopup(true);
    date->setDate(QDate::currentDate());
    date->setDisplayFormat("dd/MM/yyyy");
    form1->addRow("Date:",date);

//    QPushButton *voirBte = new QPushButton("Cliquer ici");
//    form1->addRow("Chercher: ",voirBte);

    QGroupBox *group2 = new QGroupBox("Resultat");
    grid->addWidget(group2,1,1);

    QFormLayout *form2 = new QFormLayout;
    group2->setLayout(form2);

    dateLabel = new QLabel("---");
    form2->addRow("Date: ",dateLabel);

    depotLabel = new QLabel("---");
    form2->addRow("Depot: ",depotLabel);

    retraitLabel = new QLabel("---");
    form2->addRow("Retrait: ",retraitLabel);

    balanceLabel = new QLabel("---");
    form2->addRow("Balance: ",balanceLabel);


    QPushButton *ajouBte = new QPushButton("Cliquer ici");
    form2->addRow("Ajouter:",ajouBte);

    QGroupBox *group3 = new QGroupBox("Rapport");
    grid->addWidget(group3,2,1,2,1);

    QFormLayout *form3 = new QFormLayout;
    form3->setSpacing(10);
    group3->setLayout(form3);

    totDepot = new QLabel("---");
    form3->addRow("Total des depots: ",totDepot);

    totRetrait = new QLabel("---");
    form3->addRow("Total des retraits: ",totRetrait);

    diff = new QLabel("---");
    form3->addRow("Difference: ",diff);

    totgeneral = new QLabel("--- HTG");
    totgeneral->setFont(QFont("",15,15,false));
    totgeneral->setAlignment(Qt::AlignCenter);
    totgeneral->setStyleSheet("background-color:#344956;color:white;");
    grid->setAlignment(totgeneral,Qt::AlignCenter);
    grid->addWidget(totgeneral,4,1);

    QPushButton *restoreBte = new QPushButton("Restorer");
    grid->addWidget(restoreBte,5,1);

    set_totalGeneral();

    //connect(voirBte,SIGNAL(clicked()),this,SLOT(on_clicke_chercher()));
    connect(ajouBte,SIGNAL(clicked()),this,SLOT(addDataRapportCaisseTable()));
    connect(date,SIGNAL(dateChanged(QDate)),this,SLOT(on_click_CalenderDate(QDate)));
    connect(restoreBte,SIGNAL(clicked()),this,SLOT(on_click_Restore()));
    connect(tableRapport,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenu(QPoint)));

}

void Fen_Caisse::showContextMenu(QPoint p)
{
    Q_UNUSED(p);

    QMenu contextMenu(tr("Context Menu"),tableRapport);

    QAction action("Remove row",this);

    connect(&action,SIGNAL(triggered()),this,SLOT(effacerDataRapport()));
    contextMenu.addAction(&action);
    contextMenu.exec(QCursor::pos());
}

void Fen_Caisse::effacerDataRapport()
{
    int row = tableRapport->selectionModel()->currentIndex().row();
    modelRapport->removeRow(row,QModelIndex());

    set_totalGeneral();
}

void Fen_Caisse::on_click_CalenderDate(QDate d)
{
    isReqExecute = false;
    int dep =0,ret=0;
    querry.prepare("SELECT * FROM transaction_table_6 WHERE DATE = '"+d.toString("dd/MM/yyyy")+"'");
    bool c = querry.exec();
    if(c){
        while(querry.next())
        {
             dep +=querry.value(5).toInt();
             ret +=querry.value(4).toInt();
        }

        dateLabel->setText(d.toString("dd/MM/yyyy"));
        depotLabel->setText(QString::number(dep));
        retraitLabel->setText(QString::number(ret));
        balanceLabel->setText(QString::number(dep-ret));
        isReqExecute = true;
    }else
        qDebug()<<querry.lastError();
}

void Fen_Caisse::on_clicke_chercher()
{
    isReqExecute = false;
    int dep =0,ret=0;
    querry.prepare("SELECT * FROM transaction_table_6 WHERE DATE = '"+date->date().toString("dd/MM/yyyy")+"'");
    bool c = querry.exec();
    if(c){
        while(querry.next())
        {
             dep +=querry.value(5).toInt();
             ret +=querry.value(4).toInt();
        }

        dateLabel->setText(date->date().toString("dd/MM/yyyy"));
        depotLabel->setText(QString::number(dep));
        retraitLabel->setText(QString::number(ret));
        balanceLabel->setText(QString::number(dep-ret));
        isReqExecute = true;
    }else
        qDebug()<<querry.lastError();

}

void Fen_Caisse::on_click_Restore()
{
    set_totalGeneral();
}

void Fen_Caisse::addDataRapportCaisseTable()
{
    if(isReqExecute)
    {
        querry.prepare("INSERT INTO rapportCaisseTable_1 (DATE,DEPOTS,RETRAITS,BALANCE,TOTAL) VALUES"
                       "('"+dateLabel->text()+"',"
                       " "+depotLabel->text()+","
                       " "+retraitLabel->text()+","
                       " "+balanceLabel->text()+","
                       " "+balanceLabel->text()+") ");

        bool c= querry.exec();
        if(c)
        {
            modelRapport->select();
            QMessageBox::about(this,"Enregistrement","Enregistrer avec succes");
            tableRapport->scrollToBottom();
            set_totalGeneral();
            isReqExecute = false;
        }else
            qDebug()<<querry.lastError();
    }
}

void Fen_Caisse::set_FenWidget(QMdiSubWindow *f)
{
    fen_caisse = f;
}

void Fen_Caisse::closeFen()
{
    fen_caisse->close();
}

void Fen_Caisse::set_totalGeneral()
{
    double dep=0,ret=0,dif=0,som = 0;
    querry.prepare("SELECT * FROM rapportCaisseTable_1");
    bool c = querry.exec();
    if(c)
    {
        while(querry.next())
        {
            dep +=querry.value(2).toDouble();
            ret +=querry.value(3).toDouble();
            dif +=querry.value(5).toDouble();
            som +=querry.value(6).toDouble();
        }

        totDepot->setText(QLocale(QLocale::English).toString(dep)+" HTG");
        totRetrait->setText(QLocale(QLocale::English).toString(ret)+" HTG");
        diff->setText(QLocale(QLocale::English).toString(dif)+" HTG");
        totgeneral->setText(QLocale(QLocale::English).toString(som)+" HTG");

    }else
        querry.lastError();
}
