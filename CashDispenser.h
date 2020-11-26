/*#ifndef CASHDISPENSER_H
#define CASHDISPENSER_H
#include <QMessageBox>
#include <QMap>
class SessionManager;
class CashDispenser{
private:
    SessionManager& _sm;
    int _totalCashAmount;
  QMap<int,int> _notesMap;
  bool _success;
 public:
    CashDispenser(SessionManager&);
    ~CashDispenser(){}
    bool has50(int x = 0) { return _notesMap[50] - x > 0; }
    bool has100(int x = 0) { return _notesMap[100] - x > 0; }
    bool has200(int x = 0) { return _notesMap[200] - x > 0; }
    bool has500(int x = 0) { return _notesMap[500] - x > 0; }
    void initialiseNotes();
    void setTotalCashAmount();
    void calculateNotesOut(int);
    void updateNotesMap(QMap<int, int>);
    void incashMoney(int);
     QMap<int, int> getNotesOut( int);
     QMap<int, int> getMap() { return _notesMap; }
     int getTotalCash(){return _totalCashAmount;}
     bool isSuccess(){return _success;}
};


#endif // CASHDISPENSER_H
*/
