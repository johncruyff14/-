#ifndef  PROJECT_H
#define PROJECT_H

#include <string.h>

class Department;
class Project;

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
    char name[18];
    bool isMale;
    char ID[20];
    Grade grade;
    Department* department;
    Project* project;
    int projectNum;
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
        if(studentNumber<1)return;
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
    static Department* ReadDeprtmentFromFile();//返回学院的头指针
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


#endif


