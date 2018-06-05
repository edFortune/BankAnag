#ifndef FEN_TRANSACTIONINFO_H
#define FEN_TRANSACTIONINFO_H

#include <widgetStyleHeader.h>

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


#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QDebug>

#include <QMessageBox>



class Fen_transactionInfo : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_transactionInfo(QWidget *parent = 0);
    Fen_transactionInfo(QSqlQuery q);


    
signals:

protected:
    void setTransactionTab(QWidget*);
    void add_dataTotableTransaction();
    
public slots:
    void on_doubleClick_tableTransacion(QModelIndex);

private:
    QSqlQuery querry;

    QLabel *img,*imgClient;
    QStandardItemModel *model;
    QTableView *tableTransaction;
    QLabel *lab_ID,*lab_Nom,*lab_Prenom,*lab_depot,*lab_retrait,*lab_solde,*lab_groupe,*lab_status;

};

#endif // FEN_TRANSACTIONINFO_H
