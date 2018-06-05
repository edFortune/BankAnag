#include "investmenttransaction.h"

InvestmentTransaction::InvestmentTransaction(QWidget *parent) : QWidget(parent)
{

}

InvestmentTransaction::InvestmentTransaction(QSqlQuery q)
{
    query = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QSplitter *splitter = new QSplitter;
    vbox->addWidget(splitter);

    QListWidget *listeWidget = new QListWidget;
    listeWidget = new QListWidget;
    listeWidget->setViewMode(QListView::IconMode);
    listeWidget->setIconSize(QSize(80, 80));
    listeWidget->setMovement(QListView::Static);
    listeWidget->setMaximumWidth(128);
    listeWidget->setSpacing(12);
    splitter->addWidget(listeWidget);

    QListWidgetItem *produitButton = new QListWidgetItem(listeWidget);
    produitButton->setIcon(QIcon("Image/produitInvestIcon.png"));
    produitButton->setText(tr("Produit"));
    produitButton->setTextAlignment(Qt::AlignHCenter);
    produitButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *serviceButton = new QListWidgetItem(listeWidget);
    serviceButton->setIcon(QIcon("Image/liste.png"));
    serviceButton->setText(tr("Service"));
    serviceButton->setTextAlignment(Qt::AlignHCenter);
    serviceButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QStackedWidget *pageStack = new QStackedWidget;
    splitter->addWidget(pageStack);

    ProduitTransaction *produitTransacPage = new ProduitTransaction(query);
    produitTransacPage->setFenWidget(subWindow);
    pageStack->addWidget(produitTransacPage);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,0);

}


void InvestmentTransaction::setFenWidget(QMdiSubWindow *sub)
{
    subWindow = sub;
}
