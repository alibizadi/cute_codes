#include "database.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "QDebug"

Database::Database(QObject *parent) : QObject(parent)
{
    QSqlDatabase Appdb=QSqlDatabase::addDatabase("QMYSQL");
    Appdb.setHostName("localhost");
    Appdb.setDatabaseName("USERS");
    Appdb.setUserName("admin");
    Appdb.setPassword("admin");

    if(!Appdb.open())
        qDebug()<<"Database not open!!!";

    QSqlQuery q;
    q.exec("CREATE TABLE users (id INT PRIMARY KEY , username TEXT , password TEXT);");
}

bool Database::saveuser(QString str1, QString str2)
{
    bool ok=false;
    id=0;

    QSqlQuery q;
    q.exec("SELECT username FROM users");

    while (q.next()) {
        if(!str1.compare(q.value(0).toString()))
            return false;
    }

    q.exec("SELECT id FROM users");
    while (q.next()) {
        id++;
    }
    id++;

    ok=q.exec("INSERT INTO users VALUES ('"+QString::number(id)+"','"+str1+"','"+str2+"')");

    username=str1;
    password=str2;

    return ok;
}

bool Database::checkuser(QString str)
{
    bool ok=false;

    QSqlQuery q;
    q.exec("SELECT password FROM users WHERE username='"+str+"'");

    if(q.first()){
        ok=true;
        password=q.value(0).toString();
        username=str;
    }

    return ok;
}
