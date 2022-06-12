#pragma once

#include <QMainWindow>
#include<QtSql>
#include<QtWidgets>
#include<stack>
#include<vector>
#include<unordered_map>
using namespace std;


enum windowtypes {mainWin, entranceWin, donationsWin ,peopleWin,donersWin,addPeopleWin};

class QAction;
class QMenu;
class QToolBar;
class QPushButton;
class QLabel;
class QGridLayout;
class MainWindow;
class QTreeWidget;
class QSqlDatabase;
class QStackedWidget;
class QVBoxLayout;

class Recipient{
    public:
    Recipient(long int id, QString name, QString b_date, bool c_disease, QString addr, long int number, int rec_number){
        ID=id; this->name=name;birthdate= b_date;chronic_disease=c_disease;address=addr;phone_number=number;civil_record_number=rec_number;

    }

    private:
    long int ID;
    QString name;
    QString birthdate;
    bool chronic_disease;
    QString address;
    long int phone_number;
    int civil_record_number;


};
class OtherWindows : public QWidget{
    Q_OBJECT
public:
    MainWindow * parentt;
    OtherWindows(){WindowType="OtherWindows";setParent(0);}
public:
    void set_Parent(MainWindow * parentt=NULL){this->parentt=parentt;}
    virtual OtherWindows * createWindow()=0;
    virtual QWidget * getCentralWidget()=0;
    virtual windowtypes getWindowType()=0;
    QGridLayout * layout;
    QString WindowType;

};

class mainWindow: public OtherWindows{
    Q_OBJECT ;
public:
    mainWindow(){ WindowType="MainWindow";setParent(0);};


public slots:
    void startHere();
public:
    virtual mainWindow * createWindow();
    virtual mainWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return mainWin;};
   // virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:

    QLabel * title;
    //QLabel * subtitle;
    QPushButton * startHereButton;
    QVBoxLayout * layout;
};


struct entranceWindow: public OtherWindows{
    Q_OBJECT;
public:
    entranceWindow( ){WindowType="EntranceWindow";setParent(0);};

 public slots:
    void viewDoners();
    void viewDonations();
    void addPeople();
public:
    virtual entranceWindow * createWindow();
    virtual entranceWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return entranceWin;};
public:
    QLabel * donations;
    QLabel * people;
    QLabel * doners;

    // Under the donations Cluster
    QPushButton * viewOldDonations;
    QPushButton * viewUpcomingDonations;
    QPushButton * addNewDonations;

    //Under the people Cluster
    QPushButton * viewAllPeople;
    QPushButton * viewPrioritizedPeople;
    QPushButton * addNewPeople;

    //Under the doners cluster
    QPushButton * viewdoners;
    QPushButton * seePercentage;
    QPushButton * addUnexpected;

};




class donationsWindow: public OtherWindows{
    Q_OBJECT;
public:
    donationsWindow( ){WindowType="donationsWindow";setParent(0);};
public:
    virtual donationsWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return donationsView;};
    virtual windowtypes getWindowType(){return donationsWin;};

  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    QTreeWidget * donationsView;
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;


};

class donersWindow: public OtherWindows{
    Q_OBJECT;
public:
    donersWindow(){WindowType="donerWindow";setParent(0);};
public:
    virtual donersWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return donersView;};
    virtual windowtypes getWindowType(){return donersWin;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;


    QTreeWidget * donersView;



};

class AddPeopleWindow: public OtherWindows{
  Q_OBJECT;
   public:
   AddPeopleWindow(){WindowType="AddPeopleWindow";setParent(0);}

public slots:
   void submitAct();

public:
    virtual AddPeopleWindow * createWindow();
    virtual AddPeopleWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return donersWin;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    QFormLayout * add_People;

    QLabel * name;
    QLabel * birthdate;
    QLabel * civil_record_num;
    QLabel * address;
    QLabel * phone_number;
    QLabel * chronic_disease;
    QLabel * comments;
    QLabel * submit;


    QLineEdit * name_edit;
    QDateEdit * birthdate_edit;
    QLineEdit * civil_record_num_edit;
    QLineEdit * address_edit;
    QLineEdit * phone_number_edit;
    QComboBox * chronic_disease_edit;
    QTextEdit * comments_edit;
    QPushButton * submit_button;







};
class peopleWindow: public OtherWindows{
    Q_OBJECT;
public:
    peopleWindow( ){WindowType="PeopleWindow";setParent(0);};
public:
    virtual peopleWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return peopleView;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    QTreeWidget * peopleView;
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
public:
    OtherWindows * changeWindow(windowtypes w);
public slots:
    void connectFile();
    void newFile();

    void Tutorial();


    void redo();
    void undo();

public:

    void createMenuBar();
    void createToolBar();
    void createActions();
    void createStatusBar();
    void createTreeWidget();

    void createMainWindow();
    void createEntranceWindow();
    void createDonationsWindow();
    void createPeoplesWindow();

public:
    stack<windowtypes> windows;

    stack<OtherWindows *> Windows;


    mainWindow * main_Window;
    entranceWindow * entrance_Window;
    donersWindow * doners_Window;

    unordered_map<windowtypes,OtherWindows *> W_Windows;


    QAction * connectAct;
    QAction * newAct;

    QAction * tutorialAct;

    QAction * undoAct;
    QAction * redoAct;

    OtherWindows * currentWindow=NULL;
    OtherWindows * prevWindow=NULL;

    QMenu * file;
    QMenu * view;
    QMenu * help;

    QToolBar * mainToolBar ;

    QString DataBaseName;

    QSqlDatabase db;
    QSqlQuery query;


    friend class OtherWindows;
    friend class mainWindow;
    friend class donersWindow;

};

