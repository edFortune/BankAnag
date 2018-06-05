#ifndef SERVICEMANAGEMENT_H
#define SERVICEMANAGEMENT_H

#include <QWidget>
#include <QStackedWidget>
#include <QMdiSubWindow>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>


class ServiceManagement : public QWidget
{
    Q_OBJECT
public:
    explicit ServiceManagement(QWidget *parent = 0);
    ServiceManagement(QSqlQuery q);

    void setFenWidget(QMdiSubWindow *sub);
signals:

private slots:
    void onActivatedListWidget(QModelIndex idx);

    void fermerFen();
public slots:

private:
    QMdiSubWindow *subWind;
    QSqlQuery query;

    QStackedWidget *pageStack;
};

#endif // SERVICEMANAGEMENT_H
