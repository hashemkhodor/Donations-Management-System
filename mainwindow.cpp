#include<QtWidgets>
#include<QtSql>
#include<QtDebug>
#include <QSpacerItem>
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
    i++;
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
    setCentralWidget(currentWindow->getCentralWidget());
    undos.push(currentWindow);
    windows.push_back(currentWindow);
    return currentWindow;
}

void MainWindow:: connectFile() {
    // DESKTOP-MHVMP5F\MSSQLSERVER01

    /*DataBaseName= QFileDialog:: getOpenFileName(this,tr("Connect File"),"",tr(" database (*.db);;all files (* *.*)"));

    if (DataBaseName.isEmpty()){
         To Do : MessageBox Warning
        return;
    }
    QString connectString = "Driver={SQL Server Native Client 11.0};";                     // Driver is now {SQL Server Native Client 11.0}
    connectString.append("Server=DESKTOP-MHVMP5F\\MSSQLSERVER01");   // Hostname,SQL-Server Instance
    connectString.append("Database=mysqlhashem;");  // Schema
    connectString.append("Trusted_Connection=Yes");
    QString servername="DESKTOP-MHVMP5F\\MSSQLSERVER01";
    QString dbname="mysqlhashem.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn= QString("Driver={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbname);
        */
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName(tr("MySQL"));
    if(db.open()){
        qDebug() <<"Opened";
        /*if(qr.exec("select * from [mysqlhashem].[dbo].[EmployeeTable]" )){
            while(qr.next()){
                qDebug() << qr.value(0).toInt() <<" "<<qr.value(1).toString()<<" "<<qr.value(2).toString();

            }
        }
        else{}*/
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

    if(redos.top() && redos.size()>1){
        //setCentralWidget(redos.top()->getCentralWidget());
        setCentralWidget(redos.top());
        undos.push(redos.top());
        redos.pop();


    }

}
void MainWindow:: undo(){

    if(undos.top() && undos.size()>1){
        //OtherWindows * other= undos.top();
        OtherWindows * other = windows[i-1];
        QMessageBox::warning(this,tr("Error 202"),other->WindowType + QString::number(undos.size()));
        //setCentralWidget(other->getCentralWidget());
        qDebug() <<other->WindowType;
        setCentralWidget(other);
        redos.push(other);
        //undos.pop();

    }
   // else{
    //   changeWindow(mainWin);
   // }

}

void mainWindow:: startHere(){
    parent->setCentralWidget(0);
   // parent->setLayout(0);
    parent->changeWindow(entranceWin);
   // parent->setCentralWidget(parent->changeWindow(entranceWin));



}

mainWindow * mainWindow :: createWindow(){


    title= new QLabel(tr("Welcome to the Donations Management System \n A Project By Al Taalouf IT Team "));
    //subtitle= new QLabel(tr("A Project By Hashem Khodor"));

    title->setAlignment(Qt::AlignCenter);
    QFont font("Segeo UI",23);
    title->setFont(font);
   // subtitle -> setAlignment(Qt:: AlignCenter);
    font= QFont("Segeo UI",15);
    title->setMaximumSize(1000,500);
    //title->setSizePolicy(QSizePolicy::Fixed  , QSizePolicy::Fixed);
    //title->setAlignment(Qt::AlignVCenter);
    // To-Do: Fonts for both subtitle and title
    //Implementing the spacer:
    //QSpacerItem * spacer= new QSpacerItem(30,30);


    // Implementing Button:
    startHereButton= new QPushButton(tr("Start Here"));
    startHereButton->setFont(font);
    startHereButton->setMaximumSize(5000,50);
    connect(startHereButton,SIGNAL(clicked()),this,SLOT(startHere()));
    //startHereButton->setSizeIncrement(200,50);
    //startHereButton-> setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout= new QVBoxLayout();

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);
    layout-> addWidget(title);
    layout->setAlignment(title,Qt::AlignCenter);
    //layout-> addWidget(new QLabel(tr("")));
    //layout-> addWidget(new QLabel(tr("")),2,0,2,4);
    layout-> addWidget(startHereButton);
    //layout->setAlignment(startHereButton,Qt::AlignCenter);

    //layout-> addWidget(new QLabel(tr("")),5,0,2,4);

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
    connect(viewOldDonations,SIGNAL(clicked()),this,SLOT(viewDonations()));

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
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName(tr("MySQL"));

    donationsView= new QTreeWidget(this);
    QStringList headers= {"Donation ID","Donation Type","Individual or NGO","Number of recipients","Number of ass","Donation Record"};
    donationsView->setColumnCount(6);
    donationsView-> setHeaderLabels(headers);
    //QStringList division= {"Individual","NGO"};
    //QStringList names= {"Hashem","Latifa","Mohamad","Abed","Fatima"};
    QTreeWidgetItem * row= new QTreeWidgetItem(donationsView);
    QSqlQuery query;
    int i=0;
    if(db.open() && query.exec("SELECT * FROM [mysqlhashem].[dbo].[managementSystemTest]")){
        while(query.next()){
            i++;
            row->setText(0,QString::number(query.value(0).toInt()));
            row-> setText(1,query.value(1).toString());
            row -> setText(2,query.value(2).toString());
            row-> setText(3,QString::number(query.value(3).toInt()));
            row-> setText(4,QString::number(query.value(4).toInt()));
            donationsView-> setItemWidget(row,5,new QPushButton (tr("ID:")+QString::number(i)));
            row= new QTreeWidgetItem(donationsView);

        }
        db.close();
    }

    delete row;
    // Resizing columns to contents
    donationsView->resizeColumnToContents(6);
    //donersView-> setGeometry(geometry());

    return this;
}

peopleWindow * peopleWindow:: createWindow(){
    return NULL;
}

donersWindow * donersWindow  :: createWindow(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName(tr("MySQL"));

    donersView= new QTreeWidget(this);
    QStringList headers= {"Doner ID","Donor Name","Individual or NGO","First Donation","Latest Donation","Donation Record"};
    donersView->setColumnCount(6);
    donersView-> setHeaderLabels(headers);
    //QStringList division= {"Individual","NGO"};
    //QStringList names= {"Hashem","Latifa","Mohamad","Abed","Fatima"};
    QTreeWidgetItem * row= new QTreeWidgetItem(donersView);
    QSqlQuery query;
    int i=0;
    if(db.open() && query.exec("SELECT * FROM [mysqlhashem].[dbo].[managementSystemTest]")){
        while(query.next()){
            i++;
            row->setText(0,QString::number(query.value(0).toInt()));
            row-> setText(1,query.value(1).toString());
            row -> setText(2,query.value(2).toString());
            row-> setText(3,QString::number(query.value(3).toInt()));
            row-> setText(4,QString::number(query.value(4).toInt()));
            donersView-> setItemWidget(row,5,new QPushButton (tr("ID:")+QString::number(i)));
            row= new QTreeWidgetItem(donersView);

        }
        db.close();

    }
    delete row;

    /*
    for(int i=0; i<1000; i++){

        row->setText(0,QString::number(rand()%202201553));
        row-> setText(1,names[rand()%5]);
        row -> setText(2,division[rand()%2]);
        row-> setText(3,QString::number(rand()%1000));
        row-> setText(3,QString::number(rand()%1000));
        donersView-> setItemWidget(row,5,new QPushButton (tr("ID:")+QString::number(i)));
        row= new QTreeWidgetItem(donersView);
    }
    */
    // Resizing columns to contents
    donersView->resizeColumnToContents(6);
    //donersView-> setGeometry(geometry());

    return this;
}

void entranceWindow::viewDoners() {
    //parent->setCentralWidget(0);
    parent->changeWindow(donersWin);
    //parent->setCentralWidget(parent->changeWindow(donersWin));

}
void entranceWindow:: viewDonations(){
    parent->changeWindow(donationsWin);

}
