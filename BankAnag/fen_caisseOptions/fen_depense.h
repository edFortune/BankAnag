#ifndef FEN_DEPENSE_H
#define FEN_DEPENSE_H

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

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>


class Fen_Depense : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Depense(QWidget *parent = 0);
    Fen_Depense(QSqlQuery);
    void totaliserDepense();
    
signals:
    
public slots:
    void validerDepense();
    void effacerDepense();
    void on_click_changeTab(int);

protected:
    QWidget* add_styleWidget(QString titre,QLabel * data);

private:
    QWidget *frame_Lister;
    QGridLayout *LayoutLister;

    QSqlTableModel *model,*model_2;
    QTreeView *table,*table_2;

    QPushButton *bimprimer,*bsupprimer,*tclose;

    QSqlQuery querry;
    QLabel *lab_qte;
    QSpinBox *spin_qte;
    QPushButton *bclose;

    QDateEdit *dater;
    QLineEdit *descrip;
    QDoubleSpinBox *mtnt;
    QLabel *totaldep,*totaldepPayer,*totalGeneral;

    int indexTab;
    
};

#endif // FEN_DEPENSE_H
