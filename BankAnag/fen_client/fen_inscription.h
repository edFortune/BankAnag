#ifndef FEN_INSCRIPTION_H
#define FEN_INSCRIPTION_H

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
#include <QComboBox>
#include <QRadioButton>

#include <QSqlQueryModel>
#include <QCompleter>

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>

#include <QMessageBox>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

#include "databaseclass.h"

class Fen_Inscription : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Inscription(QWidget *parent = 0);
    Fen_Inscription(QSqlQuery);
    bool verification();
    
    QCompleter* setCompleterQuery(QString query);
signals:
    
public slots:
    void enregistrer();
    void addPicdialogBox();
    void addPicRef_dialogBox();
    void addPicFormInscrip_dialogBox();


private:
    QFormLayout *form_Inscrip;

    QVBoxLayout *vframe_Inscrip;
    QGridLayout *gridLayout;
    QLabel *titre;
    QLabel *image,*logo;

    QGroupBox *groupbox;
    QVBoxLayout *vgroupbox;

    QGroupBox *groupbox2;
    QFormLayout *form_Inscrip2;

    QGroupBox *groupboxTel;
    QFormLayout *form_Tel;

    QLineEdit *nomReference;
    QLineEdit *prenomReference;
    QLineEdit *adressReference;
    QSpinBox *telReference;

    QLineEdit *nomReference2;
    QLineEdit *prenomReference2;
    QLineEdit *adressReference2;
    QSpinBox *telReference2;
    QSpinBox *nifRef2;
    QComboBox *titreRef,*sexeRef;

    QGroupBox *groupbox3;
    QFormLayout *form_Inscrip3;

    QLabel *imgForm;

    QGroupBox *groupchoix;
    QRadioButton *groupeA,*groupeB,*groupeC,*groupeD;
    QComboBox *groupCombo;

    QVBoxLayout *groupLayout;
    QString PicName,PicName_ref,PicName_form;

    QLabel *lab_qte;
    QSpinBox *spin_qte;
    QPushButton *bclose, *benreg;

    QLineEdit *nomEdit,*prenomEdit,*adress,*domAct,*email,*nif,*nifRef;
    QSpinBox *idd,*tel,*tel1,*tel2,*postal;

    QComboBox *typePiece;
    QComboBox *nationalite;

    QDateEdit *dateNaiss;
    QComboBox *sexe,*titreEdit,*country,*provence;

    QDateEdit *dateInscrip;
    QSpinBox *montantCom;

    QComboBox *typePiece_ref;

    QLabel *imageRef;
    QLineEdit *nomMere;
    QComboBox *autorisation,*statut;

    QSqlQuery q;
    QTabWidget *centre;

    QImage imagePic,imagePicRef,imagePicform;

    int solde;
    int totDebit;
    int totCredit;

    
};

#endif // FEN_INSCRIPTION_H
