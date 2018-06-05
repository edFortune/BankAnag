#ifndef DATABASECLASS_H
#define DATABASECLASS_H

//#include <widgetStyleHeader.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>

#include <QStringList>

#include <QFile>

class DataBaseClass
{
public:
    DataBaseClass();
    DataBaseClass(QString location);
    QSqlQuery getSqlQuerry();
    void createTable(QString,QString);
    void setEnablePragma(bool);
    void makeRequest(QString);
    void alterTable_AddColumn(QString tableName, QString colName, QString colType);
    void backupData();
    void closeDataBase();
    bool deleteTable(QString);

protected:

private:
    QSqlQuery querry;
    QSqlDatabase db;
};

#endif // DATABASECLASS_H
