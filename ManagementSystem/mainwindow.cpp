#include<QtWidgets>
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
    switch(w){
    case mainWin : currentWindow = new mainWindow();break;
    case entranceWin : currentWindow = new entranceWindow();break;
    case donationsWin : currentWindow = new donationsWindow(); break;
    case peopleWin : currentWindow = new peopleWindow(); break;
    case donersWin : currentWindow= new donersWindow();break;
    default: return NULL; //TO - DO :Message
    }
    currentWindow->setParent(this);
    currentWindow ->createWindow();
    setCentralWidget(currentWindow);
    return currentWindow;
}

void MainWindow:: connectFile() {
    DataBaseName= QFileDialog:: getOpenFileName(this,tr("Connect File"),"",tr(" database (*.db);;all files (* *.*)"));

    if (DataBaseName.isEmpty()){
        // To Do : MessageBox Warning
        return;
    }
}

void MainWindow:: newFile(){}
void MainWindow:: Tutorial(){}
void MainWindow:: redo(){}
void MainWindow:: undo(){}

void mainWindow:: startHere(){
    parent->setCentralWidget(0);
    parent->setLayout(0);
    parent->setCentralWidget(parent->changeWindow(entranceWin));



}

mainWindow * mainWindow :: createWindow(){


    title= new QLabel(tr("Welcome to the Donations Management System \n A Project By Hashem Khodor "));
    subtitle= new QLabel(tr("A Project By Hashem Khodor"));

    title->setAlignment(Qt::AlignCenter);
    subtitle -> setAlignment(Qt:: AlignCenter);

    title->resize(200,50);
    // To-Do: Fonts for both subtitle and title

    // Implementing Button:
    startHereButton= new QPushButton(tr("Start Here"));
    connect(startHereButton,SIGNAL(clicked()),this,SLOT(startHere()));

    layout= new QGridLayout();


    layout-> addWidget(title,0,0,1,4);
    layout-> addWidget(subtitle,1,0,1,4);
    layout-> addWidget(new QLabel(tr("")),2,0,2,4);
    layout-> addWidget(startHereButton,4,0,1,4);
    layout-> addWidget(new QLabel(tr("")),5,0,2,4);

    this-> setLayout(layout);
    return this;


}


entranceWindow * entranceWindow:: createWindow(){
    donations= new QLabel(tr("Donations"));
    people= new QLabel(tr("People"));
    doners= new QLabel(tr("Doners"));

    // Centering the labels
    donations->setAlignment(Qt:: AlignCenter);
    people-> setAlignment(Qt:: AlignCenter);
    doners -> setAlignment(Qt:: AlignCenter);

    // Donations Cluster
    viewOldDonations= new QPushButton(tr("View Old"));
    viewUpcomingDonations= new QPushButton(tr("View Upcoming"));
    addNewDonations = new QPushButton(tr("Add New"));


    //People Cluster
    viewAllPeople=new QPushButton(tr("View All"));
    viewPrioritizedPeople= new QPushButton(tr("View Prioritized"));
    addNewPeople= new QPushButton(tr("Add New"));

    //Doners Cluster
    viewdoners=new QPushButton(tr("View All"));
    seePercentage= new QPushButton(tr("View Statistics"));
    addUnexpected= new QPushButton(tr("Add New"));
    //Connecting SIGNALS AND SLOTS
    connect(viewdoners,SIGNAL(clicked()),this,SLOT(viewDoners()));

    layout= new QGridLayout();

    // Adding to the Layout

    layout-> addWidget(donations,0,0,1,4);
    layout-> addWidget(people,0,6,1,4);
    layout-> addWidget(doners,8,3,1,4);

    layout-> addWidget(viewOldDonations,2,1,1,2);
    layout -> addWidget(viewUpcomingDonations,4,1,1,2);
    layout -> addWidget(addNewDonations,6,1,1,2);

    layout-> addWidget(viewAllPeople,2,7,1,2);
    layout-> addWidget(viewPrioritizedPeople,4,7,1,2);
    layout-> addWidget(addNewPeople,6,7,1,2);


    layout -> addWidget(viewdoners,10,4,1,2);
    layout -> addWidget(seePercentage,12,4,1,2);
    layout-> addWidget(addUnexpected,14,4,1,2);

    this-> setLayout(layout);
    return this;


}

donationsWindow * donationsWindow:: createWindow(){
    return NULL;
}

peopleWindow * peopleWindow:: createWindow(){
    return NULL;
}

donersWindow * donersWindow  :: createWindow(){

    donersView= new QTreeWidget(this);
    QStringList headers= {"Doner ID","Donor Name","Individual or NGO","First Donation","Latest Donation","Donation Record"};
    donersView->setColumnCount(6);
    donersView-> setHeaderLabels(headers);
    QStringList division= {"Individual","NGO"};
    QTreeWidgetItem * row= new QTreeWidgetItem(donersView);
    for(int i=0; i<100; i++){

        row->setText(0,QString::number(rand()%202201553));
        row-> setText(1,"Hashem");
        row -> setText(2,division[rand()%2]);
        row-> setText(3,QString::number(rand()%1000));
        row-> setText(3,QString::number(rand()%1000));
        donersView-> setItemWidget(row,5,new QPushButton (tr("ID:")+QString::number(i)));
        row= new QTreeWidgetItem(donersView);
    }
    // Resizing columns to contents
    donersView->resizeColumnToContents(6);
    donersView-> setGeometry(geometry());

    return this;
}

void entranceWindow::viewDoners() {
    //parent->setCentralWidget(0);
    parent->changeWindow(donersWin);
    //parent->setCentralWidget(parent->changeWindow(donersWin));

}
