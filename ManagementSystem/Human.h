
#include<vector>

class Human {
public:
    Human(){}


    public:
    virtual vector< string > get_info()=0;
    virtual double getpriority()=0;
    virtual long int getID()=0;



};

class RecipientAdded:public Human{
    public:
    RecipientAdded(long int id,QString fname, QString lname, QString bday, int civ, QString Vill, QString Addr, QString phone, bool chron, QString comm="") {
        ID=id;
        f_name= fname;
        l_name=lname;
        birthdate= bday;
        civil_record_number= civ;
        Village = Vill;
        Address= Addr;
        phone_number= phone;
        chron_dis= chron;
        comments= comm;

    }


    public:
    long int ID;
    QString f_name;
    QString l_name;
    QString birthdate;
    int civil_record_number;
    QString Village;
    QString Address;
    QString phone_number;
    bool chron_dis;
    QString comments;
};

class RecipientAccessed:public Human{
    public:
    RecipientAccessed(long int id,QString fname, QString lname, QString bday, QString number,QString latest_d, long int latest_d_id, vector<long int> d_ids) {
        ID=id;
        f_name= fname;
        l_name=lname;
        birthdate= bday;
        phone_number=number;
        latest_donation_date= latest_d;
        latest_donation_id = latest_d_id;
        donations_id= d_ids;
    }


    public:
    long int ID;
    QString f_name;
    QString l_name;
    QString birthdate;
    QString phone_number;
    QString latest_donation_date;
    long int latest_donation_id;
    vector<long int> donations_id;
    QString phone_number;


    virtual double getpriority(){
        //TO-DO: Find out how the priority is calculated
    }
    
};