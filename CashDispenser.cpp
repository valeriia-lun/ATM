
/*#include "CashDispenser.h"
CashDispenser::CashDispenser(SessionManager& sm)
        : _sm(sm) {
    initialiseNotes();
}
 void CashDispenser::incashMoney(int n){
     if(n!=50 && n!=100 && n!=200 && n!=500){
             _success=false;
              QMessageBox::warning(NULL, QObject::tr("Error"),
                                         QObject::tr("Wrong banknote! Try again!"),QMessageBox::Cancel);
         }else{
         _notesMap[n]++;
          setTotalCashAmount();
          QMessageBox msgBox;
          QString a="Done successfuly!\n";
          _success=true;
          msgBox.setText(a);
          msgBox.exec();
     }

 }




 void CashDispenser::initialiseNotes(){
   _notesMap[50] = 100;
    _notesMap[100] = 100;
    _notesMap[200] = 100;
    _notesMap[500] = 100;
     setTotalCashAmount();
 }
 void CashDispenser::setTotalCashAmount(){
     int total = 0;
     total += _notesMap[50] * 50;
     total += _notesMap[100] * 100;
     total += _notesMap[200] * 200;
     total += _notesMap[500] * 500;
    _totalCashAmount=total;
 }
 void CashDispenser::calculateNotesOut(int m){
     _success=false;
     QMap<int, int> cashOutMap;
     if (m % 50 != 0) {
         {
          QMessageBox::warning(NULL, QObject::tr("Error"),
                                     QObject::tr("Enter amount that is divisible by 50\n"),QMessageBox::Cancel);
         }
     }else if(m < 50){
         QMessageBox::warning(NULL, QObject::tr("Error"),
                                    QObject::tr("Amount is too small!\n"),QMessageBox::Cancel);
     }
  else if(m >= _totalCashAmount){
         QMessageBox::warning(NULL, QObject::tr("Error"),
                                    QObject::tr("ATM hasn`t enough money!\n"),QMessageBox::Cancel);
     }
     else {
         int n = m;
         int _50(0),
             _100(0),
             _200(0),
             _500(0);
         while (n >= 500 && has500(_500)) {
             _500++;
             n -= 500;
         }
         if (_500 > 0 && n % 200 != 0 && !has100()) {
             _500--;
             n += 500;
         }
         while (n >= 200 && has200(_200)) {
             _200++;
             n -= 200;
         }
         while (n >= 100 && has100(_100)) {
             _100++;
             n -= 100;
         }
         while (n >= 50 && has50(_50)) {
             _50++;
             n -= 50;
         }

         if (n != 0) {
             {
              QMessageBox::warning(NULL, QObject::tr("Error"),
                                         QObject::tr("ATM hasn't required set of banknotes!\n"),QMessageBox::Cancel);}
         }
         else {
             _success=true;
             cashOutMap[50] = _50;
             cashOutMap[100] = _100;
             cashOutMap[200] = _200;
             cashOutMap[500] = _500;
             QMessageBox msgBox;
             QString a="Done successfuly!\nYour set of banknotes:\n";
             QString f="";
             QString h="";
             QString t="";
             QString fi="";
             if(_50!=0){
                   f="\n50$ : "+QString::number(_50);
             }
             if(_100!=0){
                   h="\n100$ : "+QString::number(_100);
             }
             if(_200!=0){
                   t="\n200$ : "+QString::number(_200);
             }
             if(_500!=0){
                   fi="\n500$ : "+QString::number(_500);
             }

             a=a+f+h+t+fi;
             msgBox.setText(a);
             msgBox.exec();
             updateNotesMap(cashOutMap);
             setTotalCashAmount();

         }
     }
 }
 void CashDispenser::updateNotesMap(QMap<int, int> m){
     _notesMap[50] = _notesMap[50] - m[50];
         _notesMap[100] = _notesMap[100] - m[100];
         _notesMap[200] = _notesMap[200] - m[200];
        _notesMap[500] = _notesMap[500] - m[500];


 }

*/
