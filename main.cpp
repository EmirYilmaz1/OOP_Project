#include<iostream>
#include<cmath>
#include<list> //So I thought that list is c++ is exactly same with c#... So after checking runtime I understood that I have to change all list to vector... But I didnt want to delete this line because when I see this I will always remember that I need to check things from internet when Im not sure. 
#include<vector>


using namespace std;

class Human;
class Customer;
class Instructor;

//I made them global because this things are not responsiblity of instructors. Before the class starts system needs to check this
bool CheckClassOfNumber(int customer_number, int max_student_number_for_group);
void BuyHour(int hour, Customer* customer);
void RefundRemaningHours(int hour, Customer* customer);
bool CheckForTheHours(vector<Customer*> customer, int lesson_hour);
bool CheckForThePairs(vector<Customer*> customer) ;

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

    protected:
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
    
    int GetAge()
    {
        return Age;
    }
    
    void SetAge(int age)
    {
      Age = age;
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
    
    virtual void SetProfessionOnCurrentDance(int point, bool is_Changing_Dance_Style = false)
    {

        if(point == 0 && is_Changing_Dance_Style)
        {
            Profession_On_Current_Dance = 0; // If customer changes the dance style the process going to be start zero again.
        }
        else if(point<1)
        {
            cout<<"You entered a wrong input. Hour cannot be smaller than 1!"<<endl;
        }
        else
        {
            Profession_On_Current_Dance += point;
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

        Remaining_Hours += hour;
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
        Remaining_Hours = 10; // Because every customer who joins the studio gets 10 hours in the start
        Certificate = false; 
        Profession_On_Current_Dance = 0;
    }
    
};

class Instructor: public Human 
{
    private:

    int Lesson_Count = 0;
    int Max_Student_Number_For_Group = 0;
    int Cost_Of_Private_Lesson = 0;
    int Level_To_Get_A_Certificate = 0;
    
    protected:
    
    int GetLessonCount()
    {
        return Lesson_Count;
    }

    void SetLessonCount(int increase)
    {
        Lesson_Count += 1;
    }

    int GetMaxStudentNumberForGroup()
    {
        return Max_Student_Number_For_Group;
    }

    void SetMaxStudentNumberForGroup(int number)
    {
        Max_Student_Number_For_Group = number;
    }

    int GetCostOfPrivateLesson()
    {
        return Cost_Of_Private_Lesson;
    }

    void SetCostOfPrivateLesson(int cost)
    {
        Cost_Of_Private_Lesson = cost;
    }

    int GetLevelToGetACertificate()
    {
        return Level_To_Get_A_Certificate;
    }

    void SetLevelToGetACertificate(int level)
    {
        Level_To_Get_A_Certificate = level;
    }

    void DanceWithCustomer() // This function going to be inside of Dance(). Thats why I made c private.
    {
        cout<<GetName()<<" is dancing with the customer"<<endl;
    }


    void GiveCertificate(Customer* customer) // This function going to be inside of Dance(). Thats why I made c private.
    {
        cout<<GetName()<<" is giving a certificate to the "<<customer->GetName()<<endl;
        customer->SetCertificate(true);
    }

    vector<Customer*> CheckForTheLevel(vector<Customer*> customers)
    {
        vector <Customer*>  customers_going_to_get_certificate = {};
        for(Customer* c : customers)
        {
           if(c->GetProfessionOnCurrentDance()>=Level_To_Get_A_Certificate && c->GetCertificate()==false)
           {
                customers_going_to_get_certificate.push_back(c);
           }
        }
        

        return customers_going_to_get_certificate;
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

    void Teach(vector<Customer*> customers, int teaching_Point) 
    {
        int point = teaching_Point; 

        // Every lesson has a small chance of being unsuccesfull.        
        int rate = rand() % 101;
        int possibility = 0;
        
        if(GetAge()>35) // Becuase of the experience some teachers teachs better
        {
            possibility += 5;
            point += 1;
        }

        if(customers.size()>1) // It is a group class
        {         
            int i = rand() % customers.size();
            
            if(rate>15)
            {
                cout<<"The group lesson did go well. ";
                cout<<"But "<<customers[i]->GetName()<<" performed a bad performance"<<endl;
                
                for (int j = 0; j < customers.size(); ++j)                    
                {
                    if (j != i)
                    {
                     customers[j]->SetProfessionOnCurrentDance(point);
                    }
                }
                
            }
            else
            {
                cout<<"The group lesson did not go well. ";
                cout<<"But "<<customers[i]->GetName()<<" performed a good performance"<<endl;  
                customers[i]->SetProfessionOnCurrentDance(point);
            }

        }
        else // It is a private lesson
        {
            point =+ 1; //Private lessons give more experience
            if(rate>10) 
            {
                cout<<customers[0]->GetName()<<" finished the private lesson and performed a good performance"<<endl;
                customers[0]->SetProfessionOnCurrentDance(point);
            }
            else
            {
                cout<<customers[0]->GetName()<<" finished the private lesson. It could have gone better."<<endl;   
            }
        }

        SetLessonCount(1); 
    }

    void GetInformation()
    {
        cout<<GetName()<<" is the instructor of "<<EnumToString(GetCurrentDance())<<" in our dance studio and did "<<Lesson_Count<<" lessons"<<endl;
    }

 

    virtual void GiveAStarterLesson(vector<Customer*>) = 0; // This function is pure virtual because every dance lesson have different parameters and special cout to themselfs
   
   // virtual void GiveAnIntermadiateLesson(vector<Customer*>) = 0;
   // virtual void GiveAPrivateLesson(vector<Customer*>, int money) = 0; 

    Instructor(string name, int age, int money, DanceStyle current_Dance,bool is_male, int max_student_number_for_group, int cost_of_private_lesson, int level_to_get_a_certificate) : Human(name, age, money, current_Dance, is_male)
    {
        Lesson_Count = 0;
        Profession_On_Current_Dance = 999;
        Max_Student_Number_For_Group = max_student_number_for_group;
        Cost_Of_Private_Lesson = cost_of_private_lesson;
        Level_To_Get_A_Certificate = level_to_get_a_certificate;
    }
};

class SalsaInstructor: public Instructor
{

    public:


    void GiveAStarterLesson(vector<Customer*> customers)
    {

       if(CheckClassOfNumber(customers.size(), GetMaxStudentNumberForGroup()))
       {
            if(CheckForThePairs(customers) && CheckForTheHours(customers, 1) )
            {
    
                cout << "Now playing: La Vida Es Un Carnaval" <<endl;
                Dance();
                cout << "The studio becomes silent as the instructor finishes their final spin" << endl;
                cout<<"Now its their turn to perform this dance."<<endl;
                Teach(customers, 1);

                vector<Customer *> customers_going_to_get_certificate = CheckForTheLevel(customers);

                if(customers_going_to_get_certificate.size()>0)
                {
                    for(Customer* c: customers_going_to_get_certificate)
                     GiveCertificate(c);
                }

                customers.clear();

            }
       }

    }


    SalsaInstructor(string name, int age, int salary, DanceStyle dance, bool isCertified, int minAge, int maxAge, int minProfession) : Instructor(name, age, salary, dance, isCertified, minAge, maxAge, minProfession) 
    {

    }

};

int main()
{
    vector<Customer*> customers = {};
    
    Customer* rosy = new Customer("Rosalia", 21, 200, DanceStyle::Salsa, false);
    Customer* emir = new Customer("Emir",20, 100, DanceStyle::Salsa, true);

    SalsaInstructor laura = SalsaInstructor("Laura", 22, 250, DanceStyle::Salsa, false, 10, 30, 1);

    customers.push_back(rosy);
    customers.push_back(emir);


    BuyHour(2,emir);
    RefundRemaningHours(5,emir);

    
    laura.GiveAStarterLesson(customers);

    rosy->GetInformation();
    


}

// I get used to this hierarchy the classes are top of the code and functions are bottom of the code.

bool CheckClassOfNumber(int customer_number, int max_student_number_for_group)
{
     if(customer_number>max_student_number_for_group)
        {
            cout<<"This lesson can done with maximum "<<max_student_number_for_group<<" student."<<endl;
            return false;
        }
        
    return true;
}

void BuyHour(int hour, Customer* customer)
{
   int cost = hour * 20;
    if(customer->GetMoney()>=cost)
    {
        customer->SetMoney(-cost);
        customer->SetRemainingHours(hour) ;
        cout<<customer->GetName()<<" bought "<<hour<<" hours of dance lesson"<<endl;
    }
    else
    {
        cout<<customer->GetName()<<" does not have enough money!"<<endl;
    }

}

void RefundRemaningHours(int hour, Customer* customer)
{
    int money = hour * 5;

    if(customer->GetRemainingHours() >= hour)
    {
        customer->SetMoney(money);
        customer->SetRemainingHours(-hour);
        cout<<customer->GetName()<<" got a refund for "<<hour<<" hours of dance lesson"<<endl;
    }
    else
    {
        cout<<"Customer cant do this refund because customer has"<<customer->GetRemainingHours()<<" hours of lessons"<<endl;
    }
}

bool CheckForTheHours(vector<Customer*> customer, int lesson_hour)
{
    for(Customer* c: customer)
        if(c->GetRemainingHours()<lesson_hour)
        {
            cout<<c->GetName()<<" does not have enough hour for this lesson!"<<endl;
            return false;
        }
    
    for(Customer* c: customer) // if I implemented this above in the else condition if one customer does not have any remaining hour function going to return false.

        c->SetRemainingHours(-lesson_hour);

    

    return true;
}

bool CheckForThePairs(vector<Customer*> customer) 
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
