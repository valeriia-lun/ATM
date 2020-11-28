#include "AccountsService.h"
#include "UserService.h"
#include <QtDebug>
int monthToInt(QString month){
    int res;
    if(month == "Jan"){
        return 1;
    }
    if(month == "Feb"){
        return 2;
    }
    if(month == "Mar"){
        return 3;
    }
    if(month == "Apr"){
        return 4;
    }
    if(month == "May"){
        return 5;
    }
    if(month == "Jun"){
        return 6;
    }
    if(month == "Jul"){
        return 7;
    }
    if(month == "Aug"){
        return 8;
    }
    if(month == "Sep" || month == "Sept"){
        return 9;
    }
    if(month == "Oct"){
        return 10;
    }
    if(month == "Nov"){
        return 11;
    }
    if(month == "Dec"){
        return 12;
    }

}
bool isEarlierThan(QString date1, QString date2){
    QStringList list1 = date1.split(" ", QString::SkipEmptyParts);
    QString month1 = list1[1];
    int day1 = list1[2].toUInt();
    QString time1 = list1[3];
    int year1 = list1[4].toUInt();

     QStringList list1_1 = time1.split(":", QString::SkipEmptyParts);
     int hour1 = list1_1[0].toUInt();
     int min1 = list1_1[1].toUInt();
     int sec1 = list1_1[2].toUInt();

     qDebug() << month1 << day1 << year1 << hour1 <<  min1 << sec1 ;

     QStringList list2 = date2.split(" ", QString::SkipEmptyParts);
     QString month2 = list2[1];
     int day2 = list2[2].toUInt();
     QString time2 = list2[3];
     int year2 = list1[4].toUInt();
     year2--;
      QStringList list2_1 = time2.split(":", QString::SkipEmptyParts);
      int hour2 = list2_1[0].toUInt();
      int min2 = list2_1[1].toUInt();
      int sec2 = list2_1[2].toUInt();

qDebug() << month2 << day2 << year2 << hour2 <<  min2 << sec2 ;
      if(year1 > year2){
          return false;
      }else if(year1 < year2){
          return true;
      }else{
          if(monthToInt(month1) < monthToInt(month2)){
              return true;
          }else if(monthToInt(month1) > monthToInt(month2)){
              return false;
          }else{
              if(day1 < day2){
                  return true;
              }else if(day1 > day2){
                  return false;
              }else{
                  if(hour1 < hour2){
                      return true;
                  }else if(hour1 > hour2){
                      return false;
                  }else{
                      if(min1 < min2){
                          return true;
                      }else if(min1 > min2){
                          return false;
                      }else{
                          if(sec1 < sec2){
                              return true;
                          }else if(sec1 > sec2){
                              return false;
                          }else{
                              return false;
                          }
                      }
                  }
              }
          }
      }
}

void createUniversalAccount(int userIdATM, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                                        int limit, QString expiryDate,  bool isBlocked){
    UniversalAccount ua(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,expiryDate);
     expiryDate = ua.expiryDate();
     QString sql("INSERT INTO UNIVERSAL_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance, user_id, limit, isBlocked) VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', '"+ QString::number(sumOnBalance) + "', '"+ QString::number(userIdATM) + "', '" + QString::number(limit) + "','" + QString::number(isBlocked)+"')");
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
    q.exec(sql);
    q.clear();
    db.close();
}

void createCreditAccount(int creditTerm, double creditDept, int userIdATM, QString cardNumber, QString pin, QString cvv,
                                  double sumOnBalance, int limit, bool isBlocked, QString expiryDate,
                                  QString creditExpiryDate){

    CreditAccount ca(creditTerm,creditDept,userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,"");
        expiryDate = ca.expiryDate();
        creditExpiryDate = ca.creditExpiryDate();
        sumOnBalance = ca.sumOnBalance();
        QString sql("INSERT INTO CREDIT_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance,credit_term,credit_expiry_date,credit_debt, user_id)"
                   " VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', '"+ QString::number(sumOnBalance) + "', '"+ QString::number(creditTerm)+"', '"+ creditExpiryDate+ "', '" + QString::number(creditDept)+ "', '"+ QString::number(userIdATM) + "', '" + QString::number(limit) + "','" + QString::number(isBlocked)+"'");
        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
        q.exec(sql);
        q.clear();
        db.close();
}

void createDepositAccount(int userIdATM, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                                    int limit,QString expiryDate,  bool isBlocked,int depositTerm, int depositPercentage,
                                    QString depositExpiryDate){
    DepositAccount da(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,"",false,depositTerm,depositPercentage,"");
       expiryDate = da.expiryDate();
       depositExpiryDate = da.depositExpiryDate();
       sumOnBalance = da.sumOnBalance();
       QString sql("INSERT INTO DEPOSIT_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance,deposit_term,deposit_expiry_date,deposit_percentage, user_id)"
                  " VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', '"+ QString::number(sumOnBalance) + "', '"+ QString::number(depositTerm)+"', '"+ depositExpiryDate+ "', '" + QString::number(depositPercentage)+ "', '"+ QString::number(userIdATM) +  "','" + QString::number(isBlocked) + "', '" + QString::number(limit)+"'");
       //DB
       DBPath path;
       QSqlDatabase db;
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(path.getPath());
       db.open();
       QSqlQuery q;
       //
       q.exec(sql);
       q.clear();
       db.close();

}
void setNewLimit(QString card, int amount){
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
    q.exec("UPDATE DEPOSIT_ACCOUNT set [limit]="+QString::number(amount)+" where account_number =" + card);
    q.clear();
    q.exec("UPDATE CREDIT_ACCOUNT set [limit]="+QString::number(amount)+" where account_number =" + card);
    q.clear();
    q.exec("UPDATE UNIVERSAL_ACCOUNT set [limit]="+QString::number(amount)+" where account_number =" + card);
    q.clear();
    db.close();
}
void unblockCard(QString card){
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    q.exec("UPDATE DEPOSIT_ACCOUNT set isBlocked=0 where account_number =" + card);
    q.clear();
    q.exec("UPDATE CREDIT_ACCOUNT set isBlocked=0   where account_number =" + card);
    q.clear();
    q.exec("UPDATE UNIVERSAL_ACCOUNT set isBlocked=0  where account_number =" + card);
    q.clear();
    db.close();
}
void blockCard(QString card){
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    q.exec("UPDATE DEPOSIT_ACCOUNT set isBlocked=1 where account_number =" + card);
    q.clear();
    q.exec("UPDATE CREDIT_ACCOUNT set isBlocked=1   where account_number =" + card);
    q.clear();
    q.exec("UPDATE UNIVERSAL_ACCOUNT set isBlocked=1  where account_number =" + card);
    q.clear();
    db.close();
}

void withdrawMoneyFromUniversalAccount(int amount, UniversalAccount& ua){
       QString card = ua.cardNumber();
       double sum = ua.sumOnBalance() - amount;
       ua.withdrawMoney(amount);
       //DB
       DBPath path;
       QSqlDatabase db;
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(path.getPath());
       db.open();
       QSqlQuery q;
       //
       q.exec("UPDATE UNIVERSAL_ACCOUNT set sum_on_balance ="+ QString::number(sum) + " where account_number =" + card);
       q.clear();
       db.close();
}

void withdrawMoneyFromCreditAccount(int amount, CreditAccount& ca){
    QString card = ca.cardNumber();
    double sum = ca.sumOnBalance() - amount;
    ca.withdrawMoney(amount);
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    q.exec("UPDATE CREDIT_ACCOUNT set sum_on_balance ="+ QString::number(sum) + " where account_number =" + card);
    q.clear();
    db.close();
}

void closeCredit(QString card){
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    q.exec("UPDATE CREDIT_ACCOUNT set credit_term = 0 where account_number = " + card);
    q.exec("UPDATE CREDIT_ACCOUNT set credit_debt = 0 where account_number = " + card);
    q.exec("UPDATE CREDIT_ACCOUNT set credit_expiry_date = '' where account_number = " + card);
    db.close();
}

void putMoneyOnCreditAccount(int amount, CreditAccount& ca){
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString card = ca.cardNumber();
    if(ca.creditDept() == 0){
        q.exec("UPDATE CREDIT_ACCOUNT set sum_on_balance ="+ QString::number(ca.sumOnBalance()+amount) + " where account_number =" + card); 
    }else{
        double sum = ca.creditDept() - amount;
        if(sum <= 0){
            closeCredit(card);
            if(sum < 0){
                        q.exec("UPDATE CREDIT_ACCOUNT set sum_on_balance ="+ QString::number(ca.sumOnBalance() - sum) + " where account_number =" + card);
                    }
        } else{
            q.exec("UPDATE CREDIT_ACCOUNT set credit_debt ="+ QString::number(sum) + " where account_number =" + card);
        }
    }
    ca.putMoney(amount);


    db.close();
}

void putMoneyOnUniversalAccount(int amount, UniversalAccount& ua){
       QString card = ua.cardNumber();
       double sum = ua.sumOnBalance() + amount;
       ua.putMoney(amount);
       //DB
       DBPath path;
       QSqlDatabase db;
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(path.getPath());
       db.open();
       QSqlQuery q;
       //

      q.exec("UPDATE UNIVERSAL_ACCOUNT set sum_on_balance ="+ QString::number(sum) + " where account_number =" + card);
        db.close();
}

void putMoneyOnDepositAccount(int amount, DepositAccount& da){
       QString card = da.cardNumber();
       double sum = da.sumOnBalance() + amount;
       da.putMoney(amount);
       //DB
       DBPath path;
       QSqlDatabase db;
       db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(path.getPath());
       db.open();
       QSqlQuery q;
       //
      q.exec("UPDATE DEPOSIT_ACCOUNT set sum_on_balance ="+ QString::number(sum) + " where account_number =" + card);
    db.close();
}

CreditAccount getCreditAccountByUserId(int id){
    QString strSql = "SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.user_id = "+QString::number(id);
    int userIdATM(0), sum(0), creditTerm(0), creditDebt(0),limit(0),isBlocked(0);
    QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), creditExpDate("");

    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
   // q.exec(strSql);
    bool exists = false;
        bool isBl;
        if(q.exec(strSql)){
        while (q.next()){
            exists=true;
            accountNumber=q.value(0).toString();
            pin = q.value(1).toString();
            expiryDate = q.value(2).toString();
            cvvNumber=q.value(3).toString();
            sum = q.value(4).toDouble();
            creditTerm=q.value(5).toInt();
            creditExpDate=q.value(6).toString();
            creditDebt=q.value(7).toInt();
            userIdATM=q.value(8).toInt();
            limit=q.value(9).toInt();
            isBlocked=q.value(10).toInt();
            isBl = isBlocked == 1 ? true : false;

        }
        if(exists){
            db.close();
            return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);

        }


    }else{
        qWarning("Sql Error");
    }
         db.close();
       return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);

}

DepositAccount getDepositAccountByUserId(int id){
    QString strSql = "SELECT * FROM DEPOSIT_ACCOUNT where user_id ="+ QString::number(id);
    QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), depositExpDate("");
    int userIdATM(0), sum(0), depositTerm(0),limit(0), isBlocked(0);
    double depositPerc(0.0);
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
   // bool exists = false;
        bool isBl;
    //q.exec(strSql);
  if(q.exec(strSql)){
while (q.next()){
   // exists=true;
    accountNumber=q.value(0).toString();
    pin = q.value(1).toString();
    expiryDate = q.value(2).toString();
    cvvNumber=q.value(3).toString();
    sum = q.value(4).toDouble();
    depositTerm=q.value(5).toInt();
    depositExpDate=q.value(6).toString();
    depositPerc=q.value(7).toDouble();
    userIdATM=q.value(8).toInt();
    isBlocked=q.value(9).toInt();
    limit=q.value(10).toInt();
    isBl = isBlocked == 1 ? true : false;
     db.close();
    return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);


}
}else{
qWarning("Sql Error");
}
 db.close();
return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);

}
DepositAccount getDepositAccountByCardAndPin(QString card, QString pinn){
        QString strSql = "SELECT * FROM DEPOSIT_ACCOUNT where account_number =" + card + " AND pin =" + pinn;
        QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), depositExpDate("");
        int userIdATM(0), sum(0), depositTerm(0),limit(0), isBlocked(0);
        double depositPerc(0.0);
        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
      //  bool exists = false;
            bool isBl;
      //  q.exec(strSql);
            qWarning("d1");
 if(q.exec(strSql)){
    while (q.next()){
        qWarning("d0");
        //exists=true;
        accountNumber=q.value(0).toString();
        pin = q.value(1).toString();
        expiryDate = q.value(2).toString();
        cvvNumber=q.value(3).toString();
        sum = q.value(4).toDouble();
        depositTerm=q.value(5).toInt();
        depositExpDate=q.value(6).toString();
        depositPerc=q.value(7).toDouble();
        userIdATM=q.value(8).toInt();
        isBlocked=q.value(9).toInt();
        limit=q.value(10).toInt();
        isBl = isBlocked == 1 ? true : false;
         db.close();
        return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);

    }

        qWarning("d2");
 db.close();
        return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);


}else{
qWarning("Sql Error");
}
  db.close();
    return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
}

DepositAccount getDepositAccountByCard(QString card){
        QString strSql = "SELECT * FROM DEPOSIT_ACCOUNT where account_number =" + card;
        QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), depositExpDate("");
        int userIdATM(0), sum(0), depositTerm(0),limit(0), isBlocked(0);
        double depositPerc(0.0);
        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
      //  bool exists = false;
            bool isBl;
      //  q.exec(strSql);
            qWarning("d1");
 if(q.exec(strSql)){
    while (q.next()){
        qWarning("d0");
        //exists=true;
        accountNumber=q.value(0).toString();
        pin = q.value(1).toString();
        expiryDate = q.value(2).toString();
        cvvNumber=q.value(3).toString();
        sum = q.value(4).toDouble();
        depositTerm=q.value(5).toInt();
        depositExpDate=q.value(6).toString();
        depositPerc=q.value(7).toDouble();
        userIdATM=q.value(8).toInt();
        isBlocked=q.value(9).toInt();
        limit=q.value(10).toInt();
        isBl = isBlocked == 1 ? true : false;
         db.close();
        return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);

    }

        qWarning("d2");
 db.close();
        return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);


}else{
qWarning("Sql Error");
}
  db.close();
    return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
}



UniversalAccount getUniversalAccountByCardAndPin(QString card, QString pinn){
        QString strSql = "SELECT * FROM UNIVERSAL_ACCOUNT where account_number = " + card + " AND pin = "+pinn;
        int userIdATM(0), sum(0), limit(0), isBlocked(0);
       // bool exists = false;
        QString accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
        bool isBl(true);

        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
        //q.exec(strSql);
        bool exists = false;
        qWarning("u1");

 if(q.exec(strSql)){
    while (q.next()){
       // exists=true;
        accountNumber=q.value(0).toString();
        pin = q.value(1).toString();
        expiryDate = q.value(2).toString();
        cvvNumber=q.value(3).toString();
        sum = q.value(4).toDouble();
        userIdATM=q.value(5).toInt();
        limit=q.value(6).toInt();
        isBlocked=q.value(7).toInt();
        isBl = isBlocked == 1 ? true : false;

    }
    if(exists){
         db.close();
        return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);

    }else{
        }


}else{
qWarning("Sql Error");
}
  db.close();
return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);

}




UniversalAccount getUniversalAccountByCard(QString card){
        QString strSql = "SELECT * FROM UNIVERSAL_ACCOUNT where account_number = " + card;
        int userIdATM(0), sum(0), limit(0), isBlocked(0);
       // bool exists = false;
        QString accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
        bool isBl(true);

        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
        //q.exec(strSql);
        bool exists = false;
        qWarning("u1");

 if(q.exec(strSql)){
    while (q.next()){
       // exists=true;
        accountNumber=q.value(0).toString();
        pin = q.value(1).toString();
        expiryDate = q.value(2).toString();
        cvvNumber=q.value(3).toString();
        sum = q.value(4).toDouble();
        userIdATM=q.value(5).toInt();
        limit=q.value(6).toInt();
        isBlocked=q.value(7).toInt();
        isBl = isBlocked == 1 ? true : false;

    }
    if(exists){
         db.close();
        return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);

    }else{
        }


}else{
qWarning("Sql Error");
}
  db.close();
return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);

}



CreditAccount getCreditAccountByCardAndPin(QString card, QString pinn){
    QString strSql = "SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card+" AND pin = "+pinn;
    int userIdATM(0), sum(0), creditTerm(0), creditDebt(0),limit(0),isBlocked(0);
    QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), creditExpDate("");

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
   // q.exec(strSql);
 //   bool exists = false;
        bool isBl;
        qWarning("c1");
 if(q.exec(strSql)){
        while (q.next()){
 //           exists=true;
            accountNumber=q.value(0).toString();
            pin = q.value(1).toString();
            expiryDate = q.value(2).toString();
            cvvNumber=q.value(3).toString();
            sum = q.value(4).toDouble();
            creditTerm=q.value(5).toInt();
            creditExpDate=q.value(6).toString();
            creditDebt=q.value(7).toInt();
            userIdATM=q.value(8).toInt();
            limit=q.value(9).toInt();
            isBlocked=q.value(10).toInt();
            isBl = isBlocked == 1 ? true : false;
             db.close();
 return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
        }
         db.close();
            return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);



    }else{
    qWarning("Sql Error");
    }
        return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
}

CreditAccount getCreditAccountByCard(QString card){
    QString strSql = "SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card;
    int userIdATM(0), sum(0), creditTerm(0), creditDebt(0),limit(0),isBlocked(0);
    QString accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), creditExpDate("");

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
   // q.exec(strSql);
 //   bool exists = false;
        bool isBl;
        qWarning("c1");
 if(q.exec(strSql)){
        while (q.next()){
 //           exists=true;
            accountNumber=q.value(0).toString();
            pin = q.value(1).toString();
            expiryDate = q.value(2).toString();
            cvvNumber=q.value(3).toString();
            sum = q.value(4).toDouble();
            creditTerm=q.value(5).toInt();
            creditExpDate=q.value(6).toString();
            creditDebt=q.value(7).toInt();
            userIdATM=q.value(8).toInt();
            limit=q.value(9).toInt();
            isBlocked=q.value(10).toInt();
            isBl = isBlocked == 1 ? true : false;
             db.close();
 return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
        }
         db.close();
            return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);



    }else{
    qWarning("Sql Error");
    }
        return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
}


UniversalAccount getUniversalAccountByUserId(int id){
    int userIdATM(0), sum(0), limit(0), isBlocked(0);
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
    QString strSQL = "SELECT * FROM UNIVERSAL_ACCOUNT where user_id =" +QString::number(id);
    QString accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
   // q.exec(strSQL);
   // bool exists = false;

        bool isBl;
 if(q.exec(strSQL)){
        while (q.next()){
            accountNumber=q.value(0).toString();
            pin = q.value(1).toString();
            expiryDate = q.value(2).toString();
            cvvNumber=q.value(3).toString();
            sum = q.value(4).toDouble();
            userIdATM=q.value(5).toInt();
            limit=q.value(6).toInt();
            isBlocked=q.value(7).toInt();
            isBl = isBlocked == 1 ? true : false;
     //       exists=true;
             db.close();
             return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);
        }



    }else{
    qWarning("Sql Error");
    }

  db.close();
 return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);
}
bool cardBlocked(QString card){
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
    if(q.exec("SELECT * FROM DEPOSIT_ACCOUNT where DEPOSIT_ACCOUNT.account_number = "+card+" AND isBlocked = 1")){
        if(q.next()){
             db.close();
             return true;
        }
    }

    if(q.exec("SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card+" AND isBlocked = 1")){
        if(q.next()){
             db.close();
             return true;
        }
    }

    if(q.exec("SELECT * FROM UNIVERSAL_ACCOUNT where UNIVERSAL_ACCOUNT.account_number = "+card+" AND isBlocked = 1")){
         if(q.next()){
              db.close();
              return true;
         }
    }
 db.close();
   return false;
}

void putMoneyOnAccountByCard(double amount, QString card) {
 if (cardExists(card)) {
  UniversalAccount ua = getUniversalAccountByCard(card);
  if (ua.cardNumber() != "") {
      qDebug("uuu");
   putMoneyOnUniversalAccount(amount, ua);
  }else {
   CreditAccount ca = getCreditAccountByCard(card);
   if (ca.cardNumber() != "") {
       qDebug("ccc");
    putMoneyOnCreditAccount(amount, ca);
   }else {
       qDebug("ddd");
    DepositAccount da = getDepositAccountByCard(card);
    putMoneyOnDepositAccount(amount, da);
   }
  }
 }
}



bool universalIsValid(UniversalAccount& ua){
    time_t now = time(0);
    char* dt1 = ctime(&now);
    if(isEarlierThan( ua.expiryDate(), dt1)){
        blockCard(ua.cardNumber());
        return false;
    }
    return true;
}

bool creditIsValid(CreditAccount& ca){
    time_t now = time(0);
        char* dt1 = ctime(&now);
        if(isEarlierThan( ca.expiryDate(), dt1) || (ca.creditExpiryDate() != "" && isEarlierThan( ca.creditExpiryDate(), dt1))){
            blockCard(ca.cardNumber());
                return false;
        }
        return true;
}

bool depositIsValid(DepositAccount& da){
    time_t now = time(0);
        char* dt1 = ctime(&now);
        if(isEarlierThan(da.expiryDate(), dt1)){
            blockCard(da.cardNumber());
                return false;
        }
        if(da.expiryDate()!="" && isEarlierThan(da.depositExpiryDate(),dt1)){
            closeDeposite(da);
        }
        return true;
}

void closeDeposite(DepositAccount& da){
    double sum = da.chargePercentageOfCost();
    putMoneyOnAccountByCard(sum,getUniversalAccountByUserId(selectUserByCard(da.cardNumber()).id()).cardNumber());
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    q.exec("UPDATE DEPOSIT_ACCOUNT set sum_on_balance ="+ QString::number(0) + " where account_number =" + da.cardNumber());
   q.clear();
   q.exec("UPDATE CREDIT_ACCOUNT set deposit_term = 0 where account_number = " + da.cardNumber());
      q.clear();
   q.exec("UPDATE CREDIT_ACCOUNT set deposit_percentage = 0.0 where account_number = " + da.cardNumber());
      q.clear();
   q.exec("UPDATE CREDIT_ACCOUNT set deposit_expiry_date = '' where account_number = " + da.cardNumber());
      q.clear();
      da.close();
    db.close();
}

bool cardExists(QString card) {
    //DB
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //
    if(q.exec("SELECT * FROM DEPOSIT_ACCOUNT where DEPOSIT_ACCOUNT.account_number = "+card)){
        if(q.next()){
             db.close();
             return true;
        }
    }

    if(q.exec("SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card)){
        if(q.next()){
             db.close();
             return true;
        }
    }

    if(q.exec("SELECT * FROM UNIVERSAL_ACCOUNT where UNIVERSAL_ACCOUNT.account_number = "+card)){
         if(q.next()){
              db.close();
             return true;
         }
    }
 db.close();
   return false;

}
