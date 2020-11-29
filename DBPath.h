#ifndef DBPATH_H
#define DBPATH_H
#pragma once

#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DBPath {
public:

    DBPath() {}

    ~DBPath() {}

    QString getPath() {
//            QString s=QCoreApplication::applicationDirPath();
//            QString res;
//            for(int i=0;i<s.length();i++){
//                if(s.at(i)==QChar('b')&&s.at(i+1)==QChar('u')&&s.at(i+2)=='i'&&s.at(i+3)==QChar('l')&&s.at(i+4)==QChar('d')){
//                        break;
//            }else{
//                    res+=s.at(i);
//                }
//            }


          //  qDebug()<< res+"ATM/ATM.db";
           // return res+"ATM/ATM.db";
            return "/Users/valerie/Documents/GitHub/ATM/ATM.db";
        }
};


#endif // DBPATH_H
