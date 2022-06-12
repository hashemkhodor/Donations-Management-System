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

void mainWindow:: startHere(){
    //parent->setCentralWidget(0);
   // parent->setLayout(0);
    parentt->changeWindow(entranceWin);
   // parent->setCentralWidget(parent->changeWindow(entranceWin));



}

mainWindow * mainWindow :: createWindow(){
    //Implementing title

    title= new QLabel(tr("Welcome to the Donations Management System \n A Project By Al Taalouf IT Team "));

    // Implementing Button:
    startHereButton= new QPushButton(tr("Start Here"));
    connect(startHereButton,SIGNAL(clicked()),this,SLOT(startHere()));
   // Implementing Layout:
    layout= new QVBoxLayout();
    layout-> addWidget(title);
    layout-> addWidget(startHereButton);

    //Fonts:
    QFont font("Segeo UI",23);
    title->setFont(font);
    font= QFont("Segeo UI",15);
    startHereButton->setFont(font);

    //Sizes:
    title->setMaximumSize(1000,500);
    startHereButton->setMaximumSize(5000,50);

    //Alignments:
    title->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);
    layout->setAlignment(title,Qt::AlignCenter);



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
    connect(addNewPeople,SIGNAL(clicked()),this,SLOT(addPeople()));

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
    QStringList headers= {"Donation ID","Donation Type","Individual or NGO","Number of recipients","Number of people in IT Team","Donation Record"};
    donationsView->setColumnCount(6);
    donationsView-> setHeaderLabels(headers);
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
    delete row;
    }
    else{
        if(db.lastError().text() != tr("")){
        QMessageBox::warning(this,tr("Error 202"),db.lastError().text());
        }
        else{
            QMessageBox::warning(this,tr("Error 202"),tr("SQL Query Error: Invalid Query"));
        }

    }
    // Resizing columns to contents
    donersView->resizeColumnToContents(6);

    return this;
}

AddPeopleWindow * AddPeopleWindow::createWindow(){
    add_People= new QFormLayout();
    //Creating the Labels;
    name= new QLabel(tr("Name(*)"));
    birthdate= new QLabel(tr("Birthdate(*)"));
    civil_record_num= new QLabel(tr("Civil Record Number(*)"));
    address= new QLabel(tr("Address(*)"));
    phone_number= new QLabel(tr("Phone Number(*)"));
    chronic_disease= new QLabel(tr("Chronic Diseases(*)"));
    comments= new QLabel(tr("Comments(Optional)"));
    submit= new QLabel(tr("Submit"));

    //Creating QLineEdit
    name_edit= new QLineEdit(tr("Mohammad Ali"));
    civil_record_num_edit= new QLineEdit(tr("177"));
    address_edit= new QLineEdit(tr("Enter Address"));
    phone_number_edit= new QLineEdit(tr("06370047"));

    //Creating QDateEdit
    QDate minDay(1900,1,1);
    birthdate_edit= new QDateEdit(QDate(2022,6,12));

    //Creating QComboBox
    chronic_disease_edit= new QComboBox();
    chronic_disease_edit->addItem(tr("Yes"));
    chronic_disease_edit->addItem(tr("No"));


    //Creating QTextEdit
    comments_edit= new QTextEdit(tr("Add Comments ..."));

    //Creating Button:
    submit_button= new QPushButton(tr("Submit"));
    connect(submit_button,SIGNAL(clicked()),this,SLOT(submitAct()));


    //Adding to QFormLayout
    add_People->addRow(name,name_edit);
    add_People->addRow(birthdate,birthdate_edit);
    add_People->addRow(civil_record_num,civil_record_num_edit);
    add_People->addRow(address,address_edit);
    add_People->addRow(phone_number,phone_number_edit);
    add_People->addRow(chronic_disease,chronic_disease_edit);
    add_People->addRow(comments,comments_edit);
    add_People->addRow(submit,submit_button);

    //Setting Layout
    setLayout(add_People);
    return this;




}

void entranceWindow::viewDoners() {
    parentt->changeWindow(donersWin);
}
void entranceWindow:: viewDonations(){
    parentt->changeWindow(donationsWin);

}
void entranceWindow:: addPeople(){
    parentt->changeWindow(addPeopleWin);

}

void AddPeopleWindow:: submitAct(){

    qDebug() <<name_edit->displayText()<< birthdate_edit->date().toString("yyyy-MM-dd")<<civil_record_num_edit->displayText()<<address_edit->displayText()<<chronic_disease_edit->currentText()<<comments_edit->toPlainText();

}
