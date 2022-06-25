# Human 
Create an abstract class Human that has the following public pure virtual methods:

- virtual vector< String >  get_info()=0;
- virtual double getpriority()=0;
- virtual long int ID()=0;


We want two subclasses that inherit from Human and each one has its own implementation of the virtual methods above.We will implement the first class below.
The following subclasses are:
- Recipient
- Donor

# Recipient
The following class has the following data attributes:
1. ID
2. Name
3. Birthdate
4. Latest Donation Recieved(Date)
5. Latest Donation Recieved (ID of the Donation)
6. Record of recieved Donations (IDs)

It's constructor initialize an object of type Recipient assigning values to the above data attributes. If no such data is present, didn't recieve any donation, we initialize it to be empty (empty vector and empty string, etc.).

It has the following implementation of the virtual functions:
- virtual vector< String >  get_info() returns a vector of information in the above order {ID,Name,Birthdate,...}
- virtual int priority() returns the priority of the recipient which is the number of days that passed since the latest donation recieved. If No such donation is recieved, the function must return infinity.
- virtual long int ID() that returns the ID of the recipient.
