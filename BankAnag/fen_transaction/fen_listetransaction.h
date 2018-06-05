#ifndef FEN_LISTETRANSACTION_H
#define FEN_LISTETRANSACTION_H

#include <widgetStyleHeader.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QListView>
#include <QTableView>
#include <QDateEdit>
#include <QTreeView>
#include <QSpinBox>
#include <QTreeWidgetItem>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>

#include <QDialog>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>

#include "fen_transaction_delegate.h"

class Fen_ListeTransaction : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_ListeTransaction(QWidget *parent = 0);
    Fen_ListeTransaction(QSqlQuery);
    int getsolde();
    void getsoldeResultat();
    void addHeader(QPainter *painter,QRect page,QPrinter*);
    void addText(QPainter*,QPrinter*);
    void addFooter(QPainter *painter);
    
signals:

protected:

    
public slots:
    void choisirRecherche(int);
    void chercherDate();
    void chercherDonnee();
    void refresh();
    void imprimer();
    void print(QPrinter*);
    void showDialogRecherche();


private:
    QWidget *frame_Lister;

    QGridLayout *LayoutLister;

    QSqlTableModel *model;
    QTableView *table;

    QPushButton *bcopy,*bmodifier,*beffacer,*bajout,*bimprimer,*bsupprimer,*bapercu,*tclose;
    QComboBox *searchEdit;
    QPushButton *brecherche;
    QSpinBox *identif;

    QSqlQuery querry;
    QDialog *dialogAjout;

    QLineEdit *nomReference;
    QLineEdit *prenomReference;
    QLineEdit *adressReference;
    QSpinBox *telReference;

    QLabel *lab_qte;
    QSpinBox *spin_qte;
    QPushButton *bclose;

    QLineEdit *nomEdit,*prenomEdit,*adress,*domAct,*email;
    QSpinBox *nif,*tel,*tel1,*tel2,*postal;

    QDateEdit *dateNaiss;
    QComboBox *sexe,*titreEdit,*country,*provence;
    QStringList liste;

    QComboBox *comRech;
    QDateEdit *dateEdit;
    QDateEdit *dateEdit2;
    QPushButton *validerDate;
    QLineEdit *editRecherch;
    QPushButton *bvalider;

    QLabel *resultdepot;
    QLabel *resultretrait;
    QLabel *resultsolde;

    QLabel *r_group25,*r_group50,*r_group100,*r_group250;
    QLabel *r1_group25,*r1_group50,*r1_group100,*r1_group250;
    QLabel *r2_group25,*r2_group50,*r2_group100,*r2_group250;

    int solde;
    int nbreDepot;
    int nbreRetrait;
    int totDebit;
    int totCredit;
    QString req;

    QStringList listeClientActif;
    
};

#endif // FEN_LISTETRANSACTION_H
