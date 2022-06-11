#pragma once

#include <QMainWindow>
#include<QtSql>
#include<QtWidgets>
#include<stack>
#include<vector>


enum windowtypes {no,mainWin, entranceWin, donationsWin ,peopleWin,donersWin};

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


class OtherWindows : public QWidget{
    Q_OBJECT
public:
    MainWindow * parent;
    OtherWindows(){}
public:
    void setParent(MainWindow * parent=NULL){this->parent=parent;}
    virtual OtherWindows * createWindow(){return NULL;};
    virtual QWidget * getCentralWidget(){return NULL;};
    virtual windowtypes getWindowType(){return no;};
   // virtual QGridLayout * getLayout(){return NULL;};
   // virtual windowtypes getWindowType(){};
    QGridLayout * layout;
    QString WindowType;

};

class mainWindow: public OtherWindows{
    Q_OBJECT ;
public:
    mainWindow(){};
    QString WindowType="MainWindow";

private slots:
    void startHere();
private:
    virtual mainWindow * createWindow();
    virtual mainWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return mainWin;};
   // virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:

    QLabel * title;
    //QLabel * subtitle;
    QPushButton * startHereButton;
    QVBoxLayout * layout;





};


class entranceWindow: public OtherWindows{
    Q_OBJECT;
public:
    entranceWindow( ){};
    QString WindowType="EntranceWindow";
private slots:
    void viewDoners();
    void viewDonations();
private:
    virtual entranceWindow * createWindow();
    virtual entranceWindow * getCentralWidget(){return this;};
    virtual windowtypes getWindowType(){return entranceWin;};
   // virtual QGridLayout * getLayout();
    //virtual windowtypes getWindowType();
private:
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
    donationsWindow( ){};
private:
    virtual donationsWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return donationsView;};
    virtual windowtypes getWindowType(){return donationsWin;};

  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
    QString WindowType="donationsWindow";
    QTreeWidget * donationsView;
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;


};

class donersWindow: public OtherWindows{
    Q_OBJECT;
public:
    donersWindow(){};
private:
    virtual donersWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return donersView;};
    virtual windowtypes getWindowType(){return donersWin;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
    QString WindowType="donerWindow";
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;

    QTreeWidget * donersView;



};
class peopleWindow: public OtherWindows{
    Q_OBJECT;
public:
    peopleWindow( ){};
    QString WindowType="PeopleWindow";
private:
    virtual peopleWindow * createWindow();
    virtual QTreeWidget * getCentralWidget(){return peopleView;};
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
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
protected slots:
    void connectFile();
    void newFile();

    void Tutorial();


    void redo();
    void undo();

private:

    void createMenuBar();
    void createToolBar();
    void createActions();
    void createStatusBar();
    void createTreeWidget();

    void createMainWindow();
    void createEntranceWindow();
    void createDonationsWindow();
    void createPeoplesWindow();

private:
    int i=-1;
    std:: stack <OtherWindows *> undos;
    std:: stack <OtherWindows *> redos;


    std:: vector <OtherWindows *> windows;

    QStackedWidget * widgets;

    QAction * connectAct;
    QAction * newAct;

    QAction * tutorialAct;

    QAction * undoAct;
    QAction * redoAct;

    OtherWindows * currentWindow;

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

