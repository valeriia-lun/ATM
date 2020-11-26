
#include "TransactionDB.h"
#include "AccountsDB.h"

void createTransaction(int transactionSum, QString cardSourceNumber, QString cardDestinationNumber){
    Transaction transaction(transactionSum,cardSourceNumber,cardDestinationNumber,"",0);
     QString transactionDateTime = transaction.transactionDateTime();
        DBPath p;
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(p.getPath());
        db.open();
        QSqlQuery q;
        q.exec("INSERT INTO TRANSACTION_ATM (transaction_sum,transaction_date_time,source_account_number, destination_account_number)"
               " VALUES('"  + QString::number(transactionSum) + "', '" + transactionDateTime + "', '" + cardSourceNumber + "', '"+ cardDestinationNumber+"')");
         db.close();
}
void makeTransactionFromCreditToAnother(CreditAccount& ca, QString cardDest, int amount){
    createTransaction(amount,ca.cardNumber(),cardDest);
    //

   withdrawMoneyFromCreditAccount(amount,ca);
    //
}

void makeTransactionFromUniversalToAnother(UniversalAccount& ua, QString cardDest, int amount){
    createTransaction(amount,ua.cardNumber(),cardDest);
      //

      withdrawMoneyFromUniversalAccount(amount,ua);
      //
}

void makeTransactionFromCreditToUniversal(CreditAccount& ca, UniversalAccount& ua, int amount){
    createTransaction(amount,ca.cardNumber(),ua.cardNumber());
    //

    withdrawMoneyFromCreditAccount(amount,ca);
    putMoneyOnUniversalAccount(amount,ua);
    //
}
void makeTransactionFromCreditToCredit(CreditAccount& ca, CreditAccount& ca2, int amount){
    createTransaction(amount,ca.cardNumber(),ca2.cardNumber());
    //

    withdrawMoneyFromCreditAccount(amount,ca);
    putMoneyOnCreditAccount(amount,ca2);
}
void makeTransactionFromUniversalToUniversal(UniversalAccount& ua, UniversalAccount& ua2, int amount){
    createTransaction(amount,ua.cardNumber(),ua2.cardNumber());
    //

    withdrawMoneyFromUniversalAccount(amount,ua);
   putMoneyOnUniversalAccount(amount,ua2);
}
void makeTransactionFromCreditToDeposit(CreditAccount& ca, DepositAccount& da, int amount){
    createTransaction(amount,ca.cardNumber(),da.cardNumber());
    //

    withdrawMoneyFromCreditAccount(amount,ca);
    putMoneyOnDepositAccount(amount,da);
    //
}

void makeTransactionFromUniversalToCredit(UniversalAccount& ua, CreditAccount& ca, int amount){
    createTransaction(amount,ua.cardNumber(),ca.cardNumber());
    //

   withdrawMoneyFromUniversalAccount(amount,ua);
   putMoneyOnCreditAccount(amount,ca);
    //
}

void makeTransactionFromUniversalDeposit(UniversalAccount& ua, DepositAccount& da, int amount){
    createTransaction(amount,ua.cardNumber(),da.cardNumber());
    //

   withdrawMoneyFromUniversalAccount(amount,ua);
   putMoneyOnDepositAccount(amount,da);
    //
}

void getAllTransactions(){
    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
    bool exists = false;
    QString sql("SELECT * FROM TRANSACTION_ATM");
     q.exec(sql);
    while (q.next()){
            exists=true;
        }
    if ( !exists )
           {
            QMessageBox::warning(NULL, QObject::tr("Error"),
                                       QObject::tr("No transactions\n"),QMessageBox::Cancel);}

}

void getAllTransactionsByCard(QString card){
       DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
     bool exists = false;
    QString sql("SELECT * FROM TRANSACTION_ATM WHERE source_account_number = " + card + " OR destination_account_number = " + card);
    q.exec(sql);
    while (q.next()){
            exists=true;
        }
        if ( !exists )
           {
            QMessageBox::warning(NULL, QObject::tr("Error"),
                                       QObject::tr("No transactions\n"),QMessageBox::Cancel);}

}

