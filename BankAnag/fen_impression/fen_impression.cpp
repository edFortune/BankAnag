#include "fen_impression.h"

Fen_Impression::Fen_Impression(QWidget *parent) :
    QWidget(parent)
{

}


Fen_Impression::Fen_Impression(QSqlQuery q)
{
    querry = q;

    v = new QVBoxLayout;
    this->setLayout(v);

    QGridLayout *h = new QGridLayout;
    h->setSpacing(0);
    h->setMargin(0);
    v->addLayout(h);

    spinZoom = new QDoubleSpinBox;
    spinZoom->setMinimum(1.0);
    //h->addWidget(spinZoom,0,0);

    QLabel *l = new QLabel("Recherche:");
    h->addWidget(l,0,0);

    QLabel *de = new QLabel("De");
    h->addWidget(de,0,1);

    date1 = new QDateEdit;
    date1->setCalendarPopup(true);
    date1->setDate(QDate::currentDate());
    date1->setDisplayFormat("dd/MM/yyyy");
    h->addWidget(date1,0,2);

    QLabel *a = new QLabel("a");
    h->addWidget(a,0,3);

    date2 = new QDateEdit;
    date2->setCalendarPopup(true);
    date2->setDate(QDate::currentDate());
    date2->setDisplayFormat("dd/MM/yyyy");
    h->addWidget(date2,0,4);

    QPushButton *searchBut = new QPushButton("Chercher");
    searchBut->setIcon(QIcon("Image/searchIcon.png"));
    searchBut->setIconSize(QSize(30,30));
    searchBut->setFlat(true);
    h->addWidget(searchBut,0,5);

    QComboBox *combZoom = new QComboBox;
    combZoom->addItem("10%");
    combZoom->addItem("20%");
    combZoom->addItem("50%");
    combZoom->addItem("70%");
    combZoom->addItem("100%");
    h->setAlignment(combZoom,Qt::AlignLeft);
    h->addWidget(combZoom,1,0);


    QPushButton *zoomIn = new QPushButton("Zoom In");
    zoomIn->setIcon(QIcon("Image/zoomIn.png"));
    zoomIn->setIconSize(QSize(30,30));
    zoomIn->setFlat(true);
    h->setAlignment(zoomIn,Qt::AlignLeft);
    h->addWidget(zoomIn,1,1);

    QPushButton *zoomOut = new QPushButton("Zoom Out");
    zoomOut->setIcon(QIcon("Image/zoomOut.ico"));
    zoomOut->setIconSize(QSize(30,30));
    zoomOut->setFlat(true);
    h->setAlignment(zoomOut,Qt::AlignLeft);
    h->addWidget(zoomOut,1,2);

    QPushButton *backpage = new QPushButton("Back");
    backpage->setIcon(QIcon("Image/back.png"));
    backpage->setIconSize(QSize(30,30));
    backpage->setFlat(true);
    h->addWidget(backpage,1,3);

    QLineEdit *numPage = new QLineEdit;
    numPage->setMaximumWidth(100);
    h->addWidget(numPage,1,4);

    QPushButton *nexPage = new QPushButton("Next");
    nexPage->setIcon(QIcon("Image/next.png"));
    nexPage->setIconSize(QSize(30,30));
    nexPage->setFlat(true);
    h->addWidget(nexPage,1,5);

    QPushButton *printPage = new QPushButton("Imprimer");
    printPage->setIcon(QIcon("Image/print.png"));
    printPage->setIconSize(QSize(30,30));
    printPage->setFlat(true);
    h->addWidget(printPage,1,6);

    QPushButton *closefenButton = new QPushButton("Fermer");
    closefenButton->setIcon(QIcon("Image/bclose.png"));
    closefenButton->setIconSize(QSize(30,30));
    closefenButton->setFlat(true);
    h->addWidget(closefenButton,1,7);



    printer = new QPrinter(QPrinter::HighResolution );
    preview = new QPrintPreviewWidget(printer,this);
    preview->setZoomFactor(spinZoom->value());
    v->addWidget(preview);


    connect(preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    connect(spinZoom,SIGNAL(valueChanged(double)),this,SLOT(setZoom(double)));
    connect(closefenButton,SIGNAL(clicked()),this,SLOT(closeFen()));
    connect(searchBut,SIGNAL(clicked()),this,SLOT(addText()));
    connect(printPage,SIGNAL(clicked()),this,SLOT(filePrint()));
}


void  Fen_Impression::print( QPrinter* printer )
{
  // create painter for drawing print page
  QPainter painter( printer );
  int      w = printer->pageRect().width();
  int      h = printer->pageRect().height();
  QRect    page( 0, 0, w, h );

  // create a font appropriate to page size
  QFont    font = painter.font();
  font.setPixelSize( (w+h) / 150 );
  painter.setFont( font );

  addHeader(&painter,page);

  // draw simulated landscape
  page.adjust( w/20, h/20, -w/20, -h/20 );

}

void Fen_Impression::setZoom(double d)
{
    preview->setZoomFactor(d/10);
}

void Fen_Impression::addHeader(QPainter *painter,QRect page)
{
    // draw labels in corners of page
    painter->drawText( page, Qt::AlignTop    | Qt::AlignLeft, "Rapport des transaction" );
    painter->drawText( page, Qt::AlignTop | Qt::AlignRight,QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm AP") );


    painter->drawText(200,500 ,"DATE" );
    painter->drawText(1000,500 ,"HEURE" );
    painter->drawText(1600,500 ,"DESCRIPTION" );
    painter->drawText(2600,500 ,"RETRAITS" );
    painter->drawText(3400,500 ,"DEPOTS" );
    painter->drawText(4000,500 ,"SOLDE" );


    painter->drawLine(200,530,4400,530);
    painter->drawLine(200,550,4400,550);

    //painter->eraseRect(page);
    //painter->drawImage(0,0,QImage("Image/searchIcon.png"));

}

void Fen_Impression::addText()
{



//    querry.prepare("SELECT * FROM transaction_table_6");
//    bool c = querry.exec();
//    int y = 700;
//    int lines = 0;
//    if(c)
//    {
//        while(querry.next() && lines <35)
//        {
//            painterGlobal->drawText(200,y,querry.value(1).toString());
//            painterGlobal->drawText(1000,y,querry.value(2).toString());
//            painterGlobal->drawText(1600,y,querry.value(3).toString());
//            painterGlobal->drawText(2600,y,querry.value(4).toString());
//            painterGlobal->drawText(3400,y,querry.value(5).toString());
//            painterGlobal->drawText(4000,y,querry.value(7).toString());

//            painterGlobal->drawLine(200,y+20,4400,y+20);

//            lines++;
//            y +=150;
//        }
//    }
}

void  Fen_Impression::filePrint()
{
  // display print dialog and if accepted print
  QPrinter       printer( QPrinter::HighResolution );
  QPrintDialog   dialog( &printer, this );
  if ( dialog.exec() == QDialog::Accepted ) print( &printer );
}

void Fen_Impression::setCloseFen(QMdiSubWindow *fen)
{
    fenPreview = fen;
}

void Fen_Impression::closeFen()
{
    fenPreview->close();
}
