#pragma once
#include<QMainWindow>
#include<QtSql>
#include<QtWidgets>
#include<QString>
#include<stack>
#include<vector>
#include<QString>
#include<unordered_map>


using namespace std;
class QAction;
class QMenu;
class QToolBar;
class QPushButton;
class QLabel;
class QGridLayout;
class QTreeWidget;
class QSqlDatabase;
class QStackedWidget;
class QVBoxLayout;
class MainWindow;
class QDate;
class Human {
public:
    Human(){}


};


class Recipient:public Human{
    public:
    Recipient(long int id,QString fname, QString lname, QDate bday, int civ, QString Vill, QString Addr, QString phone, bool chron, QString comm="") {
        ID=id;
        f_name= fname;
        l_name=lname;
        birthdate= bday;
        civil_record_number= civ;
        Village = Vill;
        Address= Addr;
        phone_number= phone;
        chron_dis= chron;
        comments= comm;

    }


    public:
    long int ID;
    QString f_name;
    QString l_name;
    QDate birthdate;
    int civil_record_number;
    QString Village;
    QString Address;
    QString phone_number;
    bool chron_dis;
    QString comments;


};
