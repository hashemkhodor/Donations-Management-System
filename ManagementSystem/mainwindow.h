#pragma once

#include <QMainWindow>
#include<QtSql>
#include<QtWidgets>
#include<QString>
#include<stack>
#include<vector>
#include<QString>
#include<unordered_map>
using namespace std;

enum windowtypes {mainWin, entranceWin, donationsWin ,peopleWin,donersWin,addPeopleWin,addDonationWin};

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

public :
     QString button_css= QString("QPushButton{"
                                 "background-color: #2ea44f;"
                                 "border: 1px solid rgba(27, 31, 35, .15);"
                                 "border-radius: 6px;"
                                 "color: #fff;"
                                 "font-family: -apple-system,system-ui,'Segoe UI','Helvetica','Arial','sans-serif','Apple Color Emoji','Segoe UI Emoji';"
                                 "font-size: 14px;"
                                 "font-weight: 600;"
                                 "line-height: 20px;"
                                 "padding: 6px 16px;"
                                 "position: relative;"
                                 "text-align: center;"
                                 "text-decoration: none;"
                                 "vertical-align: middle;"
                                 "white-space: nowrap;}"
                                 "QPushButton:hover {"
                                 "    background-color: lightgreen;"
                                 "}");
;


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
    void addDonations();
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
   void viewAct();
   void addAct();

public:
    virtual AddPeopleWindow * createWindow();
    virtual AddPeopleWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return addPeopleWin;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    QFormLayout * add_People;
    QHBoxLayout * buttons_layout;

    QLabel * name;
    QLabel * birthdate;
    QLabel * civil_record_num;
    QLabel * village;
    QLabel * address;
    QLabel * phone_number;
    QLabel * chronic_disease;
    QLabel * comments;
    QLabel * submit;


    QLineEdit * name_edit;
    QDateEdit * birthdate_edit;
    QLineEdit * civil_record_num_edit;
    QComboBox * village_edit;
    QLineEdit * address_edit;
    QLineEdit * phone_number_edit;
    QComboBox * chronic_disease_edit;
    QTextEdit * comments_edit;

    QPushButton * add_button;
    QPushButton * view_button;
    QPushButton * submit_button;







};

class AddDonationWindow: public OtherWindows{
  Q_OBJECT;
   public:
   AddDonationWindow(){WindowType="AddDonationWindow";setParent(0);}

public slots:
   void editsuggestedAct(){};
   void viewsuggestedAct(){};
   void adddonationAct(){};

public:
    virtual AddDonationWindow * createWindow();
    virtual AddDonationWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return donationsWin;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
public:
    QFormLayout * add_Donation;
    QFormLayout * conditions_layout;
    QHBoxLayout * buttons_layout;
    QHBoxLayout * donation_type_layout;
    QHBoxLayout * donor_layout;

    QLabel * name;
    QLabel * donation_type;
    QLabel * donor;
    QLabel * num_recipients;
    QLabel * pre_requistes;
        QLabel * num_people_house;
        QLabel * chronic_dis;
        QLabel * village;
        QLabel * nationality;
    QLabel * date;
    QLabel * buttons_label;
    QLabel * comments;


    QLineEdit * name_edit;
    QComboBox * donation_type_edit1;
    QLineEdit * donation_type_edit2;
    QComboBox * donor_edit1;
    QLineEdit * donor_edit2;
    QSpinBox * num_recipients_edit;
        QSpinBox * num_people_house_edit;
        QComboBox * chronic_dis_edit;
        QComboBox * village_edit;
        QComboBox * nationality_edit;

    QDateEdit * date_edit;

    QPushButton * add_donation_button;
    QPushButton * view_suggested_button;
    QPushButton * edit_suggested_button;

    QTextEdit * comments_edit;







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


    //StyleSheets:
    QString button_css;

    friend class OtherWindows;
    friend class mainWindow;
    friend class donersWindow;

};

