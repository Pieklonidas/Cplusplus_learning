#include <iostream>

using std::string;

class AbstractEmployee
{
    virtual void AskForPoromotion() = 0;
};

class Employee : AbstractEmployee
{
private:
    string Company;
    int Age;
protected:
    string Name;
public:
    void setName(string name){ Name = name; }
    string getName(){ return Name; }

    void setCompany(string company){ Company = company; }
    string getCompany(){ return Company; }

    void setAge(int age){ if(age >= 18) Age = age; }
    int getAge(){ return Age; }



    void IntroduceYourself()
    {
        std::cout << "Name: " << Name << std::endl;
        std::cout << "Company: " << Company << std::endl;
        std::cout << "Age: " << Age << std::endl;
    }
    Employee(string name, string company, int age)
    {
        Name = name;
        Company = company;
        Age = age;
    }

    virtual void AskForPoromotion()
    {
        if(Age > 30)
        {
            std::cout << Name << " got promoted" << std::endl;
        }
        else
        {
            std::cout << Name << ", sorry NO promotion for you" << std::endl;
        }
    }

    virtual void Work()
    {
        std::cout << Name << " is checking email, task backlog, performing tasks..." << std::endl;
    }
};

class Developer : public Employee
{
public:
    string FavProgrammingLanguage;
    Developer(string name, string company, int age, string language)
        : Employee(name, company, age)
    {
        FavProgrammingLanguage = language;
    }

    void FixBug()
    {
        std::cout << Name << " fixed bug using " << FavProgrammingLanguage << std::endl;
    }

    void Work()
    {
        std::cout << Name << " is writing " << FavProgrammingLanguage << " code" << std::endl;
    }
};

class Teacher : public Employee
{
public:
    string Subject;
    Teacher(string name, string company, int age, string subject)
        : Employee(name, company, age)
    {
        Subject = subject;
    }
    void PrepareLesson()
    {
        std::cout << Name << " is preparing " << Subject << " lesson" << std::endl;
    }

    void Work()
    {
        std::cout << Name << " is teaching " << Subject << std::endl;
    }
};

int main()
{
    Developer d = Developer("Saldina", "YT-CodeBeauty", 25, "C++");
    Teacher t = Teacher("Jack", "Cool School", 35, "History");

    Employee *e1 = &d;
    e1->Work();
    Employee *e2 = &t;
    e2->Work();

    return 0;
}
