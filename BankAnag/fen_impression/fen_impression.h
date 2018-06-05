#ifndef FEN_IMPRESSION_H
#define FEN_IMPRESSION_H

//#include <widgetStyleHeader.h>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QPrintPreviewWidget>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>

#include <QMdiSubWindow>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

class Fen_Impression : public QWidget
{
    Q_OBJECT
public:
    explicit Fen_Impression(QWidget *parent = 0);
    Fen_Impression(QSqlQuery q);
    void addHeader(QPainter *painter,QRect page);
    void setCloseFen(QMdiSubWindow*);

    
signals:
    
public slots:
    void print( QPrinter*);
    void setZoom(double);
    void closeFen();
    void addText();
    void filePrint();

private:
    QSqlQuery querry;
    QDoubleSpinBox *spinZoom;

    QPrinter *printer;
    QPrintPreviewWidget *preview;
    QMdiSubWindow *fenPreview;
    QDateEdit *date1,*date2;

    QPainter *painterGlobal;
    QPrinter* printerGlobal;
    QRect rectGlobal;
    QVBoxLayout *v;


    
};

#endif // FEN_IMPRESSION_H
