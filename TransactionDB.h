#ifndef TRANSACTIONDB_H
#define TRANSACTIONDB_H
#pragma once
#include "ATMdata/ATMHeaders/Transaction.h"
#include "ATMdata/ATMHeaders/accounts/CreditAccount.h"
#include "ATMdata/ATMHeaders/accounts/DepositAccount.h"
#include "ATMdata/ATMHeaders/accounts/UniversalAccount.h"
#include <QMessageBox>
#include "DBPath.h"
class TransactionDB{
public:
    void createTransaction(int transactionSum, QString cardSourceNumber, QString cardDestinationNumber);

    void makeTransactionFromCreditToAnother(CreditAccount& ca, QString cardDest, int amount);

    void makeTransactionFromUniversalToAnother(UniversalAccount& ua, QString cardDest, int amount);

    void makeTransactionFromCreditToUniversal(CreditAccount& ca, UniversalAccount& ua, int amount);
    void makeTransactionFromCreditToCredit(CreditAccount& ca, CreditAccount& ca2, int amount);
    void makeTransactionFromUniversalToUniversal(UniversalAccount& ua, UniversalAccount& ua2, int amount);
    void makeTransactionFromCreditToDeposit(CreditAccount& ca, DepositAccount& da, int amount);

    void makeTransactionFromUniversalToCredit(UniversalAccount& ua, CreditAccount& ca, int amount);

    void makeTransactionFromUniversalDeposit(UniversalAccount& ua, DepositAccount& da, int amount);

    void getAllTransactions();

    void getAllTransactionsByCard(QString card);
};



#endif // TRANSACTIONDB_H
