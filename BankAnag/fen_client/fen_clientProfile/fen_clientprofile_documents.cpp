#include "fen_clientprofile.h"
#include "fen_clientprofile_document_delegate.h"


QWidget* Fen_ClientProfile::setDocumentClientTab()
{
    QWidget *documentTab = new QWidget;

    QHBoxLayout *hbox = new QHBoxLayout;
    documentTab->setLayout(hbox);

    listWidget = new QListWidget;
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(70, 70));
    listWidget->setMovement(QListView::Static);
    listWidget->setMaximumWidth(128);
    listWidget->setSpacing(12);
    hbox->addWidget(listWidget);

    QListWidgetItem *item1 = new QListWidgetItem(listWidget);
    item1->setIcon(QIcon("Image/memoIcon.png"));
    item1->setText(tr("Memo"));
    item1->setTextAlignment(Qt::AlignHCenter);
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    stackWid = new QStackedWidget;
    hbox->addWidget(stackWid,5);

    QWidget *memoWidget = new QWidget;
    stackWid->addWidget(memoWidget);
    setPageMemo(memoWidget);


    connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
            SLOT(changePageDocument(QListWidgetItem*,QListWidgetItem*)));

    return documentTab;
}



void Fen_ClientProfile::changePageDocument(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current)
        current = previous;

    stackWid->setCurrentIndex(listWidget->row(current));

}

void Fen_ClientProfile::setPageMemo(QWidget* wid)
{
    QGridLayout *grid = new QGridLayout;
    wid->setLayout(grid);

    modelMemo = new QSqlTableModel;
    modelMemo->setTable("MemoTable");
    modelMemo->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelMemo->select();

    tableMemo = new QTableView;
    tableMemo->setModel(modelMemo);
    tableMemo->setColumnWidth(1,500);
    tableMemo->resizeRowsToContents();
    tableMemo->setAlternatingRowColors(true);
    tableMemo->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableMemo->setItemDelegate(new Fen_ClientProfil_document_delegate(tableMemo));
    grid->addWidget(tableMemo,0,0,1,2);

    memoTextEdit = new QTextEdit;
    memoTextEdit->setPlaceholderText("Ajouter un memo");
    grid->addWidget(memoTextEdit,1,0,3,1);

    QPushButton *addMemo_button = new QPushButton("Ajouter");
    grid->addWidget(addMemo_button,1,1);

    QPushButton *effMemo_button = new QPushButton("Effacer");
    grid->addWidget(effMemo_button,2,1);

    check_memo_comb = new QComboBox;
    check_memo_comb->addItem("Non");
    check_memo_comb->addItem("Oui");
    grid->addWidget(check_memo_comb,3,1);

    modelMemo->setFilter("ID_CLIENT ="+foreign_id);

    connect(addMemo_button,SIGNAL(clicked()),this,SLOT(onClicked_addMemoButton()));
    connect(effMemo_button,SIGNAL(clicked()),this,SLOT(onClicked_effMemoButton()));

}

void Fen_ClientProfile::onClicked_addMemoButton()
{
    if(memoTextEdit->toPlainText().isEmpty())
        return;

    querry.prepare("INSERT INTO MemoTable (memo,check_memo,ID_CLIENT) VALUES (:memo,:check_memo,:ID_CLIENT)");

    querry.bindValue(":memo",memoTextEdit->toPlainText());
    querry.bindValue(":check_memo",check_memo_comb->currentText());
    querry.bindValue(":ID_CLIENT",foreign_id);

    if(querry.exec()){
        qDebug()<<"Memo insert into table";
        memoTextEdit->clear();
        modelMemo->select();
    }else{
        qDebug()<<"Memo is not inserted into table";
        qDebug()<<querry.lastError();
    }
}

void Fen_ClientProfile::onClicked_effMemoButton()
{
    int row = tableMemo->selectionModel()->currentIndex().row();
    QString id = modelMemo->index(row,0).data().toString();

    querry.prepare("DELETE FROM MemoTable WHERE ID = "+id);

    if(querry.exec()){
        qDebug()<<"Memo deleted";
        modelMemo->select();
    }
}

