#include "fen_depense.h"

Fen_Depense::Fen_Depense(QWidget *parent) :
    QWidget(parent)
{

}


Fen_Depense::Fen_Depense(QSqlQuery q)
{
    querry = q;

    LayoutLister = new QGridLayout;
    this->setLayout(LayoutLister);


    QTabWidget *tabParent = new QTabWidget;
    LayoutLister->addWidget(tabParent,2,1,3,6);
    indexTab = 0;


    model = new QSqlTableModel;
    model->setTable(QString("depenseTable"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    table = new QTreeView;
    table->setWordWrap(true);
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->setMinimumHeight(390);
    table->setColumnWidth(2,800);

    tabParent->addTab(table,QString::fromUtf8("Depense à payer"));


    model_2 = new QSqlTableModel;
    model_2->setTable(QString("depensePayerTable"));
    model_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_2->select();

    table_2 = new QTreeView;
    table_2->setWordWrap(true);
    table_2->setModel(model_2);
    table_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_2->setAlternatingRowColors(true);
    //table_2->setMinimumHeight(450);
    table_2->setColumnWidth(2,800);

    tabParent->addTab(table_2,QString::fromUtf8("Depense payé"));


    bimprimer = new QPushButton;
    bimprimer->setToolTip("Imprimer");
    bimprimer->setFixedSize(40,40);
    bimprimer->setIcon(QIcon("Image/printIcon.png"));
    bimprimer->setIconSize(QSize(30,30));
    LayoutLister->addWidget(bimprimer,2,0);

    bsupprimer = new QPushButton;
    bsupprimer->setToolTip("Supprimer");
    bsupprimer->setFixedSize(40,40);
    bsupprimer->setIcon(QIcon("Image/deleteIcon.png"));
    bsupprimer->setIconSize(QSize(30,30));
    LayoutLister->addWidget(bsupprimer,3,0);

    dater = new QDateEdit;
    dater->setCalendarPopup(true);
    dater->setDisplayFormat("dd/MM/yyyy");
    dater->setDate(QDate::currentDate());
    LayoutLister->addWidget(dater,1,1,1,1);

    descrip = new QLineEdit;
    descrip->setPlaceholderText("Description");
    LayoutLister->addWidget(descrip,1,2,1,1);

    mtnt = new QDoubleSpinBox;
    mtnt->setMinimum(1);
    mtnt->setMaximum(50000);
    mtnt->setMinimumWidth(200);

    LayoutLister->addWidget(mtnt,1,3,1,1);

    QPushButton *valid = new QPushButton("Valider");
    LayoutLister->addWidget(valid,1,4);


    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(5);
    hLayout->setMargin(0);
    LayoutLister->addLayout(hLayout,5,0,1,5);

    totaldep = new QLabel("---");
    hLayout->addWidget(add_styleWidget("A payer ",totaldep));

    totaldepPayer = new QLabel("---");
    hLayout->addWidget(add_styleWidget("Payer ",totaldepPayer));

    totalGeneral = new QLabel("---");
    hLayout->addWidget(add_styleWidget("Total ",totalGeneral));

    LayoutLister->setRowStretch(1,0);

    totaliserDepense();

    QObject::connect(valid,SIGNAL(clicked()),this,SLOT(validerDepense()));
    QObject::connect(bsupprimer,SIGNAL(clicked()),this,SLOT(effacerDepense()));
    QObject::connect(tabParent,SIGNAL(currentChanged(int)),this,SLOT(on_click_changeTab(int)));
}


QWidget* Fen_Depense::add_styleWidget(QString titre,QLabel * data)
{
    QWidget *wid = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    wid->setLayout(v);


    QLabel *lab_titre = new QLabel(titre);
    lab_titre->setStyleSheet("background-color:#344956;color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    v->addWidget(lab_titre);

    QLabel *lab_data = data;
    lab_data->setStyleSheet("background-color:#DB532B ;color:white;");
    lab_data->setAlignment(Qt::AlignCenter);
    lab_data->setFont(QFont("",20,20,false));
    lab_data->setMargin(5);
    v->addWidget(lab_data);

    return wid;
}



void Fen_Depense::on_click_changeTab(int i)
{
    indexTab = i;
    qDebug()<<i;
}


void Fen_Depense::validerDepense()
{
    if(descrip->text().isEmpty())
    {
        QMessageBox::warning(this,"Erreur","Veuillez preciser la status du depense.");
        return;
    }else{
        if(indexTab==0){
                querry.prepare("INSERT INTO depenseTable (DATE,DESCRIPTION,MONTANT)"
                               "VALUES (:DATE,:DESCRIPTION,:MONTANT)");

                querry.bindValue(":DATE",dater->text());
                querry.bindValue(":DESCRIPTION",descrip->text());
                querry.bindValue(":MONTANT",mtnt->text());

                bool c = querry.exec();

                if(c){

                    qDebug()<<"Insert depense";
                    model->select();
                    totaliserDepense();
                    descrip->clear();
                    mtnt->clear();
                }
                else
                    qDebug()<<querry.lastError();
        }else if(indexTab==1){

            querry.prepare("INSERT INTO depensePayerTable (DATE,DESCRIPTION,MONTANT)"
                           "VALUES (:DATE,:DESCRIPTION,:MONTANT)");

            querry.bindValue(":DATE",dater->text());
            querry.bindValue(":DESCRIPTION",descrip->text());
            querry.bindValue(":MONTANT",mtnt->text());

            bool c = querry.exec();

            if(c){

                qDebug()<<"Insert depense";
                model_2->select();
                totaliserDepense();
                descrip->clear();
                mtnt->clear();
            }
            else
                qDebug()<<querry.lastError();
        }
    }

}



void Fen_Depense::totaliserDepense()
{
    int depenseApayer = 0, depensePayer = 0;

    querry.exec("SELECT SUM(MONTANT) FROM depenseTable");
    if(querry.first())
        depenseApayer = querry.value(0).toInt();

    totaldep->setText(QLocale(QLocale::English).toString(depenseApayer));

    querry.exec("SELECT SUM(MONTANT) FROM depensePayerTable");
    if(querry.first())
        depensePayer = querry.value(0).toInt();

    totaldepPayer->setText(QLocale(QLocale::English).toString(depensePayer));
    totalGeneral->setText(QLocale(QLocale::English).toString(depenseApayer + depensePayer));
}



void Fen_Depense::effacerDepense()
{
    int row = table->selectionModel()->currentIndex().row();
    QString id = model->index(row,0).data().toString();

    int row2 = table_2->selectionModel()->currentIndex().row();
    QString id2 = model_2->index(row2,0).data().toString();

    if(id=="" && id2=="")
    {
        QMessageBox::warning(this,"Erreur","Selectionnez un element dans le tableau pour le supprimer.");
        return;
    }

    QMessageBox::StandardButton resBtnYes = QMessageBox::question( this,"Close",tr("Voulez-vous vraiment supprimer ce donnee?\n"),
             QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);

    if(resBtnYes == QMessageBox::Yes)
    {
        if(indexTab==0){
            if(!querry.exec("DELETE FROM depenseTable WHERE ID = "+id+"  "))
                qDebug()<<"pas effacer";
            else{
                    qDebug()<<"effacer";
                    model->select();
                    totaliserDepense();
                }
        }else if(indexTab==1){
            if(!querry.exec("DELETE FROM depensePayerTable WHERE ID = "+id2+"  "))
                qDebug()<<"pas effacer";
            else{
                    qDebug()<<"effacer";
                    model_2->select();
                    totaliserDepense();
                }
        }
    }

}







