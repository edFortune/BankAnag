#ifndef FEN_TRANSACTION_H
#define FEN_TRANSACTION_H

//#include <widgetStyleHeader.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QDateEdit>
#include <QSpinBox>
#include <QLCDNumber>
#include <QGroupBox>
#include <QComboBox>
#include <QInputDialog>


#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QDebug>
#include <QTimer>

#include <QMessageBox>
#include <QMenu>
#include <QAction>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>

#include "databaseclass.h"
#include "fen_transaction/fen_transaction_delegate.h"
#include "fen_client/fen_clientProfile/fen_clientprofile_document_delegate.h"


class Fen_Transaction : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Transaction(QWidget *parent = 0);
    Fen_Transaction(QSqlQuery);
    int getSolde();
    QString setDelaisJour();
    bool checkID();
    bool verifierAutorisation();
    void setJoursPayee();

    
    void printTransaction();
    void addHeader(QPainter *painter, QRect page, QPrinter *printer);
    void addText(QPainter *painter, QPrinter *printer);
    void addFooter(QPainter *painter);
    void filePrint();
signals:

protected:
    QWidget* add_styleWidget(QString dataname,QLabel *lab_Data);
    QWidget* add_styleHeader(QString titre,QString col_titre,QLCDNumber *data,QString col_data);
    QLabel  *add_WidgetStatus(QString pathImage);
    
public slots:
    void afficheDebitDialog();
    void afficheCreditDialog();
    void closeDebitDialog();
    void closeCreditDialog();
    void chercherClient();
    bool debiterTransaction();
    bool crediterTransaction();
    void showMontantDeb(int);
    void showMontantCred(int);
    void showDialogRef();
    void showDialogFormInscrip();
    void activerBalance();
    void onTriggered_showContextMenu(QPoint);
    void supprimerData();
    void setJoursRetirer();
    void on_clicked_ZoomImage();
    void showDialogMemo();
    void onPressed_memoButton();
    void changeMemoButtonColor();


    void print(QPrinter *printer);
private:
    QSqlQuery querry;

    QDialog *debitDialog;
    QDialog *creditDialog;
    QDialog *dialogReference,*dialogFormInscrip;

    QSqlTableModel *model;
    QLabel *tabInfo[12],*tabRef[9];
    QLineEdit *comboID;
    QPushButton *deb,*cred;
    QPushButton *voirForm;

    QLineEdit *transacName;
    QSpinBox *spinDebit;
    QSpinBox *spinCredit;

    QPushButton *debiter;
    QPushButton *crediter;

    QLCDNumber *delaisJours;
    QLCDNumber *JourRetirer;

    QSpinBox *mtntTotal;
    QDateEdit *date1,*date2;

    DataBaseClass *db;

    int solde;
    int nbreDepot;
    int nbreRetrait;
    int totDebit;
    int totCredit;
    int min;

    QLabel *dateInscrip;
    QLabel *group;
    QLabel *qteVers;
    QLabel *lcdSolde;

    QStandardItemModel *mod;

    QLabel *img;
    QImage *image,image2;

    QMessageBox::StandardButton resBtn;
    QPushButton *voirRef;
    QComboBox *parQui,*delivre;
    QSpinBox *noRetrait;
    QLabel *statut;
    bool etatcompte;
    QTableView *table;

    QLCDNumber *noCompte;
    QLCDNumber *Jourspayee;

    QLabel *update,*closed;
    QPushButton *memoButton;
    bool isMemoButtonNotPressed;
    QTimer *timer;
    //int countTimer;

    QString transacType, balanceAccount, lastInsertID, transacAmount, accountGroup;

    // Transaction-list ID client
    QStringList listID;
    QMap<int,QString>listMemoMap;
    
};

#endif // FEN_TRANSACTION_H
