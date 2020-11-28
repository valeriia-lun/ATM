#ifndef DBPATH_H
#define DBPATH_H
#pragma once

#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DBPath {
private :
     const QString _path="/MAMP/htdocs/ATM/ATM.db";
    //const QString _path="/ATM.db";
    //const QString _path = "/Users/valerie/Documents/GitHub/ATM/ATM.db";
public:

    DBPath() {}

    ~DBPath() {}

    QString getPath() {
        //qDebug() << "App path : " << qApp->applicationDirPath();
        qDebug() << "PATH" << _path;
        return _path;
    }
};


#endif // DBPATH_H
