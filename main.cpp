#include<iostream>
#include<cmath>
#include<list> //So I thought that list is c++ is exactly same with c#... So after checking runtime I understood that I have to change all list to vector... But I didnt want to delete this line because when I see this I will always remember that I need to check things from internet when Im not sure. 
#include<vector>


using namespace std;

class Human;
class Customer;
class Instructor;

enum class DanceStyle // I usualy use enums when I'm programing games thats why also used in this project, I think its way more safer than string.
{
    Salsa,
    Folk,
    HipHop,
};

string EnumToString(DanceStyle dance_Style) 
{
    switch (dance_Style) {

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

void DoTheLesson(Instructor* instructor,vector<Customer*> customers,int lesson_type);
void ChangeCustomerInformation(Customer* customer);
void SelectAndShowInfo(vector<Human*> humans) ;
Customer* CreateANewMembership();
vector<Customer*> ShowAvaliableCustomersForLesson(vector<Customer*> customers, DanceStyle lesson_style);
void GetLesson(int* normal_Page_input ,DanceStyle* dance_Style_Input,bool* isPrivateLesson);
DanceStyle WhichDanceStyle();
Instructor* AssignInstructor(vector<Instructor*> instructors, DanceStyle dance_Style_Of_Lesson);

//I made them global because this things are not responsiblity of instructors. Before the class starts system needs to check this
bool CheckClassOfNumber(int customer_number, int max_student_number_for_group);
void BuyHour(int hour, Customer* customer);
void RefundRemaningHours(int hour, Customer* customer);
bool CheckForTheHours(vector<Customer*> customer, int lesson_hour);
bool CheckForThePairs(vector<Customer*> customer) ;



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
            Profession_On_Current_Dance = 0; // If customer changes the dance dance_Style the process going to be start zero again.
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

    virtual void SetDanceType(DanceStyle dance_Style)
    {
        Current_Dance = dance_Style;
        cout<<Name<< "change their dance dance_Style"<<endl;
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

    void SetDanceType(DanceStyle dance_Style)
    {
       cout<<"System Error! Instructors cant change their current dance dance_Style";
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
            cout << "The student pays " << GetCostOfPrivateLesson() << " for the private lesson." << endl;
            customers[0]->SetMoney(GetCostOfPrivateLesson()); 
            customers[0]->SetProfessionOnCurrentDance(point);
   
        }

        SetLessonCount(1); 
    }

    void GetInformation()
    {
        cout<<GetName()<<" is the instructor of "<<EnumToString(GetCurrentDance())<<" in our dance studio and did "<<Lesson_Count<<" lessons"<<endl;
    }

    void GiveAStarterLesson(vector<Customer*> customers)
    {
    
        PlayStarterMusic();
        Dance();
        PlayStarterMusic();

        Teach(customers, 1);
        vector<Customer*> customers_going_to_get_certificate = CheckForTheLevel(customers);

        if(customers_going_to_get_certificate.size()>0)
        {
            for(Customer* c: customers_going_to_get_certificate)
            GiveCertificate(c);
        }

        customers.clear();       
    }

    void GiveAnIntermadiateLesson(vector<Customer*> customers)
    {
        vector <Customer*> customers_Can_Able_To_Dance = {};
        PlayIntermediateMusic();
        Dance();
        IntermediateLessonStarts();


        for(int i = 0; i<customers.size(); i++)
        {
            if(customers[i]->GetProfessionOnCurrentDance()>4) // We are checking if customers can able to dance like this. Because if it is begginer it cant be possible to do this things;
            {
                customers_Can_Able_To_Dance.push_back(customers[i]);     
            }
            else
            {
                cout<<customers[i]->GetName()<<" cant able to perform these moves. Starter lessons going to be better for learn"<<endl;
            }
        }

        cout<<customers_Can_Able_To_Dance.size()<<" customers can able to perform this dance"<<endl;
        if(customers_Can_Able_To_Dance.size()>0)
        {
            Teach(customers_Can_Able_To_Dance, 2);
        }
        else
        {
            cout<<"There is no customer that can able to perform this dance"<<endl;
            customers.clear();  
            return;
        }

        vector<Customer *> customers_going_to_get_certificate = CheckForTheLevel(customers);
        if(customers_going_to_get_certificate.size()>0)
        {
            for(Customer* c: customers_going_to_get_certificate)
            GiveCertificate(c);
        }

        customers.clear();       
    }

    void GiveAPrivateLesson(vector<Customer*> customers, int money)
    {

        PrivateLessonStarts();
        Teach(customers, 3);
        vector<Customer*> customers_going_to_get_certificate = CheckForTheLevel(customers);
        if(customers_going_to_get_certificate.size()>0)
        {
            for(Customer* c: customers_going_to_get_certificate)
            GiveCertificate(c);
        }

        customers.clear();
    }
 
    virtual void PlayStarterMusic() = 0;
    virtual void StarterLessonStarts() = 0;

    virtual void PlayIntermediateMusic() = 0;
    virtual void IntermediateLessonStarts() = 0;
    
    virtual void PrivateLessonStarts() = 0;

    Instructor(string name, int age, int money, DanceStyle current_Dance,bool is_male, int max_student_number_for_group, int cost_of_private_lesson, int level_to_get_a_certificate) : Human(name, age, money, current_Dance, is_male)
    {
        Lesson_Count = 0;
        Profession_On_Current_Dance = 999;
        Max_Student_Number_For_Group = max_student_number_for_group;
        Cost_Of_Private_Lesson = cost_of_private_lesson;
        Level_To_Get_A_Certificate = level_to_get_a_certificate;
    }
};

// Subclasses of Instructor Class
class SalsaInstructor: public Instructor
{

    public:

        // I generated these couts with AI because I dont have any idea about dance terms...
        void PlayStarterMusic()
        {
            cout << "Now playing: La Vida Es Un Carnaval" <<endl;
        }
        
        void StarterLessonStarts()
        {
            cout << "The studio becomes silent as the instructor finishes their final spin" << endl;
            cout<<"Now its their turn to perform this dance."<<endl;
        }

        void PlayIntermediateMusic()
        {
            cout << "Now playing: El Cantante" << endl;
        }
    
        void IntermediateLessonStarts()
        {
            cout << "The rhythm softens and the instructor’s last giro spins gracefully through the room." << endl; // I got help from AI to generate this couts because I dont have any idea about dance terms...
            cout<<"Now its turn to perform this interesting dance."<<endl;
        }

        void PrivateLessonStarts()
        {
            cout << "The soft beat of the clave fills the room as the instructor guides their student through the basic paso." << endl;
            cout << "With every giro and cross-body lead, the connection between them deepens." << endl;
            cout << "The room pulses with the sabor of salsa, every step flowing with rhythmic precision." << endl;
            cout << "The instructor patiently adjusts the student's timing, helping them feel the music's heartbeat." << endl;
            cout << "Now, the student confidently tries a complex turn, the instructor’s eyes encouraging every move." << endl;
            cout << "As the final note fades, the room is alive with the energy of a lesson well learned." << endl;
            cout << "The instructor smiles, knowing that this private lesson has brought them closer to mastering the salsa." << endl;
        }

    SalsaInstructor(string name, int age, int salary, DanceStyle dance, bool isCertified, int minAge, int maxAge, int minProfession) : Instructor(name, age, salary, dance, isCertified, minAge, maxAge, minProfession) 
    {

    }

};


class FolkInstructor: public Instructor
{

    public:

     // I generated these couts with AI because I dont have any idea about dance terms...
    void PlayStarterMusic()
    {
        cout << "Now playing: 'Çayelinden Öteye' — a traditional folk melody echoes through the studio..." << endl;
    }

    void StarterLessonStarts()
    {
        cout << "The instructor performs a dignified folk routine. The studio holds its breath." << endl;
        cout << "Now it's their turn — the students must carry on the spirit of this dance." << endl;
    }

    void PlayIntermediateMusic()
    {
        cout << "Now playing: 'Vals från Värmland' — a lively folk tune fills the air..." << endl;
    }

    void IntermediateLessonStarts()
    {
        cout << "The hall quiets as the instructor completes their final elegant glide across the floor." << endl;
        cout << "Now it's turn to embrace the rhythm and dance with grace." << endl;
    }

    void PrivateLessonStarts()
    {
        cout << "The warm strains of the saz echo softly as the instructor patiently leads their student through each traditional step." << endl;
        cout << "Every movement carries the weight of generations, passed down with care and pride." << endl;
        cout << "The room feels alive with the heartbeat of folk rhythms, steady and grounded." << endl;
        cout << "The instructor gently corrects the posture, ensuring each step tells its own story." << endl;
        cout << "The student mirrors the instructor’s movements, growing more confident with every beat." << endl;
        cout << "As the final notes linger in the air, a shared sense of heritage fills the studio." << endl;

    }

    FolkInstructor(string name, int age, int salary, DanceStyle dance, bool isCertified, int minAge, int maxAge, int minProfession) : Instructor(name, age, salary, dance, isCertified, minAge, maxAge, minProfession) 
    {
        
    }

};

class HipHopInstructor: public Instructor
{
    public:
    // I generated these couts with AI because I dont have any idea about dance terms...
    void PlayStarterMusic()
    {
        cout << "Now playing: 'Hip Hop Hooray' — the beat drops and the studio comes alive..." << endl;
    }

    void StarterLessonStarts()
    {
        cout << "The instructor finishes their final move, the room buzzing with energy." << endl;
        cout << "Now it's their turn to step up and show what they've got." << endl;
    }
    void PlayIntermediateMusic()
    {
        cout << "Now playing: 'Lose Yourself' — the rhythm intensifies, pushing everyone to their limits..." << endl;
    }

    void IntermediateLessonStarts()
    {
        cout << "The instructor’s last move leaves the room in awe, the energy palpable." << endl;
        cout << "Now it's time to take on the challenge and dance with passion." << endl;
    }

    void PrivateLessonStarts()
    {
        cout << "The bass thumps as the instructor guides their student through the intricate footwork of hip hop." << endl;
        cout << "Every move is sharp, every beat is felt deep in the soul." << endl;
        cout << "The instructor’s eyes are focused, ensuring each step is executed with precision." << endl;
        cout << "The student mirrors the instructor, gaining confidence with every beat." << endl;
        cout << "As the final note fades, the room is charged with the energy of a lesson well learned." << endl;
        cout << "The instructor smiles, knowing that this private lesson has brought them closer to mastering the art of hip hop." << endl;
    }

    HipHopInstructor(string name, int age, int salary, DanceStyle dance, bool isCertified, int minAge, int maxAge, int minProfession) : Instructor(name, age, salary, dance, isCertified, minAge, maxAge, minProfession) 
    {

    }
};

int main()
{
    bool using_Program = true;
    bool isPrivateLesson = false;

    int main_Page_input = 0;
    int normal_Page_input = 0;
    int lesson_Type = -1;

    Instructor* current_Instructor ;

    vector<Customer*> customer_Can_Join_Class = {}; // This vector going to show the customers that have the same dance dance_Style with the lesson
    vector<Customer*> customer_List_Going_To_Enter_Class = {}; // This vector going to contain the customers from customer_Can_Join_Class that are going to attrnd lesson
    
    DanceStyle dance_Style_Input = DanceStyle::Salsa;

    vector<Customer*> customers = {};
    vector<Instructor*> instructors = {};
    
    Customer* rosy = new Customer("Rosalia", 21, 200, DanceStyle::Salsa, false);
    Customer* emir = new Customer("Emir",20, 100, DanceStyle::Salsa, true);
    Customer* hamit = new Customer("Hamit", 22, 150, DanceStyle::Folk, true);
    Customer* elisa = new Customer("Elisa", 19, 50, DanceStyle::Folk, false);
    Customer* carlo = new Customer("Carlo", 27, 90, DanceStyle::HipHop, false);

    SalsaInstructor* laura = new SalsaInstructor("Laura", 22, 250, DanceStyle::Salsa, false, 10, 30, 10);
    FolkInstructor* eren = new FolkInstructor("Eren", 54, 250, DanceStyle::Folk, true, 20, 15, 6);
    HipHopInstructor* giada = new HipHopInstructor("Giada", 30, 300, DanceStyle::HipHop, false, 15, 40, 4);

    customers.push_back(rosy);
    customers.push_back(emir);
    customers.push_back(hamit);
    customers.push_back(elisa);
    customers.push_back(carlo);

    instructors.push_back(eren);
    instructors.push_back(laura);
    instructors.push_back(giada);


    while(using_Program)
    {
        normal_Page_input = 0;
        cout<<"You are currently in main page, whats your action:"<<endl;
        
        cout<<"1)Lesson"<<endl;
        cout<<"2)Customer"<<endl;
        cout<<"3)Instructor"<<endl;

        cout<<"Number: ";
        cin>>main_Page_input;

        switch(main_Page_input)
        {
            case 1:
                    //I'm reseting the values here
                    dance_Style_Input = DanceStyle::Folk;
                    isPrivateLesson = false;
                    current_Instructor = nullptr;
                    customer_Can_Join_Class.clear();
                    customer_List_Going_To_Enter_Class.clear();
                    lesson_Type = -1;


                    GetLesson(&lesson_Type,&dance_Style_Input,&isPrivateLesson);
                    customer_Can_Join_Class = ShowAvaliableCustomersForLesson(customers, dance_Style_Input);
                    current_Instructor = AssignInstructor(instructors, dance_Style_Input);

                    if(customer_Can_Join_Class.size() == 0)
                    {
                        cout<<"There is no customer that can join this lesson"<<endl;
                        break;
                    }

                    cout<<"Please select the customers from list. When you finish it please enter '-1' "<<endl;
                    while(normal_Page_input != -1)
                    {   
                        cin>>normal_Page_input;

                        if(normal_Page_input == -1)
                        break;


                        if( normal_Page_input-1<0  || normal_Page_input - 1>customer_Can_Join_Class.size()) //normal_Page_input - 1 because of the index start with zero and in the ShowCotumer class it starts from
                        {
                            cout<<"You entered a wrong number!!!"<<endl;
                        } 
                        else
                        {
                            bool already_assigned = false;
                            
                            for(int i = 0; i<customer_List_Going_To_Enter_Class.size(); i++) // Checking if the student allready enroll for class
                            {
                                already_assigned = false;
                                if(customer_Can_Join_Class[normal_Page_input-1] == customer_List_Going_To_Enter_Class[i])
                                {
                                    already_assigned = true;
                                    cout<<"This customer already assigned to this lesson"<<endl;
                                    break;
                                }
                            }
                            
                            if(!already_assigned)
                            {
                                customer_List_Going_To_Enter_Class.push_back(customer_Can_Join_Class[normal_Page_input-1]);
                                cout<<customer_Can_Join_Class[normal_Page_input-1]->GetName()<<" assigned to the class"<<endl;   
                            }
                            
                            
                        }

                    }
                    
                    DoTheLesson(current_Instructor, customer_List_Going_To_Enter_Class, lesson_Type);
                    
            break;

            case 2:
                    cout<<"Please select type the action you want to do:"<<endl;
                    cout<<"1) Add a customer."<<endl;
                    cout<<"2) Change information about customer"<<endl;
                    cout<<"3) Get information about customer"<<endl;

                
                    cout<<"Number: ";
                    cin>>normal_Page_input;

                    switch (normal_Page_input)
                    {
                        case 1:
                            customers.push_back(CreateANewMembership());
                            cout<<"New customer added to the system"<<endl;
                            break;

                        case 2:
                            cout<<"Please select the customer"<<endl;
                            for(int i = 0; i<customers.size(); i++)
                            {
                                cout<<i+1<<")"<<customers[i]->GetName()<<endl;
                            }
                            
                            cout<<"Number: ";
                            cin>>normal_Page_input;

                            if(normal_Page_input-1<0 || normal_Page_input-1>customers.size())
                            {
                                cout<<"Error! You entered a wrong Input"<<endl;
                                break;
                            }

                            ChangeCustomerInformation(customers[normal_Page_input-1]);
                        break;
                        case 3:
                            cout<<"Please select the customer "<<endl;
                            for(int i = 0; i<customers.size(); i++)
                            {
                                cout<<i+1<<")"<<customers[i]->GetName()<<endl;
                            }
                            
                            cout<<"Number: ";
                            cin>>normal_Page_input;

                            if(normal_Page_input-1<0 || normal_Page_input-1>customers.size())
                            {
                                cout<<"You entered a wrong number!!!"<<endl;
                                break;
                            }

                            customers[normal_Page_input-1]->GetInformation(); 
                        break;

                        default:
                        cout<<"Error! You typed a number that does not exist"<<endl;
                    }

                   // SelectAndShowInfo(customers);
            break;

            case 3:
                    cout<<"What do you want to do with the Instructor:"<<endl;
                    cout<<"1) Change information about Instructor"<<endl;
                    cout<<"2) Get Information about Instructor"<<endl;
                
                    
                    cout<<"Number: ";
                    cin>>normal_Page_input;

                    switch (normal_Page_input)
                    {


                        case 1:
                            cout<<"Please select the Instructor"<<endl;
                            for(int i = 0; i<instructors.size(); i++)
                            {
                                cout<<i+1<<")"<<instructors[i]->GetName()<<endl;
                            }
                            
                            cout<<"Number: ";
                            cin>>normal_Page_input;

                            if(normal_Page_input-1<0 || normal_Page_input-1>instructors.size())
                            {
                                cout<<"Error! You entered a wrong Input"<<endl;
                                break;
                            }
                            else
                            {

                            }

                        break;

                        case 2:
                            cout<<"Please select the Instructor "<<endl;
                            for(int i = 0; i<instructors.size(); i++)
                            {
                                cout<<i+1<<")"<<instructors[i]->GetName()<<endl;
                            }
                            
                            cout<<"Number: ";
                            cin>>normal_Page_input;

                            if(normal_Page_input-1<0 || normal_Page_input-1>instructors.size())
                            {
                                cout<<"You entered a wrong number!"<<endl;
                                break;
                            }

                            instructors[normal_Page_input-1]->GetInformation();
                        break;

                        default:
                        cout<<"Error! You typed a number that does not exist"<<endl;


                    }
            break;

            default:
                    cout<<"Error! You typed a number that does not exist"<<endl;
                    break;
        }

    }

}

// Functions about Instructor sections
/* void SelectAndShowInfo(vector<Human*> humans) 
{

    cout << "Please select: " << endl;
    for(int i = 0; i < humans.size(); i++) {
        cout << i + 1 << ") " << humans[i]->GetName() << endl;
    }

    int choice;
    cout << "Number: ";
    cin >> choice;

    if(choice < 1 || choice > humans.size()) {
        cout << "You entered a wrong number!!!" << endl;
        return;
    }

    humans[choice - 1]->GetInformation();
}*/

//string name, int age, int money, DanceStyle current_Dance,bool is_male, int max_student_number_for_group, int cost_of_private_lesson, int level_to_get_a_certificate
void ChangeInstructorInformation(Instructor* instructor)
{
    int change_input = 0;
    cout<<"What  you want to change about the Instructor. Please type it"<<endl;
    cout<<"1) Name"<<endl;
    cout<<"2) Age"<<endl;
    cout<<"3) Money"<<endl;
    cout<<"4) Maximum student number for group"<<endl;
    cout<<"5) Cost of private class"<<endl;
    cout<<"6) Level for obtain certificate"<<endl;
    

    cin>>change_input;
    
    switch(change_input)
    {
        case 1:
            cout<<"Please enter the new name of instructor: ";
            instructor->SetName();
            break;
        case 2:
            int age;
            cout<<"Please enter the new age of instructor: ";
            cin>>age;
            instructor->SetAge(age);
            break;

        case 3:
            int money;
            cout<<"Please enter the new money of instructor: ";
            cin>>money;
            instructor->SetMoney(money);
            break;

        case 4:
            instructor->SetDanceType(WhichDanceStyle());
            break;
        case 5:
            int max_student_number_for_group;
            cout<<"Please enter the new maximum student number for group: ";
            cin>>max_student_number_for_group;
            instructor->SetMaxStudentNumberForGroup(max_student_number_for_group);
            break;

        case 6:
            int cost_of_private_lesson;
            cout<<"Please enter the new cost of private lesson: ";
            cin>>cost_of_private_lesson;
            instructor->SetCostOfPrivateLesson(cost_of_private_lesson);
            break;
        case 7:
            int level_to_get_a_certificate;
            cout<<"Please enter the new level to get a certificate: ";
            cin>>level_to_get_a_certificate;
            instructor->SetLevelToGetACertificate(level_to_get_a_certificate);
            break;
        default:
            cout<<"Error! Input not valid"<<endl;
    }
}



//Functions about the Customers Section
Customer* CreateANewMembership() 
{
    string name;
    int age;
    int money;
    int danceStyleInput;
    DanceStyle  dance_Style;
    int genderInput;
    bool gender;

    cout << "Enter customer's name: ";
    cin >> name;
    cout << "Enter customer's age: ";
    cin >> age;
    cout << "Enter customer's money: ";
    cin >> money;

    cout << "Select dance dance_Style (1: Salsa, 2: Folk, 3: HipHop): ";
    cin >> danceStyleInput;

 
    switch (danceStyleInput) 
    {
        case 1:
            dance_Style = DanceStyle::Salsa; 
        break;
        case 2: 
            dance_Style = DanceStyle::Folk; 
        break;
        case 3: 
            dance_Style = DanceStyle::HipHop; 
        break;

        default: 
            cout << "Error! Input is not valid defaulting to Salsa." << endl;
            dance_Style = DanceStyle::Salsa;
        break;
    }

    cout << "Enter gender (1 for male, 0 for female): ";
    cin >> genderInput;

    switch(genderInput) 
    {
        case 0:
            gender = false;
        break;
        case 1:
            gender = true;
        break;
        default:
            cout << "Error! Input is not valid defaulting to female." << endl;
            gender = false;
    }

    return new Customer(name, age, money, dance_Style, gender);
}


void ChangeCustomerInformation(Customer* customer)
{
    int change_input = 0;
    cout<<"What  you want to change about the customer. Please type it"<<endl;
    cout<<"1) Name"<<endl;
    cout<<"2) Age"<<endl;
    cout<<"3) Money"<<endl;
    cout<<"4) Dance Style"<<endl;
    cin>>change_input;
    
    switch(change_input)
    {
        case 1:
            cout<<"Please enter the new name of customer: ";
            customer->SetName();
            break;
        case 2:
            int age;
            cout<<"Please enter the new age of customer: ";
            cin>>age;
            customer->SetAge(age);
            break;

        case 3:
            int money;
            cout<<"Please enter the new money of customer: ";
            cin>>money;
            customer->SetMoney(money);
            break;

        case 4:
            customer->SetDanceType(WhichDanceStyle());
            break;

        default:
            cout<<"Error! Input not valid"<<endl;
    }
}

// Functions about Lesson Section
void DoTheLesson(Instructor* instructor,vector<Customer*> customers,int lesson_type)
{

        if(lesson_type == 3 && customers.size()>1)
        {
            cout<<"Error! The private lesson can be done with only one student!!!"<<endl;
            return;
        }
        if(lesson_type != 3 && customers.size() ==1)
        {
            cout<<"Error! The group lesson can be done with at least two student!!!"<<endl;
            return;
        }


        if(instructor->GetCurrentDance() == DanceStyle::Salsa && lesson_type != 3)    
        if(!CheckForThePairs(customers))
        return;


            
    
        if(CheckClassOfNumber(customers.size(), instructor->GetMaxStudentNumberForGroup()))
       {
            if(CheckForTheHours(customers, 1))
            {
                switch(lesson_type)
                {
                    case 1:
                        instructor->GiveAStarterLesson(customers);
                    break;

                    case 2:
                        instructor->GiveAnIntermadiateLesson(customers);
                    break;
                    case 3:
                        instructor->GiveAPrivateLesson(customers, instructor->GetCostOfPrivateLesson());
                    break;
                }

            }
       }

       customers.clear();
}


void GetLesson(int* normal_Page_input ,DanceStyle* dance_Style_Input,bool* isPrivateLesson)
{
        cout<<"Please select the lesson type you want to do:"<<endl;            
        cout<<"1) Starter."<<endl;
        cout<<"2) Intermadiate"<<endl;
        cout<<"3) Private"<<endl;

        cout<<"Number: ";
        cin>>*normal_Page_input;

        if(*normal_Page_input == 3)
            *isPrivateLesson = true;

        *dance_Style_Input = WhichDanceStyle();
        
}

Instructor* AssignInstructor(vector<Instructor*> instructors, DanceStyle dance_Style_Of_Lesson)
{
    for (int i = 0; i < instructors.size(); i++)
    {
        if (instructors[i]->GetCurrentDance() == dance_Style_Of_Lesson)
        return instructors[i];
    }
    return nullptr;
}


DanceStyle WhichDanceStyle()
{
    int dance_style_input = 0;
    cout<<"Please select the dance dance_Style you want to do:"<<endl;
    cout<<"1) Salsa"<<endl;
    cout<<"2) Folk"<<endl;
    cout<<"3) HipHop"<<endl;

    cout<<"Number: ";
    cin>>dance_style_input;

    switch(dance_style_input)
    {
        case 1:
            return DanceStyle::Salsa;
        case 2:
            return DanceStyle::Folk;
        case 3:
            return DanceStyle::HipHop;
        default:
            cout<<"You entered a wrong input, please try again!"<<endl;
            return WhichDanceStyle(); 
    }
}

vector<Customer*> ShowAvaliableCustomersForLesson(vector<Customer*> customers, DanceStyle lesson_style)
{
    vector<Customer*> customers_can_join = {};
    int customer_count = 0;

    for(Customer* c: customers)
    {
        if(c->GetCurrentDance() == lesson_style) // If customer does not have this dance dance_Style then he can join
        {
            customer_count++;
            cout<<customer_count<<")"<<c->GetName()<<endl;
            customers_can_join.push_back(c);
        }
    }

    return customers_can_join;
}

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
