#ifndef FEN_LISTER_H
#define FEN_LISTER_H

//#include <widgetStyleHeader.h>

#include "fen_clientProfile/fen_clientprofile.h"

#include <QComboBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QMdiArea>
#include <QMessageBox>

class Fen_ListeClient : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_ListeClient(QWidget *parent = 0);
    Fen_ListeClient(QSqlQuery,QMdiArea *c);
    void remplirListe();

    
signals:
    
public slots:
    void supprimerData();
    void showClientAccount();
    void fermerFenClientProfil();
    void chercherClient();
    void refreshListe();
    void chercherData();
    void filtrerData();


protected:
    QWidget* add_styleWidget(QString titre,QLabel * data);

private:
    Fen_ClientProfile *ClientAccount;
    QMdiSubWindow *fenClientProfil;

    QWidget *frame_Lister;
    QGridLayout *LayoutLister;

    QSqlTableModel *model;
    QTableView *table;

    QPushButton *bcopy,*bmodifier,*beffacer,*bajout,*bimprimer,*bsupprimer,*bapercu,*tclose;
    QLineEdit *searchEdit;
    QPushButton *brecherche;
    QSpinBox *identif;

    QPushButton *printer;

    QSqlQuery querry;

    QMdiArea *central;

    QDialog *dialogRecherche;

    QComboBox *comRecherche;
    QLineEdit *editRecherch;

    QLCDNumber *lcdclient;


    QLabel *group25,*group50,*group100,*group250;

    int qteClient;

};

#endif // FEN_LISTER_H
