#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MaxStrLen=1000;

class Department;
class Project;

template <class T>
T getV(const T& t)
{
    return t;
}

class Grade{
public:

private:
    double Dgrade;
    bool Bgrade;
    bool theHigherTheBetter;
};

class Student{
public:
    Student():name("Null"){}
    Student(char pname[],bool pgender,char pID[]){
        strcpy(name,pname);
        isMale=pgender;
        strcpy(ID,pID);
    }
    void PointProject(Project* pproject){
        project=pproject;
    }
    void InputSingleStudent(char pname[],bool pisMale,char pID[],Grade pgrade,Department* pdepartment,Project* pproject);
    char* getName()  {
        return name;
    }
    bool getGender();
    char* getID();
    Grade getGrade();
    Department* getDepartemnt();
    Project* getProject(){
        return project;
    }
    int getRank();
private:
    char name[1800];
    bool isMale;
    char ID[200];
    Grade grade;
    Department* department;
    Project* project;
    int rank;
};

class Project{
public:
    Project(){
        studentNumber=0;
        student=NULL;
        strcpy(name,"NULL");
        next=NULL;
    }
    Project(int pnum,char pname[],Student* p=NULL){
        studentNumber=pnum;
        student=p;
        strcpy(name,pname);
        next=NULL;
        student = new Student [studentNumber];
    }
    ~Project(){
        delete [] student;
    }
    char* getName();
    void setName(char ch[]);
    Student* getStudent();
    int getNumber();
    void CalculateScore(){};
    Project *next;
private:
    char name[180];
    Student* student;
    int studentNumber;
};

class Department{
public:
    Department();
    char* getName();
    void putName(char ch[]);
    int getNumber();
    Department* getCertainPoint(int i);
    Student* getStudent(int i);
    Department* next;
    static Department* ReadDeprtmentFromFile();
private:
    char name[100];
    Student* student[100];
};

class LinkedListProject{
public:
    LinkedListProject():projectNumber(0),firstProject(new Project){
        firstProject->next=NULL;
    };
    int newProject();
    Project* getOneProject(int n);
    int getProjectNumber();
    Project* getFirstProject();
private:
    Project* firstProject;
    int projectNumber;
};

int LinkedListProject::newProject()
{
    Project* temp=firstProject;
    int t=projectNumber-1;
    while(t--)
    {
        temp=temp->next;
    }
    temp->next=new Project;
    projectNumber++;
    return projectNumber;
}

Project* LinkedListProject::getOneProject(int n)
{
    Project* temp=firstProject;
    while(temp!=NULL)
    {
        if((n--)==0)return temp;
        temp=temp->next;
    }
    return NULL;
}

int LinkedListProject::getProjectNumber()
{
    return projectNumber;
}

Project* LinkedListProject::getFirstProject()
{
    return firstProject;
}


void Student::InputSingleStudent(char pname[],bool pisMale,char pID[],Grade pgrade,Department* pdepartment,Project* pproject)
{
    strcpy(name,pname);
    isMale=pisMale;
    strcpy(ID,pID);
    department=pdepartment;
    project=pproject;
}

Student* Project::getStudent()
{
    return student;
}

bool Student::getGender()
{
    return isMale;
}

char* Student::getID()
{
    return ID;
}

Department* Student::getDepartemnt()
{
    return department;
}

Grade Student::getGrade()
{
    return grade;
}

int Student::getRank()
{
    return rank;
}


char* Project::getName()
{
    return name;
}

void Project::setName(char ch[])
{
    strcpy(name,ch);
}

int Project::getNumber()
{
    return studentNumber;
}

Department::Department()
{
    next=NULL;
}

char* Department::getName()
{
    return name;
}

void Department::putName(char ch[])
{
    strcpy(name,ch);
}

int Department::getNumber()
{
    int i=0;
    Department* p=this;
    while(p){
        i++;
        p=p->next;
    }
    return i;
}

Department* Department::getCertainPoint(int i)
{
    Department* p=this;
    while(i--&&p->next!=NULL){
        p=p->next;
    }
    return p;
}

Student* Department::getStudent(int i)
{
    return student[i];
}

Department* Department::ReadDeprtmentFromFile()
{
    ifstream OpenFile("D.txt");
    if (OpenFile.fail())
    {
        cout<<"打开文件D.txt错误!"<<endl;
        exit(0);
    }
    char ch[100];
    Department *de=new Department();
    Department* p=de;
    bool first=1;
    while(!OpenFile.eof())
    {
        if(!first)
        {
            p->next=new  Department;
            p=p->next;
        }
        OpenFile>>ch;
        p->putName(ch);
        first=false;
    }
    OpenFile.close();
    p=de;
    while(p)
    {
        p=p->next;
    }
    return de;
}
