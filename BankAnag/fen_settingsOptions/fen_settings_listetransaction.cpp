#include "fen_settings.h"


QWidget* Fen_Settings::add_SettingsListeTransaction()
{
    QWidget *widParent = new QWidget;

    QVBoxLayout *vbox = new QVBoxLayout;
    widParent->setLayout(vbox);


    QTabWidget *tabParent = new QTabWidget;
    vbox->addWidget(tabParent);


    QWidget *widTransfertTransac = new QWidget;
    setPageTransfertTransaction(widTransfertTransac);
    tabParent->addTab(widTransfertTransac,"Transfert de transaction (Carnet Perdu)");

    QWidget *widModifierTransac = new QWidget;
    setPageModificationTransaction(widModifierTransac);
    tabParent->addTab(widModifierTransac ,"Modication d'une transaction");

    QWidget *widChangementGroup = new QWidget;
    setPageChangementGroup(widChangementGroup);
    tabParent->addTab(widChangementGroup ,"Changement de groupe");

    return widParent;

}


//--------------------------------------------Page Transfert Transaction--------------------------------------------
void Fen_Settings ::setPageTransfertTransaction(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    QLabel *lab1 = new QLabel("Ancien code:");
    grid->addWidget(lab1,0,0);

    acEdit = new QLineEdit;
    grid->addWidget(acEdit,0,1);

    modalAC = new QSqlTableModel(this);
    modalAC->setTable("transaction_table_6");
    //modalAC->select();

    QTableView *acTab = new QTableView;
    acTab->setModel(modalAC);
    acTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    acTab->setSelectionBehavior(QAbstractItemView::SelectRows);
    grid->addWidget(acTab,1,0,1,3);

    //----------------

    QLabel *lab2 = new QLabel("Nouveau code:");
    grid->addWidget(lab2,2,0);

    ncEdit = new QLineEdit;
    grid->addWidget(ncEdit,2,1);

    modalNC = new QSqlTableModel(this);
    modalNC->setTable("transaction_table_6");
    //modalNC->select();

    QTableView *ncTab = new QTableView;
    ncTab->setModel(modalNC);
    ncTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ncTab->setSelectionBehavior(QAbstractItemView::SelectRows);
    grid->addWidget(ncTab,3,0,1,3);

    QLabel *info = new QLabel(this);
    info->setText("Transferer les transactions de l'ancien compte dans le nouveau compte");
    grid->addWidget(info,4,0,1,2);

    QPushButton *b_transfert = new QPushButton("Transfert");
    grid->addWidget(b_transfert,4,2,1,1);

    connect(acEdit,SIGNAL(textEdited(QString)),this,SLOT(searchAcCode(QString)));
    connect(ncEdit,SIGNAL(textEdited(QString)),this,SLOT(searchNcCode(QString)));
    connect(b_transfert,SIGNAL(clicked()),this,SLOT(on_press_bTransfertTransaction()));
}



void Fen_Settings ::searchAcCode(QString code)
{
    modalAC->setFilter("ID_CLIENT = "+code);
    modalAC->select();
}


void Fen_Settings ::on_press_bTransfertTransaction()
{
    QList<QString> list;
    querry.prepare("SELECT ID FROM transaction_table_6 WHERE ID_CLIENT = "+acEdit->text());
    bool c = querry.exec();
    if(c)
    {
        while(querry.next())
        {
            list.append(querry.value(0).toString());
        }
    }
    querry.finish();
    qDebug()<<list.count();

    int cpt=0;
    bool b=0;

    for(int i=0; i<list.count();i++)
    {
        querry.prepare("UPDATE transaction_table_6 SET ID_CLIENT ="+ncEdit->text()+"  WHERE ID = "+list.at(i));
        b=querry.exec();
        if(b)
            cpt++;
    }
    if(cpt==list.count())
        QMessageBox::about(this,"Succes","Transfert reussit.");

    qDebug()<<cpt;
}

void Fen_Settings ::searchNcCode(QString code)
{
    modalNC->setFilter("ID_CLIENT = "+code);
    modalNC->select();
}

//--------------------------------------------PageModificationTransaction--------------------------------------------
void Fen_Settings ::setPageModificationTransaction(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    QFormLayout *form = new QFormLayout;
    grid->addLayout(form,0,0);

    QLineEdit *Id_client = new QLineEdit;
    Id_client->setPlaceholderText("Entrer l'ID du client ici");
    form->addRow("ID CLIENT:",Id_client);

    idTransac = new QLineEdit;
    idTransac->setEnabled(false);
    form->addRow("ID Transaction",idTransac);

    dateTransac = new QDateEdit;
    dateTransac->setCalendarPopup(true);
    dateTransac->setDisplayFormat("dd/MM/yyyy");
    form->addRow("DATE:",dateTransac);

    timeTransac = new QTimeEdit;
    timeTransac->setDisplayFormat("hh:mm AP");
    form->addRow("HEURE:",timeTransac);

    QPushButton *soumettre = new QPushButton("Cliquer ici");
    form->addRow("Soumettre:",soumettre);

    modelModifierTransac = new QSqlTableModel(this);
    modelModifierTransac->setTable("transaction_table_6");
    //modelModifierTransac->select();


    tableModifierTransac = new QTableView;
    tableModifierTransac->setModel(modelModifierTransac);
    tableModifierTransac->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableModifierTransac->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableModifierTransac->setAlternatingRowColors(true);
    grid->addWidget(tableModifierTransac,1,0);

    connect(Id_client,SIGNAL(textEdited(QString)),this,SLOT(text_IdClient_Change(QString)));
    QObject::connect(tableModifierTransac,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getTransactionAmodifier()));
    connect(soumettre,SIGNAL(clicked()),this,SLOT(changeDataTransaction()));

}


void Fen_Settings ::text_IdClient_Change(QString text)
{
    modelModifierTransac->setFilter("ID_CLIENT = "+text);
    modelModifierTransac->select();
}


void Fen_Settings ::getTransactionAmodifier()
{

    int row = tableModifierTransac->selectionModel()->currentIndex().row();
    QString id = modelModifierTransac->index(row,0).data().toString();
    QString date = modelModifierTransac->index(row,1).data().toString();
    QString heure = modelModifierTransac->index(row,2).data().toString();

    idTransac->setText(id);
    dateTransac->setDate(QDate::fromString(date,"dd/MM/yyyy"));
    timeTransac->setTime(QTime::fromString(heure,"hh:mm AP"));

}


void Fen_Settings ::changeDataTransaction()
{
    querry.prepare("UPDATE transaction_table_6 SET DATE ='"+dateTransac->date().toString("dd/MM/yyyy")+"',"
                   "HEURE ='"+timeTransac->time().toString("hh:mm AP")+"' WHERE ID = "+idTransac->text());
    bool c = querry.exec();
    if(c){
        QMessageBox::about(this,"Succes","Modification reussite");
    }
    else
        QMessageBox::warning(this,"Erreur","Modification echoue");
}



//--------------------------------------------Page Changement Groupe-------------------------------------------------
void Fen_Settings::setPageChangementGroup(QWidget *wid)
{
    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    QLineEdit *lineCode_edit = new QLineEdit;
    grid->addWidget(lineCode_edit,0,0);

    QFormLayout *form_layout = new QFormLayout;
    grid->addLayout(form_layout,1,0);

    QTableView *tableAncientTransaction = new QTableView;
    grid->addWidget(tableAncientTransaction,0,1,2,1);

    QLineEdit *lineCodeChange_edit = new QLineEdit;
    grid->addWidget(lineCodeChange_edit,2,0);

    QFormLayout *form_layout2 = new QFormLayout;
    grid->addLayout(form_layout2,3,0);

    QTableView *tableNouveauTransaction = new QTableView;
    grid->addWidget(tableNouveauTransaction,2,1,2,1);



}


