#include "mainwindow.h"

#include <QApplication>
#include "SessionManager.h"
#include <QDir>
#include <QDebug>
#include <QStandardPaths>

//void testing(){

//     qWarning( "STARTED***************************************" );
//    UniversalAccount universalAccount = getUniversalAccountByCardAndPin("8886", "234");
//     DepositAccount depositAcount = adb.getDepositAccountByCardAndPin("2355", "111");
//     CreditAccount creditAcount = adb.getCreditAccountByCardAndPin("7777", "111");
//     TransactionDB tdb;

//     //testing limit
//     int newLimit = 1000;
//     universalAccount.limit() = newLimit;
//     adb.setNewLimit(universalAccount.cardNumber(), newLimit);
//     assert(newLimit == universalAccount.limit());

//     //testing blocking
//     int isBlockedChanged = true;
//     depositAcount.isBlocked() = isBlockedChanged;
//     adb.blockCard(depositAcount.cardNumber());
//     assert(isBlockedChanged == depositAcount.isBlocked());

//     //testing putting money on Universal Account
//     double oldAmount = universalAccount.sumOnBalance();
//     double amount = 100;
//     adb.putMoneyOnUniversalAccount(amount, universalAccount);
//     double newAmount = oldAmount + amount;
//     assert(newAmount == universalAccount.sumOnBalance());

//     //testing putting money on Deposit Account
//     oldAmount = depositAcount.sumOnBalance();
//     amount = 100;
//     adb.putMoneyOnDepositAccount(amount, depositAcount);
//     newAmount = oldAmount + amount;
//     assert(newAmount == depositAcount.sumOnBalance());

//     //testing withdrawing money from Universal Account
//     oldAmount = universalAccount.sumOnBalance();
//     amount = 100;
//     adb.withdrawMoneyFromUniversalAccount(amount, universalAccount);
//     newAmount = oldAmount - amount;
//     assert(newAmount == universalAccount.sumOnBalance());

//     //testing withdrawing money from Credit Account
//     oldAmount = creditAcount.sumOnBalance();
//     amount = 100;
//     adb.withdrawMoneyFromCreditAccount(amount, creditAcount);
//     newAmount = oldAmount - amount;
//     assert(newAmount == creditAcount.sumOnBalance());

//     //testing Transaction from Universal To Deposit
//     amount = 100;
//     double oldAmountOnDeposit = depositAcount.sumOnBalance();
//     double oldAmountOnUniversal = universalAccount.sumOnBalance();
//     tdb.makeTransactionFromUniversalDeposit(universalAccount, depositAcount, amount);
//     double newAmountOnUniversal5 = oldAmountOnUniversal - amount;
//     assert(newAmountOnUniversal5 == universalAccount.sumOnBalance());
//     double newAmountOnDeposit5 = oldAmountOnDeposit + amount;
//     assert(newAmountOnDeposit5 == depositAcount.sumOnBalance());

//     //testing Transaction from Universal To Credit
//     amount = 100;
//     double oldDeptOnCredit6 = creditAcount.creditDept();
//     double oldAmountOnUniversal6 = universalAccount.sumOnBalance();
//     tdb.makeTransactionFromUniversalToCredit(universalAccount, creditAcount, amount);
//     double newAmountOnUniversal6 = oldAmountOnUniversal6 - amount;
//     assert(newAmountOnUniversal6 == universalAccount.sumOnBalance());
//     double newDeptOnCredit6 = oldDeptOnCredit6 - amount;
//     assert(newDeptOnCredit6 == creditAcount.creditDept());

//     //testing Transaction from Universal To Another account
//     amount = 300;
//     double oldAmountOnUniversal7 = universalAccount.sumOnBalance();
//     double newAmountOnUniversal7 = oldAmountOnUniversal7 - amount;
//     tdb.makeTransactionFromUniversalToAnother(universalAccount, "9999", amount);
//     assert(newAmountOnUniversal7 == universalAccount.sumOnBalance());

//     //testing Transaction from Credit To Universal
//     amount = 100;
//     double oldAmountOnCredit6 = creditAcount.sumOnBalance();
//     oldAmountOnUniversal6 = universalAccount.sumOnBalance();
//     tdb.makeTransactionFromCreditToUniversal(creditAcount,universalAccount,  amount);
//     newAmountOnUniversal6 = oldAmountOnUniversal6 + amount;
//     assert(newAmountOnUniversal6 == universalAccount.sumOnBalance());
//     double newAmountOnCredit6 = oldAmountOnCredit6 - amount;
//     assert(newAmountOnCredit6 == creditAcount.sumOnBalance());

//     //testing Transaction from Credit To Deposit
//     amount = 100;
//     oldAmountOnCredit6 = creditAcount.sumOnBalance();
//     oldAmountOnDeposit = depositAcount.sumOnBalance();
//     tdb.makeTransactionFromCreditToDeposit(creditAcount,depositAcount,  amount);
//     double newAmountOnDeposit = oldAmountOnDeposit + amount;
//     assert(newAmountOnDeposit == depositAcount.sumOnBalance());
//     newAmountOnCredit6 = oldAmountOnCredit6 - amount;
//     assert(newAmountOnCredit6 == creditAcount.sumOnBalance());

//      qWarning( "FINISHED***************************************" );
//}
int main(int argc, char *argv[])
{
   // testing();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
