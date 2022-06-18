#include<QtWidgets>
#include<QtSql>
#include<QtDebug>
#include <QSpacerItem>
#include <typeinfo>
#include "mainwindow.h"




MainWindow::MainWindow(){
    createActions();
    createMenuBar();
    createToolBar();
    createStatusBar();
    changeWindow(mainWin);
    //changeWindow(entranceWin);

}

void MainWindow:: createActions(){
    //File Menu Actions
    // // connect to an existing database
    connectAct= new QAction(tr("&Connect"),this);
    connectAct->setStatusTip("Connect an existing database (.db)");
    connect(connectAct, SIGNAL(triggered()),this,SLOT(connectFile()));

    // // Create an existing database
    newAct=  new QAction(tr("&New"),this);
    newAct -> setStatusTip(tr("Create a new database (.db)"));
    connect(newAct,SIGNAL(triggered()),this, SLOT(newFile()));

    // Help Menu Action
    // // Tutorials (How to use the app)
    tutorialAct= new QAction(tr("&Tutorial"),this);
    tutorialAct-> setStatusTip(tr("Click Here for Tutorial"));
    connect(tutorialAct, SIGNAL(triggered()),this,SLOT(Tutorial()));

    // ToolBar Actions
    // // Undo Action
    undoAct= new QAction(tr("&Undo"),this);
    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));


    // // Redo Action
    redoAct= new QAction(tr("&Redo"),this);
    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));


}

void MainWindow:: createMenuBar(){
    // File Menu
    file = menuBar()->addMenu(tr("&File"));
    // //  Adding Actions
    file-> addAction(newAct);
    file-> addAction(connectAct);

    // viewMenu
    view= menuBar() -> addMenu(tr("&View"));

    // Help Menu
    help= menuBar() -> addMenu(tr("&Help"));
    // // Adding Actions
    help-> addAction(tutorialAct);

}

void MainWindow:: createToolBar(){
    // ToolBar
    mainToolBar=addToolBar(tr("Actions"));

    // // Adding Actions
    mainToolBar -> addAction(undoAct);
    mainToolBar -> addAction(redoAct);
}

void MainWindow:: createStatusBar(){
    statusBar() -> showMessage(tr("Ready"));
}

OtherWindows * MainWindow:: changeWindow(windowtypes w){
    if(currentWindow != NULL){


        currentWindow->getCentralWidget()->setParent(0);
        currentWindow->setParent(0);
        prevWindow=currentWindow;
        windows.push(prevWindow->getWindowType());
    }

    if(W_Windows.find(w)!=W_Windows.end()){
        currentWindow= W_Windows.at(w);
    }


    else{
    switch(w){
    case mainWin : currentWindow = new mainWindow();break;
    case entranceWin : currentWindow = new entranceWindow();break;
    case donationsWin : currentWindow = new donationsWindow(); break;
   // case peopleWin : currentWindow = new peopleWindow(); break;
    case donersWin : currentWindow= new donersWindow();break;
    case addPeopleWin: currentWindow= new AddPeopleWindow();break;
    case addDonationWin : currentWindow= new AddDonationWindow();break;
    default: return NULL; //TO - DO :Message
    }

    //currentWindow->set_Parent(0);
    currentWindow ->createWindow();
    W_Windows[w]=currentWindow;
    }
    //Windows.push(currentWindow);
    setCentralWidget(currentWindow->getCentralWidget());
    currentWindow->set_Parent(this);
    qDebug()<<currentWindow<<" "<<currentWindow->WindowType<<typeid(currentWindow).name();
    Windows.push(prevWindow);
    return currentWindow;
}

void MainWindow:: connectFile() {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName(tr("MySQL"));
    if(db.open()){
        qDebug() <<"Opened";
        db.close();
    }
    else{
        QMessageBox::warning(this,tr("Error 202"),db.lastError().text());
        qDebug()<< "Error= "<<db.lastError().text();
    }


}

void MainWindow:: newFile(){}
void MainWindow:: Tutorial(){}
void MainWindow:: redo(){

}
void MainWindow:: undo(){

    // // Using a stack for the undo action
    if(Windows.size()>=1 && Windows.top()){
        currentWindow->getCentralWidget()->setParent(0);
        currentWindow->setParent(0);
        setCentralWidget(Windows.top()->getCentralWidget());
        currentWindow=Windows.top();
        Windows.pop();
    }
}

