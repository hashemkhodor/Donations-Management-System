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

void mainWindow:: startHere(){
    //parent->setCentralWidget(0);
   // parent->setLayout(0);
    parentt->changeWindow(entranceWin);
   // parent->setCentralWidget(parent->changeWindow(entranceWin));



}

mainWindow * mainWindow :: createWindow(){
    //Implementing title

    title= new QLabel(tr("Welcome to the Donations Management System \n A Project By Al Taalouf IT Team "));

    //Stylesheet
   // title->setStyleSheet("color: blue;"
     //                    "background-color: yellow;"
       //                  "selection-color: yellow;"
         //                "selection-background-color: blue;");

    // Implementing Button:
    startHereButton= new QPushButton(tr("Start Here"));
    startHereButton->setStyleSheet(button_css);

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
    connect(addNewDonations,SIGNAL(clicked()),this,SLOT(addDonations()));

    //StyleSheets Buttons
    viewOldDonations->setStyleSheet(button_css);
    viewUpcomingDonations->setStyleSheet(button_css);
    addNewDonations->setStyleSheet(button_css);

    viewAllPeople->setStyleSheet(button_css);
    viewPrioritizedPeople->setStyleSheet(button_css);
    addNewPeople->setStyleSheet(button_css);

    viewdoners->setStyleSheet(button_css);
    seePercentage->setStyleSheet(button_css);
    addUnexpected->setStyleSheet(button_css);

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
    donationsView->setStyleSheet("QHeaderView::section {                          "
                                 "    color: black;                               "
                                 "    padding: 2px;                               "
                                 "    height:20px;                                "
                                 "    border: 0px solid #567dbc;                  "
                                 "    border-left:0px;                            "
                                 "    border-right:0px;                           "
                                 "    background-color: #2ea44f;                        "
                                 "}");
    QStringList headers= {"Donation ID","Donation Type","Individual or NGO","Number of recipients","Number of people in IT Team","Donation Record"};
    donationsView->setColumnCount(6);
    donationsView-> setHeaderLabels(headers);
    QTreeWidgetItem * row= new QTreeWidgetItem(donationsView);
    QPushButton * button;
    QSqlQuery query;
    int i=0;
    if(db.open() && query.exec("SELECT * FROM [mysqlhashem].[dbo].[managementSystemTest]")){
        while(query.next()){
            i++;
            button= new QPushButton (tr("ID:")+QString::number(i));
            button-> setStyleSheet(button_css);
            row->setText(0,QString::number(query.value(0).toInt()));
            row-> setText(1,query.value(1).toString());
            row -> setText(2,query.value(2).toString());
            row-> setText(3,QString::number(query.value(3).toInt()));
            row-> setText(4,QString::number(query.value(4).toInt()));
            donationsView-> setItemWidget(row,5,button);
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
    QPushButton * button;
    QSqlQuery query;
    int i=0;
    if(db.open() && query.exec("SELECT * FROM [mysqlhashem].[dbo].[managementSystemTest]")){
        while(query.next()){
            i++;
            button= new QPushButton (tr("ID:")+QString::number(i));
            button-> setStyleSheet(button_css);
            row->setText(0,QString::number(query.value(0).toInt()));
            row-> setText(1,query.value(1).toString());
            row -> setText(2,query.value(2).toString());
            row-> setText(3,QString::number(query.value(3).toInt()));
            row-> setText(4,QString::number(query.value(4).toInt()));
            donersView-> setItemWidget(row,5,button);
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
    village= new QLabel(tr("Village(*)"));
    address= new QLabel(tr("Address(*)"));
    phone_number= new QLabel(tr("Phone Number(*)"));
    chronic_disease= new QLabel(tr("Chronic Diseases(*)"));
    comments= new QLabel(tr("Comments(Optional)"));
    submit= new QLabel(tr("Submit"));

    //Creating QLineEdit
    name_edit= new QLineEdit(tr(""));
    civil_record_num_edit= new QLineEdit(tr(""));
    address_edit= new QLineEdit(tr(""));
    phone_number_edit= new QLineEdit(tr(""));

    //Creating QDateEdit
    QDate minDay(1900,1,1);
    birthdate_edit= new QDateEdit();

    //Creating QComboBox
    chronic_disease_edit= new QComboBox();
    chronic_disease_edit->addItem(tr(""));
    chronic_disease_edit->addItem(tr("Yes"));
    chronic_disease_edit->addItem(tr("No"));

    village_edit= new QComboBox();
    village_edit->addItem(tr(""));
    QString villages ("Aabboudiyeh|"
               "Aadbel|"
               "Aaidamoun - Chikhlar|"
               "Aaiyat|"
               "Aakkar El Aatiqa|"
               "Aamair - Rajm Aissi|"
               "Aamaret El Baykat|"
               "Aandqet|"
               "Aaouainat|"
               "Aarqa|"
               "Aayoun (Aakkar)|"
               "Aayoun El Ghizlane|"
               "Ain El Zehab|"
               "Ain Ez Zayt|"
               "Ain Yaaqoub|"
               "Akroum |"
               "Aouadeh|"
               "Bani Sakhr|"
               "Bebnine - Aabdeh|"
               "Beino - Qboula|"
               "Beit Ayoub|"
               "Beit El Hajj|"
               "Beit Mellat|"
               "Beit Younes|"
               "Berbara (Aakkar)|"
               "Berqayel|"
               "Bezbina (Aakkar)|"
               "Bireh (Aakkar)|"
               "Borj|"
               "Borj El Aarab|"
               "Bqerzla|"
               "Bzal|"
               "Chadra|"
               "Chakdouf|"
               "Chane|"
               "Charbila|"
               "Cheikh Aayach|"
               "Cheikh Mohammad|"
               "Cheikh Taba|"
               "Daghleh|"
               "Dahr El Qanbar|"
               "Dahr Laissineh|"
               "Daoura (Aakkar)|"
               "Daoussa - Baghdadi|"
               "Deir Dalloum - Zouq El Moqachrine|"
               "Deir Jannine|"
               "Dibbabiyeh|"
               "Douair Aadouiyeh|"
               "Fardh|"
               "Fnaydeq|"
               "Fsaqine - Ain Aachma - Ain Tinta|"
               "Ghazaleh|"
               "Halba|"
               "Haycheh|"
               "Hayssa|"
               "Haytla|"
               "Hayzouq|"
               "Hmayra|"
               "Houaich|"
               "Hrar|"
               "Ilat|"
               "Jdaidet (Aakkar)|"
               "Jdaidet El Qayteaa|"
               "Jebrayel|"
               "Jermnaiya - El Ram|"
               "Karm Aasfour - Beit Ghattas|"
               "Kfartoun|"
               "Khat El Batrol|"
               "Khirbet Char|"
               "Khirbet Daoud|"
               "Khreibet Ej Jindi|"
               "Kouachra|"
               "Koucha|"
               "Koueikhat|"
               "Kroum Aarab|"
               "Machha|"
               "Machta Hammoud|"
               "Machta Hassan|"
               "Majdala|"
               "Mar Touma|"
               "Massaaoudiyeh|"
               "Mazraat Baldeh|"
               "Mechilhat Hakour|"
               "Mechmech (Aakkar)|"
               "Memneaa|"
               "Menjez|"
               "Mhamra|"
               "Minyara|"
               "Mqaitaa - Qaabrine - Kfar Melki - Rmoul|"
               "Mqaybleh|"
               "Nahriyeh - Boustane El Herch|"
               "Nahriyeh - Boustane El Herch|"
               "Naoura|"
               "Nfisseh|"
               "Ouadi Ej Jamous|"
               "Qabaait|"
               "Qantara|"
               "Qarqaf|"
               "Qechlq|"
               "Qleiaat|"
               "Qnit|"
               "Qorneh|"
               "Qoubbet Chamra|"
               "Qraiyat|"
               "Rahbeh|"
               "Rihaniyeh|"
               "Rmah|"
               "Sahleh|"
               "Sayssouq|"
               "Sfinet Ed Drayb|"
               "Sfinet El Qayteaa|"
               "Sindianet Zeidane|"
               "Souaisset|"
               "Tachaa|"
               "Tall Aabbas El Gharbi|"
               "Tall Bireh|"
               "Tall Meaayane|"
               "Talleh - Chattaha|"
               "Tikrit|"
               "Tleil |"
               "Wadi El Haour|"
               "Wadi El Jamous|"
               "Wadi Khaled|"
               "Zouarib|"
               "Zouq El Hassineh|"
               "Zouq Haddara|");
    QString v("");
    for(auto m :villages){
        if(m == '|'){village_edit->addItem(v);v="";}
        else{v+=m;}
    }


    //Creating QTextEdit
    comments_edit= new QTextEdit(tr(""));

    //Creating Button:
    submit_button= new QPushButton(tr("Submit"));
    connect(submit_button,SIGNAL(clicked()),this,SLOT(submitAct()));
    add_button = new QPushButton(tr("Add Person"));
    connect(add_button,SIGNAL(clicked()),this,SLOT(addAct()));
    view_button = new QPushButton(tr("View People"));
    connect(view_button,SIGNAL(clicked()),this,SLOT(viewAct()));

    // QHBoxLayout
    buttons_layout= new QHBoxLayout();
    buttons_layout->addWidget(add_button);
    buttons_layout->addWidget(view_button);
    buttons_layout->addWidget(submit_button);



    //Adding to QFormLayout
    add_People->addRow(name,name_edit);
    add_People->addRow(birthdate,birthdate_edit);
    add_People->addRow(civil_record_num,civil_record_num_edit);
    add_People->addRow(village,village_edit);
    add_People->addRow(address,address_edit);
    add_People->addRow(phone_number,phone_number_edit);
    add_People->addRow(chronic_disease,chronic_disease_edit);
    add_People->addRow(comments,comments_edit);
    add_People->addRow(submit,buttons_layout);

    //Setting Layout
    setLayout(add_People);
    return this;




}

AddDonationWindow * AddDonationWindow::createWindow(){
    add_Donation= new QFormLayout();
    //Creating the main Labels;
    name= new QLabel(tr("Donation Name(*)"));
    donation_type= new QLabel(tr("Donation Type(*)"));
    donor= new QLabel(tr("Donor Name(*)"));
    date= new QLabel(tr("Donation Date(*)"));
    num_recipients= new QLabel(tr("Number of Recipients(*)"));
    pre_requistes= new QLabel(tr("Pre-requistes(*)"));
    buttons_label= new QLabel(tr("Buttons"));
    comments= new QLabel(tr("Comments(Optional)"));

    //Creating QLineEdit
    name_edit= new QLineEdit(tr(""));
    donation_type_edit2= new QLineEdit(tr(""));
    donor_edit2= new QLineEdit(tr(""));


    //Creating QDateEdit
    QDate minDay(1900,1,1);
    date_edit= new QDateEdit();

    //Creating QComboBox
    donation_type_edit1= new QComboBox();
    donation_type_edit1->addItem(tr(""));

    donor_edit1= new QComboBox();
    donor_edit1->addItem(tr(""));


    // Creating QSpinBox:
    num_recipients_edit= new QSpinBox();
    num_recipients_edit->setMaximum(10000);
    num_recipients_edit->setMinimum(1);

    // Creating pre-requistes form edit:
    conditions_layout= new QFormLayout();
        // Creating Labels:
        num_people_house = new QLabel(tr("Number of People in House"));
        chronic_dis= new QLabel(tr("Chronic Disease"));
        village= new QLabel(tr("Village"));
        nationality= new QLabel(tr("Nationality"));

        //Creating spinboxes:
        num_people_house_edit= new QSpinBox();
        //Creating ComboBoxs
        chronic_dis_edit= new QComboBox();
        nationality_edit= new QComboBox();
        nationality_edit->addItem("");
        QString nationalities("Afghanistan|"
                            "Albania|"
                            "Algeria|"
                            "Andorra|"
                            "Angola|"
                            "Antigua and Barbuda|"
                            "Argentina|"
                            "Armenia|"
                            "Australia|"
                            "Austria|"
                            "Azerbaijan|"
                            "Bahamas|"
                            "Bahrain|"
                            "Bangladesh|"
                            "Barbados|"
                            "Belarus|"
                            "Belgium|"
                            "Belize|"
                            "Benin|"
                            "Bhutan|"
                            "Bolivia|"
                            "Bosnia and Herzegovina|"
                            "Botswana|"
                            "Brazil|"
                            "Brunei |"
                            "Bulgaria|"
                            "Burkina Faso|"
                            "Burundi|"
                            "Côte d'Ivoire|"
                            "Cabo Verde|"
                            "Cambodia|"
                            "Cameroon|"
                            "Canada|"
                            "Central African Republic|"
                            "Chad|"
                            "Chile|"
                            "China|"
                            "Colombia|"
                            "Comoros|"
                            "Congo (Congo-Brazzaville)|"
                            "Costa Rica|"
                            "Croatia|"
                            "Cuba|"
                            "Cyprus|"
                            "Czechia (Czech Republic)|"
                            "Democratic Republic of the Congo|"
                            "Denmark|"
                            "Djibouti|"
                            "Dominica|"
                            "Dominican Republic|"
                            "Ecuador|"
                            "Egypt|"
                            "El Salvador|"
                            "Equatorial Guinea|"
                            "Eritrea|"
                            "Estonia|"
                            "Eswatini (fmr. 'Swaziland')|"
                            "Ethiopia|"
                            "Fiji|"
                            "Finland|"
                            "France|"
                            "Gabon|"
                            "Gambia|"
                            "Georgia|"
                            "Germany|"
                            "Ghana|"
                            "Greece|"
                            "Grenada|"
                            "Guatemala|"
                            "Guinea|"
                            "Guinea-Bissau|"
                            "Guyana|"
                            "Haiti|"
                            "Holy See|"
                            "Honduras|"
                            "Hungary|"
                            "Iceland|"
                            "India|"
                            "Indonesia|"
                            "Iran|"
                            "Iraq|"
                            "Ireland|"
                            "Italy|"
                            "Jamaica|"
                            "Japan|"
                            "Jordan|"
                            "Kazakhstan|"
                            "Kenya|"
                            "Kiribati|"
                            "Kuwait|"
                            "Kyrgyzstan|"
                            "Laos|"
                            "Latvia|"
                            "Lebanon|"
                            "Lesotho|"
                            "Liberia|"
                            "Libya|"
                            "Liechtenstein|"
                            "Lithuania|"
                            "Luxembourg|"
                            "Madagascar|"
                            "Malawi|"
                            "Malaysia|"
                            "Maldives|"
                            "Mali|"
                            "Malta|"
                            "Marshall Islands|"
                            "Mauritania|"
                            "Mauritius|"
                            "Mexico|"
                            "Micronesia|"
                            "Moldova|"
                            "Monaco|"
                            "Mongolia|"
                            "Montenegro|"
                            "Morocco|"
                            "Mozambique|"
                            "Myanmar (formerly Burma)|"
                            "Namibia|"
                            "Nauru|"
                            "Nepal|"
                            "Netherlands|"
                            "New Zealand|"
                            "Nicaragua|"
                            "Niger|"
                            "Nigeria|"
                            "North Korea|"
                            "North Macedonia|"
                            "Norway|"
                            "Oman|"
                            "Pakistan|"
                            "Palau|"
                            "Palestine State|"
                            "Panama|"
                            "Papua New Guinea|"
                            "Paraguay|"
                            "Peru|"
                            "Philippines|"
                            "Poland|"
                            "Portugal|"
                            "Qatar|"
                            "Romania|"
                            "Russia|"
                            "Rwanda|"
                            "Saint Kitts and Nevis|"
                            "Saint Lucia|"
                            "Saint Vincent and the Grenadines|"
                            "Samoa|"
                            "San Marino|"
                            "Sao Tome and Principe|"
                            "Saudi Arabia|"
                            "Senegal|"
                            "Serbia|"
                            "Seychelles|"
                            "Sierra Leone|"
                            "Singapore|"
                            "Slovakia|"
                            "Slovenia|"
                            "Solomon Islands|"
                            "Somalia|"
                            "South Africa|"
                            "South Korea|"
                            "South Sudan|"
                            "Spain|"
                            "Sri Lanka|"
                            "Sudan|"
                            "Suriname|"
                            "Sweden|"
                            "Switzerland|"
                            "Syria|"
                            "Tajikistan|"
                            "Tanzania|"
                            "Thailand|"
                            "Timor-Leste|"
                            "Togo|"
                            "Tonga|"
                            "Trinidad and Tobago|"
                            "Tunisia|"
                            "Turkey|"
                            "Turkmenistan|"
                            "Tuvalu|"
                            "Uganda|"
                            "Ukraine|"
                            "United Arab Emirates|"
                            "United Kingdom|"
                            "United States of America|"
                            "Uruguay|"
                            "Uzbekistan|"
                            "Vanuatu|"
                            "Venezuela|"
                            "Vietnam|"
                            "Yemen|"
                            "Zambia|"
                            "Zimbabwe|");
        QString v("");
        for(auto m :nationalities){
            if(m == '|'){nationality_edit->addItem(v);v="";}
            else{v+=m;}
        }
        village_edit= new QComboBox();
        village_edit->addItem(tr(""));
        QString villages ("Aabboudiyeh|"
                   "Aadbel|"
                   "Aaidamoun - Chikhlar|"
                   "Aaiyat|"
                   "Aakkar El Aatiqa|"
                   "Aamair - Rajm Aissi|"
                   "Aamaret El Baykat|"
                   "Aandqet|"
                   "Aaouainat|"
                   "Aarqa|"
                   "Aayoun (Aakkar)|"
                   "Aayoun El Ghizlane|"
                   "Ain El Zehab|"
                   "Ain Ez Zayt|"
                   "Ain Yaaqoub|"
                   "Akroum |"
                   "Aouadeh|"
                   "Bani Sakhr|"
                   "Bebnine - Aabdeh|"
                   "Beino - Qboula|"
                   "Beit Ayoub|"
                   "Beit El Hajj|"
                   "Beit Mellat|"
                   "Beit Younes|"
                   "Berbara (Aakkar)|"
                   "Berqayel|"
                   "Bezbina (Aakkar)|"
                   "Bireh (Aakkar)|"
                   "Borj|"
                   "Borj El Aarab|"
                   "Bqerzla|"
                   "Bzal|"
                   "Chadra|"
                   "Chakdouf|"
                   "Chane|"
                   "Charbila|"
                   "Cheikh Aayach|"
                   "Cheikh Mohammad|"
                   "Cheikh Taba|"
                   "Daghleh|"
                   "Dahr El Qanbar|"
                   "Dahr Laissineh|"
                   "Daoura (Aakkar)|"
                   "Daoussa - Baghdadi|"
                   "Deir Dalloum - Zouq El Moqachrine|"
                   "Deir Jannine|"
                   "Dibbabiyeh|"
                   "Douair Aadouiyeh|"
                   "Fardh|"
                   "Fnaydeq|"
                   "Fsaqine - Ain Aachma - Ain Tinta|"
                   "Ghazaleh|"
                   "Halba|"
                   "Haycheh|"
                   "Hayssa|"
                   "Haytla|"
                   "Hayzouq|"
                   "Hmayra|"
                   "Houaich|"
                   "Hrar|"
                   "Ilat|"
                   "Jdaidet (Aakkar)|"
                   "Jdaidet El Qayteaa|"
                   "Jebrayel|"
                   "Jermnaiya - El Ram|"
                   "Karm Aasfour - Beit Ghattas|"
                   "Kfartoun|"
                   "Khat El Batrol|"
                   "Khirbet Char|"
                   "Khirbet Daoud|"
                   "Khreibet Ej Jindi|"
                   "Kouachra|"
                   "Koucha|"
                   "Koueikhat|"
                   "Kroum Aarab|"
                   "Machha|"
                   "Machta Hammoud|"
                   "Machta Hassan|"
                   "Majdala|"
                   "Mar Touma|"
                   "Massaaoudiyeh|"
                   "Mazraat Baldeh|"
                   "Mechilhat Hakour|"
                   "Mechmech (Aakkar)|"
                   "Memneaa|"
                   "Menjez|"
                   "Mhamra|"
                   "Minyara|"
                   "Mqaitaa - Qaabrine - Kfar Melki - Rmoul|"
                   "Mqaybleh|"
                   "Nahriyeh - Boustane El Herch|"
                   "Nahriyeh - Boustane El Herch|"
                   "Naoura|"
                   "Nfisseh|"
                   "Ouadi Ej Jamous|"
                   "Qabaait|"
                   "Qantara|"
                   "Qarqaf|"
                   "Qechlq|"
                   "Qleiaat|"
                   "Qnit|"
                   "Qorneh|"
                   "Qoubbet Chamra|"
                   "Qraiyat|"
                   "Rahbeh|"
                   "Rihaniyeh|"
                   "Rmah|"
                   "Sahleh|"
                   "Sayssouq|"
                   "Sfinet Ed Drayb|"
                   "Sfinet El Qayteaa|"
                   "Sindianet Zeidane|"
                   "Souaisset|"
                   "Tachaa|"
                   "Tall Aabbas El Gharbi|"
                   "Tall Bireh|"
                   "Tall Meaayane|"
                   "Talleh - Chattaha|"
                   "Tikrit|"
                   "Tleil |"
                   "Wadi El Haour|"
                   "Wadi El Jamous|"
                   "Wadi Khaled|"
                   "Zouarib|"
                   "Zouq El Hassineh|"
                   "Zouq Haddara|");
        v="";
        for(auto m :villages){
            if(m == '|'){village_edit->addItem(v);v="";}
            else{v+=m;}
        }
        conditions_layout->addRow(num_people_house,num_people_house_edit);
        conditions_layout->addRow(chronic_dis,chronic_dis_edit);
        conditions_layout->addRow(village,village_edit);
        conditions_layout->addRow(nationality,nationality_edit);


    //Creating QTextEdit
    comments_edit= new QTextEdit(tr(""));

    //Creating Button:
    add_donation_button= new QPushButton(tr("Add Donation"));
    connect(add_donation_button,SIGNAL(clicked()),this,SLOT(adddonationAct()));
    view_suggested_button = new QPushButton(tr("View Suggested People"));
    connect(view_suggested_button,SIGNAL(clicked()),this,SLOT(viewsuggestedAct()));
    edit_suggested_button = new QPushButton(tr("Edit Suggested People"));
    connect(edit_suggested_button,SIGNAL(clicked()),this,SLOT(editsuggestedAct()));

    // QHBoxLayout
    buttons_layout= new QHBoxLayout();
    buttons_layout->addWidget(add_donation_button);
    buttons_layout->addWidget(view_suggested_button);
    buttons_layout->addWidget(edit_suggested_button);

    donation_type_layout= new QHBoxLayout();
    donation_type_layout-> addWidget(donation_type_edit1);
    donation_type_layout -> addWidget(donation_type_edit2);
    donation_type_edit2->setSizePolicy(QSizePolicy:: Preferred,QSizePolicy::Preferred);

    donor_layout= new QHBoxLayout();
    donor_layout -> addWidget(donor_edit1);
    donor_layout -> addWidget(donor_edit2);
    donor_edit2->setSizePolicy(QSizePolicy:: Preferred,QSizePolicy::Preferred);





    //Adding to QFormLayout
    add_Donation->addRow(name,name_edit);
    add_Donation->addRow(donation_type,donation_type_layout);
    add_Donation->addRow(donor,donor_layout);
    add_Donation->addRow(date,date_edit);
    add_Donation->addRow(num_recipients,num_recipients_edit);
    add_Donation->addRow(pre_requistes,conditions_layout);
    add_Donation->addRow(comments,comments_edit);
    add_Donation->addRow(buttons_label,buttons_layout);

    //Setting Layout
    setLayout(add_Donation);
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
void entranceWindow:: addDonations(){
    parentt->changeWindow(addDonationWin);

}

void AddPeopleWindow:: submitAct(){

    qDebug() <<name_edit->displayText()<< birthdate_edit->date().toString("yyyy-MM-dd")<<civil_record_num_edit->displayText()<<address_edit->displayText()<<chronic_disease_edit->currentText()<<comments_edit->toPlainText();

}

void AddPeopleWindow:: viewAct(){

    qDebug() <<name_edit->displayText()<< birthdate_edit->date().toString("yyyy-MM-dd")<<civil_record_num_edit->displayText()<<address_edit->displayText()<<chronic_disease_edit->currentText()<<comments_edit->toPlainText();

}
void AddPeopleWindow:: addAct(){

    qDebug() <<name_edit->displayText()<< birthdate_edit->date().toString("yyyy-MM-dd")<<civil_record_num_edit->displayText()<<address_edit->displayText()<<chronic_disease_edit->currentText()<<comments_edit->toPlainText();

}
