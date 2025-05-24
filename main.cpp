#include<iostream>
#include<cmath>
#include<list>

using namespace std;

void BuyHour(int hour, Customer customer);
void RefundRemaningHours(int hour, Human& human);
bool CheckForTheHours(list<Customer*> customer, int lesson_hour);
bool CheckForThePairs(list<Customer*> customer) ;

enum class DanceStyle // I usualy use enums when I'm programing games thats why also used in this project, I think its way more safer than string.
{
    Salsa,
    Folk,
    HipHop,
    Ballet
};

string EnumToString(DanceStyle style) 
{
    switch (style) {
        case DanceStyle::Ballet: 
        return "Ballet";
        
        case DanceStyle::HipHop: 
        return "HipHop";
        
        case DanceStyle::Salsa: 
        return "Salsa";
        
        case DanceStyle::Folk: 
        return "Folk";

        default: 
        return "ErrorCode#010 In the system this customer does not have any dance program!";
    }
}


class Human
{
    private:

    string Name = "";
    int Age = 0;
    int Money = 0 ;
    bool Is_Male = false;

    DanceStyle Current_Dance;
    int Profession_On_Current_Dance = 0;

    public:

    string GetName()
    {
        return Name;
    }

    void SetName()
    {
        cout<<"Please enter the new name of customer: ";
        cin>>Name;
    }    

    void SetMoney(int money)
    {   
        Money += money;
    }

    int GetMoney()
    {
        return Money;
    }

    bool GetGender()
    {
        return Is_Male;
    }

    int GetProfessionOnCurrentDance()
    {
        return Profession_On_Current_Dance;
    }
    
    void SetProfessionOnCurrentDance(int hour, bool is_Changing_Dance_Style = false)
    {

        if(hour = 0 && is_Changing_Dance_Style)
        {
            Profession_On_Current_Dance = 0; // If customer changes the dance style the process going to be start zero again.
        }
        else if(hour<1)
        {
            cout<<"You entered a wrong input. Hour cannot be smaller than 1!"<<endl;
        }
        else
        {
            Profession_On_Current_Dance += hour;
        }
    }

    DanceStyle GetCurrentDance()
    {
        return Current_Dance;
    }

    virtual void SetDanceType(DanceStyle style)
    {
        Current_Dance = style;
        cout<<Name<< "change their dance style"<<endl;
        SetProfessionOnCurrentDance(0,true);
    }




    virtual void GetInformation() = 0;
    virtual void Dance() = 0;


    Human(string name, int age, int money, DanceStyle current_Dance, bool is_male)
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
    bool Certificate = false;

    public:
     
    int GetRemainingHours()
    {
        return Remaining_Hours;
    }

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

    bool GetCertificate()
    {
        return 
        Certificate;
    }

    void SetCertificate(bool earned)
    {
        
        Certificate = earned;
    }
    
    
    void GetInformation()
    {
        cout<<"Name of the customer: "<<GetName()<<endl;
        cout<<"The remaning hours customer have: "<<GetRemainingHours()<<endl;
        cout<<"The current dance that customer is learning: "<<EnumToString(GetCurrentDance())<<endl;
        cout<<"Does customer have a certificate on current dance: "<<GetCertificate()<<endl;

    }

    void Dance() //I'm going to change the couts
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

    Customer(string name, int age, int money, DanceStyle current_Dance, bool is_male): Human(name,age,money,current_Dance,is_male)
    {
        Remaining_Hours = 10 // Because every customer who joins the studio gets 10 hours in the start;
        Certificate = false; 
    }
    
};

class Instructor: public Human 
{
    private:
    int Lesson_Count = 0;
    
    protected:
    void DanceWithCustomer() // This function going to be inside of Dance(). Thats why I made c private.
    {
        cout<<GetName()<<" is dancing with the customer"<<endl;
    }

    void GiveCertificate(Customer& customer) // This function going to be inside of Dance(). Thats why I made c private.
    {
        cout<<GetName()<<" is giving a certificate to the customer"<<endl;
        customer.SetCertificate(true);
    }


    public:

    void SetDanceType(DanceStyle style)
    {
       cout<<"System Error! Instructors cant change their current dance style";
    }

    void Dance()
    {
        cout<<"Instructor performing "<<EnumToString(GetCurrentDance())<<endl;
    }

    void GetInformation()
    {
        cout<<GetName()<<" is the instructor of "<<EnumToString(GetCurrentDance())<<" in our dance studio"<<endl;
    }

    virtual void GiveALesson(int personNumber, int hour, int max_student_number) = 0; // This function is pure virtual because every dance lesson have different parameters

    Instructor(string name, int age, int money, DanceStyle current_Dance,bool is_male) : Human(name, age, money, current_Dance, is_male)
    {
        Lesson_Count = 0;
    }
};

class SalsaInstructor: public Instructor
{
    void GiveALesson(int personNumber, int hour)
    {

    }
};


void BuyHour(int hour, Customer customer)
{
   int cost = hour * 20;
    if(customer.GetMoney()>=cost)
    {
        customer.SetMoney(-cost);
        customer.SetRemainingHours(hour);
        cout<<customer.GetName()<<" bought "<<hour<<" hours of dance lesson"<<endl;
    }
    else
    {
         cout<<customer.GetName()<<" does not have enough money!"<<endl;
    }

}

void RefundRemaningHours(int hour, Human& human)
{
    int money = hour * 5;
    human.SetMoney(money);
    cout<<human.GetName()<<" refunded "<<hour<<" hours of dance lesson"<<endl;
}


bool CheckForTheHours(list<Customer*> customer, int lesson_hour)
{
    for(Customer* c: customer)
        if(c->GetRemainingHours()<lesson_hour)
        {
            cout<<c->GetName()<<" does not have any remaining hours!"<<endl;
            return false;
        }
    
    for(Customer* c: customer) // if I implemented this above in the else condition if one customer does not have any remaining hour function going to return false.

        c->SetRemainingHours(-lesson_hour);

    

    return true;
}

bool CheckForThePairs(list<Customer*> customer) 
{
    int male_counter = 0;
    int female_counter = 0;

    for(Customer* c: customer)
    {
        if(c->GetGender()) // If it is true so this means its male;
        {
            male_counter++;
        }
        else
        {
            female_counter++;
        }
        
    }

    if(female_counter == male_counter)
    {
        return true;
    }
    else
    {
        cout<<"The lesson cant be done because there are no equal customer number to make pairs"<<endl;
        return false;
    }
}

int main()
{
    list<customers> customers = {};
    
    return 0;
}