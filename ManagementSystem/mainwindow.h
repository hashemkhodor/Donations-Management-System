#pragma once

#include <QMainWindow>
#include<stack>
#include<vector>

enum windowtypes {mainWin, entranceWin, donationsWin ,peopleWin,donersWin};

class QAction;
class QMenu;
class QToolBar;
class QPushButton;
class QLabel;
class QGridLayout;
class MainWindow;
class QTreeWidget;



class OtherWindows : public QWidget{
    Q_OBJECT
public:
    MainWindow * parent;
    OtherWindows(){}
public:
    void setParent(MainWindow * parent=NULL){this->parent=parent;}
    virtual OtherWindows * createWindow(){return NULL;};
   // virtual QGridLayout * getLayout(){return NULL;};
   // virtual windowtypes getWindowType(){};
    QGridLayout * layout;

};

class mainWindow: public OtherWindows{
    Q_OBJECT ;
public:
    mainWindow(){};

private slots:
    void startHere();
private:
    virtual mainWindow * createWindow();
   // virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:

    QLabel * title;
    QLabel * subtitle;
    QPushButton * startHereButton;





};


class entranceWindow: public OtherWindows{
    Q_OBJECT;
public:
    entranceWindow( ){};
private slots:
    void viewDoners();
private:
    virtual entranceWindow * createWindow();
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
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;


};

class donersWindow: public OtherWindows{
    Q_OBJECT;
public:
    donersWindow(){};
private:
    virtual donersWindow * createWindow();
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
    std::vector <QPushButton *> buttons;
    std:: vector<QLabel *> labels;

    QTreeWidget * donersView;



};
class peopleWindow: public OtherWindows{
    Q_OBJECT;
public:
    peopleWindow( ){};
private:
    virtual peopleWindow * createWindow();
  //  virtual QGridLayout * getLayout();
   // virtual windowtypes getWindowType();
private:
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
    std:: stack <OtherWindows *> undos;
    std:: stack <OtherWindows *> redos;

    std:: vector <OtherWindows  *> windows;

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


    friend class OtherWindows;
    friend class mainWindow;
    friend class donersWindow;

};

