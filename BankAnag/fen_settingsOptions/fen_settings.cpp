#include "fen_settings.h"


Fen_Settings::Fen_Settings(QWidget *parent) :
    QWidget(parent)
{

}


Fen_Settings::Fen_Settings(QSqlQuery q)
{
    querry = q;

    QVBoxLayout *v = new QVBoxLayout;
    this->setLayout(v);

    QLabel *titre = new QLabel("Settings");
    titre->setFont(QFont("",15,15,false));
    v->addWidget(titre);


    QSplitter *splitter = new QSplitter;
    v->addWidget(splitter);

    listWidget = new QListWidget;
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(50, 50));
    listWidget->setMovement(QListView::Static);
    listWidget->setMaximumWidth(100);
    listWidget->setSpacing(10);
    splitter->addWidget(listWidget);

    QListWidgetItem *listeTransactionButton = new QListWidgetItem(listWidget);
    listeTransactionButton->setIcon(QIcon("Image/info.png"));
    listeTransactionButton->setText(tr("Liste des\ntransactions"));
    listeTransactionButton->setTextAlignment(Qt::AlignHCenter);
    listeTransactionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *listeClientButton = new QListWidgetItem(listWidget);
    listeClientButton->setIcon(QIcon("Image/liste.png"));
    listeClientButton->setText(tr("Liste des\nclients"));
    listeClientButton->setTextAlignment(Qt::AlignHCenter);
    listeClientButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    pagesWidget = new QStackedWidget;
    splitter->addWidget(pagesWidget);

    pagesWidget->addWidget(add_SettingsListeTransaction());
    pagesWidget->addWidget(add_SettingsListeClient());


    QObject::connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,\
                     SLOT(onChangeItem(QListWidgetItem*,QListWidgetItem*)));
}

void Fen_Settings::onChangeItem(QListWidgetItem *current,QListWidgetItem *previous)
{
    if(!current)
        current = previous;

    pagesWidget->setCurrentIndex(listWidget->row(current));
}
