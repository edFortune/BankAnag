#include "servicemanagement.h"
#include "fen_investissement/Service/emprunteur.h"
#include "fen_investissement/Service/service.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QSplitter>
#include <QMdiSubWindow>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

ServiceManagement::ServiceManagement(QWidget *parent) : QWidget(parent)
{

}

ServiceManagement::ServiceManagement(QSqlQuery q)
{
    query = q;

    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);

    QSplitter *splitter = new QSplitter;
    vbox->addWidget(splitter);

    QListWidget *listeWidget = new QListWidget;
    listeWidget->setViewMode(QListView::IconMode);
    listeWidget->setIconSize(QSize(50, 50));
    listeWidget->setMovement(QListView::Static);
    listeWidget->setMaximumWidth(110);
    listeWidget->setSpacing(12);
    splitter->addWidget(listeWidget);


    QListWidgetItem *emprunteurButton = new QListWidgetItem(listeWidget);
    emprunteurButton->setIcon(QIcon("Image/fournisseurIcon.png"));
    emprunteurButton->setText(tr("Emprunteur"));
    emprunteurButton->setTextAlignment(Qt::AlignHCenter);
    emprunteurButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    QListWidgetItem *serviceButton = new QListWidgetItem(listeWidget);
    serviceButton->setIcon(QIcon("Image/serviceIcon.png"));
    serviceButton->setText(tr("Service"));
    serviceButton->setTextAlignment(Qt::AlignHCenter);
    serviceButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    pageStack = new QStackedWidget;
    splitter->addWidget(pageStack);

    Emprunteur *emprunteurPage = new Emprunteur(query);
    pageStack->addWidget(emprunteurPage);

    Service *ServicePage = new Service(query);
    pageStack->addWidget(ServicePage);

    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,0);

    QPushButton *closeBte = new QPushButton("Close");
    closeBte->setFixedHeight(30);
    closeBte->setIcon(QIcon("Image/bclose.png"));
    vbox->addWidget(closeBte);
    vbox->setAlignment(closeBte,Qt::AlignRight);

    connect(listeWidget,SIGNAL(activated(QModelIndex)),this,SLOT(onActivatedListWidget(QModelIndex)));
    connect(closeBte,SIGNAL(clicked()),this,SLOT(fermerFen()));
}

void ServiceManagement::setFenWidget(QMdiSubWindow *sub)
{
    subWind = sub;
}

void ServiceManagement::fermerFen()
{
    subWind->close();
}

void ServiceManagement::onActivatedListWidget(QModelIndex idx)
{
    pageStack->setCurrentIndex(idx.row());
}
