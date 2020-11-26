@@ -0,0 +1,581 @@
#include "AccountsDB.h"
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
}

void putMoneyOnCreditAccount(int amount, CreditAccount& ca){
    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString card = ca.cardNumber();
    ca.putMoney(amount);
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
   // bool exists = false;
        bool isBl;
        if(q.exec(strSql)){
        while (q.next()){
          //  exists=true;
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
        QMessageBox::warning(NULL, QObject::tr("Error"),
                                                  QObject::tr("Account not found\n"),QMessageBox::Cancel);

    }else{
        qWarning("Sql Error");
    }
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

}        QMessageBox::warning(NULL, QObject::tr("Error"),
                              QObject::tr("Account not found\n"),QMessageBox::Cancel);

}else{
qWarning("Sql Error");
}

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
 if(q.exec(strSql)){
    while (q.next()){
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

    }
    QMessageBox::warning(NULL, QObject::tr("Error"),
                            QObject::tr("Account not found\n"),QMessageBox::Cancel);

}else{
qWarning("Sql Error");
}
    return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
}

UniversalAccount getUniversalAccountByCardAndPin(QString card, QString pinn){
        QString strSql = "SELECT * FROM UNIVERSAL_ACCOUNT where account_number = " + card + " AND pin = "+pinn;
        int userIdATM(0), sum(0), limit(0), isBlocked(0);
       // bool exists = false;
        QString accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
        bool isBl;

        //DB
        DBPath path;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.getPath());
        db.open();
        QSqlQuery q;
        //
        //q.exec(strSql);
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
    QMessageBox::warning(NULL, QObject::tr("Error"),
                            QObject::tr("Account not found\n"),QMessageBox::Cancel);

}else{
qWarning("Sql Error");
}
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

        }
        QMessageBox::warning(NULL, QObject::tr("Error"),
                                QObject::tr("Account not found\n"),QMessageBox::Cancel);

    }else{
    qWarning("Sql Error");
    }
        return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
}
//CreditAccount getCreditByCard(QString card){
//    QString strSql = "SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card;
//    int userIdATM(0), sum(0), creditTerm(0), creditDebt(0),limit(0),isBlocked(0);
//    QString accountNumber, pin, expiryDate, cvvNumber, creditExpDate;

//    //DB
//    DBPath path;
//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(path.getPath());
//    db.open();
//    QSqlQuery q;
//    //
//    bool isBl;
//    q.exec(strSql);
//        while (q.next()){
//            accountNumber=q.value(0).toString();
//            pin = q.value(1).toString();
//            expiryDate = q.value(2).toString();
//            cvvNumber=q.value(3).toString();
//            sum = q.value(4).toDouble();
//            creditTerm=q.value(5).toInt();
//            creditExpDate=q.value(6).toString();
//            creditDebt=q.value(7).toInt();
//            userIdATM=q.value(8).toInt();
//            limit=q.value(9).toInt();
//            isBlocked=q.value(10).toInt();
//            isBl = isBlocked == 1 ? true : false;
//        }
//        return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
//}

//UniversalAccount getUniversalByCard(QString card){
//    QString strSql = "SELECT * FROM UNIVERSAL_ACCOUNT where account_number = " + card;
//    int userIdATM(0), sum(0), limit(0), isBlocked(0);
//    QString accountNumber, pin, expiryDate, cvvNumber;
//    bool isBl;

//    //DB
//    DBPath path;
//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(path.getPath());
//    db.open();
//    QSqlQuery q;
//    //
//    q.exec(strSql);

//while (q.next()){
//    accountNumber=q.value(0).toString();
//    pin = q.value(1).toString();
//    expiryDate = q.value(2).toString();
//    cvvNumber=q.value(3).toString();
//    sum = q.value(4).toDouble();
//    userIdATM=q.value(5).toInt();
//    limit=q.value(6).toInt();
//    isBlocked=q.value(7).toInt();
//    isBl = isBlocked == 1 ? true : false;
//}

//return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);

//}

//DepositAccount getDepositByCard(QString card){
//    QString strSql = "SELECT * FROM DEPOSIT_ACCOUNT where account_number =" + card;
//    QString accountNumber, pin, expiryDate, cvvNumber, depositExpDate;
//    int userIdATM(0), sum(0), depositTerm(0),limit(0), isBlocked(0);
//    double depositPerc(0.0);
//    //DB
//    DBPath path;
//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(path.getPath());
//    db.open();
//    QSqlQuery q;
//    //
//    bool isBl;
//    q.exec(strSql);

//while (q.next()){
//    //exists=true;
//    accountNumber=q.value(0).toString();
//    pin = q.value(1).toString();
//    expiryDate = q.value(2).toString();
//    cvvNumber=q.value(3).toString();
//    sum = q.value(4).toDouble();
//    depositTerm=q.value(5).toInt();
//    depositExpDate=q.value(6).toString();
//    depositPerc=q.value(7).toDouble();
//    userIdATM=q.value(8).toInt();
//    isBlocked=q.value(9).toInt();
//    limit=q.value(10).toInt();
//    isBl = isBlocked == 1 ? true : false;

//}
//return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
//}

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
        }
        QMessageBox::warning(NULL, QObject::tr("Error"),
                                QObject::tr("Account not found\n"),QMessageBox::Cancel);

    }else{
    qWarning("Sql Error");
    }

 return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);
}
bool cardBlocked(QString card){
    bool blocked = false;
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
             blocked = true;
        }
    }

    if(q.exec("SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card+" AND isBlocked = 1")){
        if(q.next()){
             blocked = true;
        }
    }

    if(q.exec("SELECT * FROM UNIVERSAL_ACCOUNT where UNIVERSAL_ACCOUNT.account_number = "+card+" AND isBlocked = 1")){
         if(q.next()){
              blocked = true;
         }
    }

   return blocked;
}
bool cardExists(QString card) {
    bool exists = false;
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
             exists = true;
        }
    }

    if(q.exec("SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = "+card)){
        if(q.next()){
             exists = true;
        }
    }

    if(q.exec("SELECT * FROM UNIVERSAL_ACCOUNT where UNIVERSAL_ACCOUNT.account_number = "+card)){
         if(q.next()){
              exists = true;
         }
    }

   return exists;

}
