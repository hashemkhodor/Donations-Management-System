#pragma once
#include<otherwindows.h>

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

