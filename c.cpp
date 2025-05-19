#include<iostream>
#include<cmath>

using namespace std;
string EnumToString(InstructorType type);


enum class DanceTypes // I usualy use enums when I'm programing games thats why also in this project, I think its way more safer to use comparing to string.
{
    Salsa,
    Folk,
    HipHop,
    Ballet
}

string EnumToString(InstructorType type) 
{
    switch (type) {
        case InstructorType::Ballet: 
        return "Ballet";
        
        case InstructorType::HipHop: 
        return "HipHop";
        
        case InstructorType::Salsa: 
        return "Salsa";
        
        case InstructorType::Salsa: 
        return "Salsa";

        default: 
        return "ErrorCode#010 In the system this customer does not have any dance program!";
    }

class Human
{
    private:

    string Name = "";
    int Age = 0;
    int Money = 0 ;

    protected:


    public:

    virtual void Dance() = 0;

    Human(string name, int age, int money)
    {
        Name = name;
        Age = age;
        Money = money;
    }

};

class Customer
{
    private:
    DanceTypes Current_Dance;
    //int current_
    int Remaining_Hours = 0;
    bool Did_Earn_A_Certificate = false;


    public:

    void Dance()
    {
    }

    Customer(string name, int age, int money, int remaining_Hours, bool did_Earn_A_Certificate, DanceTypes current_Dance ):Human(name, age, money)
    {
        remaining_Hours = 10;
        did_Earn_A_Certificate = false;
        Current_Dance = current_Dance;
    } 
    
};


int main()
{
    return 0;
}