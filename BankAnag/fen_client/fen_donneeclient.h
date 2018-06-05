#ifndef FEN_DONNEECLIENT_H
#define FEN_DONNEECLIENT_H

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

#include <QFileDialog>
#include <QMessageBox>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>

class Fen_DonneeClient : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_DonneeClient(QWidget *parent = 0);
    Fen_DonneeClient(QSqlQuery);
    bool verifierCode();
    QString setDelaisJour();
    
signals:
    
public slots:
    void getData();
    void modifierData();
    void addPicdialogBox();
    void addPicRef_dialogBox();
    void addPicFormInscrip_dialogBox();

private:
    QSqlQuery querry;

    QTabWidget *tabWid;

    QLineEdit *search,*nomMere;
    QPushButton *validID;

    QComboBox *titre,*typePiece;
    QLineEdit *nom;
    QComboBox *nationalite;

    QLineEdit *prenom;
    QDateEdit *dateNaiss;

    QLineEdit *nif;
    QComboBox *sexe;

    QLineEdit *domAct;

    QSpinBox *idd,*telMaison,*teltravail,*mobil;

    QLineEdit *adress, *email;


    QComboBox *pays,*departement;
    QSpinBox *codePostal;

    QLineEdit *nomRef;
    QLineEdit *prenomRef;
    QSpinBox *telRef;
    QLineEdit *addRef;

    QDateEdit *dateInscrip;
    QComboBox *type;
    QSpinBox *qteVers;
    QSpinBox *mtntCom;

    QGroupBox *groupInfoPerso,*grouptel,*groupRef,*groupCompte;

    QPushButton *modif;
    QSpinBox *nbrJour;
    
    QLabel *image,*imgForm;

    QComboBox *typePiece_ref,*titreRef,*sexeRef;
    QLabel *imageRef;
    QComboBox *autorisation;
    QLineEdit *nomReference,*prenomReference,*adressReference,*nifRef;
    QSpinBox *telReference;

    QString PicName,PicName_ref,PicName_form;
    QComboBox *statut;

};

#endif // FEN_DONNEECLIENT_H
