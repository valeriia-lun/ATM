#ifndef DBPATH_H
#define DBPATH_H
#pragma once
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DBPath{
private :
      const QString _path="/Users/valerie/Documents/GitHub/ATM/ATM.db";
public:
    DBPath(){}
    ~DBPath(){}
    QString getPath(){return _path;}
};




#endif // DBPATH_H
