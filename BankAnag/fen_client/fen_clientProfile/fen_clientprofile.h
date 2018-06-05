#ifndef FEN_CLIENTPROFILE_H
#define FEN_CLIENTPROFILE_H

//#include <widgetStyleHeader.h>
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
#include <QMessageBox>
#include <QImage>
#include <QListWidget>
#include <QStackedWidget>
#include <QTextEdit>
#include <QComboBox>

#include <QMdiSubWindow>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QDebug>

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>


class Fen_ClientProfile : public QWidget
{
    Q_OBJECT
public:
    //Profil client Tab
    explicit Fen_ClientProfile(QString,QSqlQuery);
    void setCLientInfo(QString);

    //List Transaction Tab
    int getSolde();
    void setDataTransaction();
    QString setDelaisJour();
    void addHeader(QPainter *painter,QRect page,QPrinter*);
    void addText(QPainter*,QPrinter*);
    void addFooter(QPainter *painter);
    QWidget *setTransactionTab();
    QString getDates();


    //Document Tab
    QWidget* setDocumentClientTab();
    void setPageMemo(QWidget* wid);
    
signals:
    
public slots:
    //Profil client Tab
    void onTabBarClicked(int);
    void showDialogFormInscrip();
    void addPicdialogBox();
    void addPicRef_dialogBox();
    void addPicForm_dialogBox();

    //List Transaction Tab
    void imprimer();
    void print(QPrinter*);
    void chercher();
    void refresh();

    //Documents Tab
    void changePageDocument(QListWidgetItem *, QListWidgetItem *);
    void onClicked_addMemoButton();
    void onClicked_effMemoButton();




private:
    //-------Client profile ----------
    QVBoxLayout *pVLayout;
    QGridLayout *pGLayout1;
    QGridLayout *pGLayout2;
    QTableView *pTableTransaction;

    QFormLayout *pFormLayout;
    QWidget *pWidget;
    QMdiSubWindow *fenProfile;

    QLCDNumber *delai;

    QLabel *pPhoto,*pPhoto1,*pTableauInfo[10],*tel_TableauInfo[8],*ref_TableauInfo[9],*infoTabTransac[5];

    QLabel *dateInscrip;
    QLabel *group;
    QLabel *qte;
    QLabel *mtnt;


    QTableView *transac_table;

    QGroupBox *grouProfInfo;

    QSqlTableModel *modelTransaction;

    QGroupBox *ptitre;
    QFormLayout *pFormtransac ;
    QSpinBox *debitEdit,*creditEdit;

    QPushButton *valider;

    QString foreign_id;
    QLabel *state;
    QSqlQuery querry;

    QDialog *dialogFormInscrip;
    QString IDCLIENT,PicName,PicName_ref,PicName_form;
    QLabel *imgForm;

    QCheckBox *check1,*check2;
    QDateEdit *date1,*date2;


    int solde;
    int nbreDepot;
    int nbreRetrait;
    int totDebit;
    int totCredit;
    int qteDepot;
    int qteRetrait;
    QString req;

    //Document tab
    QListWidget *listWidget;
    QStackedWidget *stackWid;
    QSqlTableModel *modelMemo;
    QTextEdit *memoTextEdit;
    QComboBox *check_memo_comb;
    QTableView *tableMemo;
    
};

#endif // FEN_CLIENTPROFILE_H
