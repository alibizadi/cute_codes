#ifndef DATABASE_H
#define DATABASE_H

#include "QObject"


class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

signals:

public slots:
    QString usernamee(){return username;}
    QString passwordd(){return password;}
    bool saveuser(QString,QString);
    bool checkuser(QString);

private:
    QString username;
    QString password;
    int id;

};

#endif // DATABASE_H
