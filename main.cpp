#include<iostream>
#include<cmath>

using namespace std;



enum class DanceTypes // I usualy use enums when I'm programing games thats why also in this project, I think its way more safer than string.
{
    Salsa,
    Folk,
    HipHop,
    Ballet
};

string EnumToString(DanceTypes type) 
{
    switch (type) {
        case DanceTypes::Ballet: 
        return "Ballet";
        
        case DanceTypes::HipHop: 
        return "HipHop";
        
        case DanceTypes::Salsa: 
        return "Salsa";
        
        case DanceTypes::Folk: 
        return "Folk";

        default: 
        return "ErrorCode#010 In the system this customer does not have any dance program!";
    }
}

class Human
{
    private:
    DanceTypes Current_Dance;
    int Profession_On_Current_Dance = 0;

    string Name = "";
    bool Is_Male = false;
    int Age = 0;
    int Money = 0 ;

    protected:


    public:
    
    string GetName()
    {
        return Name;
    }

    int GetProfessionOnCurrentDance()
    {
        return Profession_On_Current_Dance;
    }

    void IncreaseProfessionOnCurrentDance(int hour)
    {
        if(hour<1)
        {
            cout<<"You entered a wrong input. Hour cant be smaller than 1!"<<endl;
        }
        else
        {
            Profession_On_Current_Dance += hour;
        }
    }

    DanceTypes GetCurrentDance()
    {
        return Current_Dance;
    }
    
    virtual void SetDanceType(DanceTypes type)
    {
        Current_Dance = type;
        cout<<Name<< "change their dance style"<<endl;
    }
 


    virtual void GetInformation() = 0;
    virtual void Dance() = 0;


    Human(string name, int age, int money, DanceTypes current_Dance, bool is_male)
    {
        Name = name;
        Age = age;
        Money = money;
        Current_Dance = current_Dance;
        Is_Male = is_male;
    }

};

class Customer: public Human
{
    private:
    int Remaining_Hours = 0;
    bool Did_Earn_A_Certificate = false;

    public:
     


    void SetRemainingHours(int hour)
    {
        if(hour<1)
        {
            cout<<"You entered a wrong input. Hour cant be smaller than 1!"<<endl;
        }
        else
        {
            Remaining_Hours = hour;
        }
    }

    void SetCertificate(bool earned)
    {
        Did_Earn_A_Certificate = earned;
    }

    void GetInformation()
    {
        cout<<"Name of the customer: "<<GetName()<<endl;
        cout<<"The remaning hours customer have: "<<Remaining_Hours<<endl;
        cout<<"The current dance that customer is learning: "<<EnumToString(GetCurrentDance())<<endl;
        cout<<"Does customer have a certificate on current dance: "<<Did_Earn_A_Certificate<<endl;

    }

    void Dance() //I'm going to change the cout
    {
        if(GetProfessionOnCurrentDance()<=0)
        {
            cout<<GetName()<<" cant able to dance this moment "<<endl;
        }
        else if(GetProfessionOnCurrentDance()>0 && GetProfessionOnCurrentDance()<5)
        {
            cout<<GetName()<< " is trying to dance "<<endl;
            
        }
        else if(GetProfessionOnCurrentDance()>5 && GetProfessionOnCurrentDance()<10)
        {
            cout<<GetName()<< " can able to dance "<<endl;
        }
        else if(GetProfessionOnCurrentDance()>10)
        {
            cout<<GetName()<< " is dancing really good "<<endl;
        }
        

    }
    
};

class Instructor: public Human 
{
    private:

    int Lesson_Count = 0;

    virtual void SetDanceType(DanceTypes type)
    {
        Current_Dance = type;
        cout<<Name<< "change their dance style"<<endl;
    }

    void DanceWithCustomer() // This function going to be inside of Dance(). Thats why I made it private.
    {
        cout<<Name<<" is dancing with the customer"<<endl;
    }


    void GiveCertificate(Customer customer)
    {
        cout<<Name<<" is giving a certificate to the customer"<<endl;
        customer.SetCertificate(true);
    }


    public:

    void Dance()
    {
        cout<<"Instructor performing "<<GetCurrentDance()<<endl;
    }

    void GetInformation()
    {
        cout<<Name<<" is the instructor of "<<EnumToString(GetCurrentDance())<<" in our dance studio"<<endl;
    }

    virtual void GiveALesson(int PersonNumber, int hour) = 0; // This function is pure virtual because every dance lesson have different parameters

    Instructor(string name, int age, int money, DanceTypes current_Dance) : Human(name, age, money, current_Dance)
    {
        Lesson_Count = 0;
    }
};

int main()
{

    return 0;
}