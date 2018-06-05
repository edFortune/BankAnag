#include "fen_caisse.h"
//#include "widgetStyleHeader.h"


void Fen_Caisse::setRapportAutreProduitPage(QWidget *w)
{
    QGridLayout *grid = new QGridLayout;
    w->setLayout(grid);

    dateProduit = new QDateEdit;
    dateProduit->setCalendarPopup(true);
    dateProduit->setDate(QDate::currentDate());
    grid->addWidget(dateProduit,0,0);

    autreProduit_edit = new QLineEdit;
    autreProduit_edit->setPlaceholderText("Descritpion du produit");
    grid->addWidget(autreProduit_edit,0,1);

    montantAutreProduit_dspin = new QDoubleSpinBox;
    montantAutreProduit_dspin->setMaximum(100000);
    grid->addWidget(montantAutreProduit_dspin,0,2);

    modelAutreProduit = new QSqlTableModel;
    modelAutreProduit->setTable("AutreProduits");
    modelAutreProduit->setHeaderData(0,Qt::Horizontal,"ID");
    modelAutreProduit->setHeaderData(1,Qt::Horizontal,"DATE");
    modelAutreProduit->setHeaderData(2,Qt::Horizontal,"DESCRIPTION D'AUTRES PRODUITS");
    modelAutreProduit->setHeaderData(3,Qt::Horizontal,"MONTANT");
    modelAutreProduit->select();

    tableAutreProduit = new QTableView;
    tableAutreProduit->setModel(modelAutreProduit);
    tableAutreProduit->setAlternatingRowColors(true);
    tableAutreProduit->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableAutreProduit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableAutreProduit->setColumnWidth(2,400);
    tableAutreProduit->setMinimumHeight(450);
    grid->addWidget(tableAutreProduit,1,0,2,3);

    QPushButton *addAutreProduit = new QPushButton("Enregistrer");
    grid->addWidget(addAutreProduit,0,3);

    QPushButton *effAutreProduit = new QPushButton("Effacer");
    grid->addWidget(effAutreProduit,1,3,1,1,Qt::AlignTop);

    QLabel *total_label = new QLabel("Total:");
    total_label->setObjectName("total_label");
    total_label->setFont(QFont("Dotum",15,QFont::Bold));
    total_label->setMargin(5);
    total_label->setStyleSheet("#total_label{background-color:#345584;color:white;}");
    grid->addWidget(total_label,3,0,1,1);

    totalAutreProduit = new QLabel("---");
    totalAutreProduit->setFont(QFont("Dotum",12,12,false));
    grid->addWidget(totalAutreProduit,3,1,1,1);

    setTotalAutreProduit();

    connect(addAutreProduit,SIGNAL(clicked()),this,SLOT(onClick_addAutreProduit()));
    connect(effAutreProduit,SIGNAL(clicked()),this,SLOT(OnCick_effAutreProduit()));
}


void Fen_Caisse::onClick_addAutreProduit()
{
    if(autreProduit_edit->text().isEmpty()){
        QMessageBox::warning(this,"Description du produit","Veuillez decrire le produit dans le champs.");
        return;
    }

    if(montantAutreProduit_dspin->value()<=0){
        QMessageBox::warning(this,"Montant du produit","Entrez un montant pour le produit.");
        return;
    }


    querry.prepare("INSERT INTO AutreProduits (_DATE,lbl_autreproduit,montant) "
                   "VALUES (:_DATE,:lbl_autreproduit,:montant)");

    querry.bindValue(":_DATE",dateProduit->date());
    querry.bindValue(":lbl_autreproduit",autreProduit_edit->text());
    querry.bindValue(":montant",montantAutreProduit_dspin->value());

    if(querry.exec()){
        qDebug()<<"Add autre produit succeed";
        autreProduit_edit->clear();
        montantAutreProduit_dspin->setValue(0);
        modelAutreProduit->select();
        setTotalAutreProduit();

    }else{
        qDebug()<<"Add autre produit not succeed";
        qDebug()<<querry.lastError();
    }
}

void Fen_Caisse::OnCick_effAutreProduit()
{
    int row = tableAutreProduit->selectionModel()->currentIndex().row();
    QString id = modelAutreProduit->index(row,0).data().toString();

    querry.prepare("DELETE FROM AutreProduits WHERE ID = "+id);
    if(querry.exec()){
        qDebug()<<"DELETE autre produit succeed";
        modelAutreProduit->select();
        setTotalAutreProduit();

    }else{
        qDebug()<<"DELETE autre produit not succeed";
        qDebug()<<querry.lastError();
    }
}

void Fen_Caisse::setTotalAutreProduit()
{
    double total = 0;
    querry.prepare("SELECT * FROM AutreProduits");

    if(querry.exec())
        while(querry.next())
            total += querry.value(3).toDouble();

    totalAutreProduit->setText(QString::number(total));
}
