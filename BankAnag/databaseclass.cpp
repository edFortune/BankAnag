#include "databaseclass.h"


DataBaseClass::DataBaseClass()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    if(!db.isOpen()){
        db.setDatabaseName("explusDB");
        bool check = db.open();

        if (!check) {
            qDebug() << "Connection to database failed: " << db.lastError();
        }else{
            qDebug() << "Connection to database succeed " << endl;
            QSqlQuery q(db);
            querry = q;
        }
    }


}

DataBaseClass::DataBaseClass(QString location)
{
    qDebug()<<"***"<<"Database apply in "<<location<<"***";

}

QSqlQuery DataBaseClass::getSqlQuerry()
{
    return querry;
}

void DataBaseClass::makeRequest(QString req)
{
    querry.prepare(req);
    bool c = querry.exec();
    if(c)
        qDebug()<<"Request succeed";
    else
        qDebug()<<"Request failed: "<<querry.lastError();

}

void DataBaseClass::alterTable_AddColumn(QString tableName, QString colName, QString colType)
{
    querry.prepare("ALTER TABLE "+tableName+" ADD COLUMN "+colName+" "+colType+" ");

    if(querry.exec())
        qDebug()<<"Column "<<colName<<" was added in table "<<tableName;
    else{
        qDebug()<<"Column "<<colName<<" was not added in table "<<tableName;
        qDebug()<<querry.lastError();
        qDebug()<<db.lastError();

    }
}

void DataBaseClass::createTable(QString req, QString tablename)
{
    querry.prepare(req);

    bool c = querry.exec();
    if(c)
        qDebug()<<tablename+" created";
    else{
        qDebug()<<tablename+"not created";
        qDebug()<<querry.lastError();

    }
}

void DataBaseClass::setEnablePragma(bool c)
{
    if(c){
        bool b = querry.exec("PRAGMA foreign_keys = ON");
        if(b)
            qDebug()<<"Pragma ON succeed";
        else
            qDebug()<<"Pragma ON failed";
    }else{

        bool b = querry.exec("PRAGMA foreign_keys = OFF");
        if(b)
            qDebug()<<"Pragma OFF succeed ";
        else
            qDebug()<<"Pragma OFF failed";
    }
}


void DataBaseClass::closeDataBase()
{
    db.close();
    qDebug()<<"Database closed";
}


bool DataBaseClass::deleteTable(QString tableName)
{
    bool c = querry.exec("DROP TABLE IF EXISTS "+tableName);

    if(c){
        qDebug()<<"Table was deleted: "+tableName;
        return true;
    }
    else{
        qDebug()<<"Table was not deleted: "+tableName;
        return false;
    }
}

void DataBaseClass::backupData()
{
    QString tableName = "";

    //1) Find the list of tables in the database
    for(int i=0;i<db.tables().size();i++){

        //2) Get a table name in the list and save it in a variable
        tableName = db.tables().at(i);

        //3) Open the file system with the name of the table found
        QFile file("backUpData/"+tableName+".csv");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        //4) Get the output stream of the file which let you write in.
        QTextStream out(&file);

        //5) Get the name of columns in the table in a loop and put them in the output stream
        for(int j=0; j<db.record(db.tables().at(i)).count();j++)
            out<<db.record(db.tables().at(i)).fieldName(j)<<",";
        out<<"\n";

        //6) Send a querry to the database with the table name to find its data
        querry.prepare("SELECT * FROM "+tableName);
        bool c = querry.exec();
        if(c)
            while(querry.next()){
                for(int i=0;i<34;i++){
                    if(querry.value(i).toString().contains(","))
                        out<<querry.value(i).toString().replace(","," ")<<",";
                    else
                        out<<querry.value(i).toString()<<",";
                }
                out<<"\n";
            }
        else
            querry.lastError();

        //7) Finally, close the file and save it on the system.
        file.close();
    }

}



