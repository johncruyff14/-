#include <windows.h>
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;

const int MaxStrLen=1000;

enum
{
    UP=72,
	DOWN=80,
    LEFT=75,
    RIGHT=77,
    ENTER=13
};

class Cells{
public:
    void Print(int x,int y,int lx,int ly);//显示以（x，y）为左上顶点，lx，ly为内部长和宽的长方形框
protected:
    int AdjustCursorPosition(int X,int Y);//调整光标位置至(X,Y)
    void HideTheCursor();//隐藏光标
    void ShowTheCursor();//显示光标
    void SetConsoleTextRed();//输出红色字体
    void SetConsoleTextWrite();//输出白色字体
};

class SelectionButton:public  Cells{
public:
    bool TryAgain(char wrongMessage[]);//输出wrongMessage的错误窗口并选择是否重试
    int MakeSelection(int from,int to,int x,int y,bool LR,int separate,char *str[]);
private:
};

class InputBox: public Cells{
public:
    void InputChar(int x,int y,char ch[],char* old);
};

class Windows{
public:
    int DisplayMainMenu();
    int DisplayStudentMenu();
    int DisplayTeacherMenu();
private:
    Cells cells;
    SelectionButton selectionButton;
};

int Windows::DisplayMainMenu()
{
    cells.Print(30,1,58,3);
    char *menu1[] =//主界面
    {
        "登陆系统",//0
        "注册账号",//1
        "修改密码",//2
        "系统说明", //3
        "安全退出", //4
    };
    return selectionButton.MakeSelection(0,4,54,9,0,2,menu1);
}

int Windows::DisplayStudentMenu()
{
    char *menu2[] =//学生界面
    {
        "查询成绩", //0
        "项目排名", //1
        "学院排名",//2
        "修改年份",//3
        "退出系统"//4
    };
    return selectionButton.MakeSelection(0,4,54,9,0,2,menu2);
}

int Windows::DisplayTeacherMenu()
{
    char *menu3[] =
    {
        "录入项目成绩", //0
        "增加参赛学院", //1
        "自定名次得分", //2
        "修改学生信息", //3
        "查询学生信息", //4
        "项目成绩排名", //5
        "学院总分报表", //6
        "删除单个项目", //7
        "删除学生信息", //8
        "修改管理年份", //9
        "安全退出系统", //10
    };
    return selectionButton.MakeSelection(0,10,50,7,0,1,menu3);
}

int SelectionButton::MakeSelection(int from,int to,int x,int y,bool LR,int separate,char *str[])
{
    HideTheCursor();
    AdjustCursorPosition(x,y);
    int maxLen=0;
    for(int i=from;i<=to;i++)
    {
        if(LR)AdjustCursorPosition(x+separate*(i-from),y);
        else AdjustCursorPosition(x,y+separate*(i-from));
        SetConsoleTextWrite();
        if(i==from)SetConsoleTextRed();
        cout<<str[i-from];
        if(maxLen<strlen(str[i-from]))maxLen=strlen(str[i-from]);
    }
    int flag=from;
    bool out=0;
    char key;
    do
    {
        key=getch();
        if(LR)AdjustCursorPosition(x+separate*(flag-from),y);
        else AdjustCursorPosition(x,y+separate*(flag-from));
        cout<<str[flag-from];
        if(LR&&key==LEFT){
            if(flag-from)flag--;
        }
        if(LR&&key==RIGHT){
            if(flag-to)flag++;
        }
        if(!LR&&key==UP){
            if(flag-from)flag--;
        }
        if(!LR&&key==DOWN){
            if(flag-to)flag++;
        }
        if(key==ENTER)out=1;
        SetConsoleTextRed();
        if(separate==0)
        {
            SetConsoleTextWrite();
            AdjustCursorPosition(x,y);
            for(int i=0;i<maxLen;i++)
                cout<<" ";
        }
        if(LR)AdjustCursorPosition(x+separate*(flag-from),y);
        else AdjustCursorPosition(x,y+separate*(flag-from));
        cout<<str[flag-from];
        SetConsoleTextWrite();
    }
    while(!out);
    return flag;
}

void Cells::Print(int x,int y,int lx,int ly)
{
    AdjustCursorPosition(x,y);
    for(int i=x;i<x+lx-1;i++){
        if(i==x)cout<<"╔";
        cout<<"═";
    }
    cout<<"╗";
    for(int i=y;i<=y+ly;i++){
        AdjustCursorPosition(x,i+1);
        cout<<"║";
        AdjustCursorPosition(x+lx,i+1);
        cout<<"║";
    }
    AdjustCursorPosition(x,y+ly+1);
    for(int i=x;i<x+lx-1;i++){
        if(i==x)cout<<"╚";
        cout<<"═";
    }
    cout<<"╝";
}

bool SelectionButton::TryAgain(char wrongMessage[])
{
    HANDLE handle;
    HideTheCursor();
    handle= GetStdHandle(STD_OUTPUT_HANDLE);
    bool flag=0,out=0;
    int len=strlen(wrongMessage);
    char key;
    system("cls");
    SetConsoleTextWrite();
    Print(30,2,61,3);
    AdjustCursorPosition(61-len/2,4);
    cout<<wrongMessage;
    SelectionButton button;
    char *str[]={"重试","返回"};
    flag=button.MakeSelection(0,1,49,9,1,20,str);
    SetConsoleTextWrite();
    if(flag==0)return 1;//重试
    if(flag==1)return 0;//返回
}

void Cells::HideTheCursor() {
    CONSOLE_CURSOR_INFO cciCursor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
        cciCursor.bVisible = FALSE;
        SetConsoleCursorInfo(hStdOut, &cciCursor);
    }
}

void Cells::ShowTheCursor() {
    CONSOLE_CURSOR_INFO cciCursor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleCursorInfo(hStdOut, &cciCursor)) {
        cciCursor.bVisible = TRUE;
        SetConsoleCursorInfo(hStdOut, &cciCursor);
    }
}

int Cells::AdjustCursorPosition(int X,int Y){
    COORD pos = { 0,0 };
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE); // 设置句柄结构体变量并初始化
    pos.X = X; //下面三句作用:调整光标位置
    pos.Y = Y;
    SetConsoleCursorPosition(handle, pos);
    return 0;
}

void Cells::SetConsoleTextRed(){
    HANDLE handle;
    SetConsoleTextAttribute(handle,FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Cells::SetConsoleTextWrite(){
    HANDLE handle;
    SetConsoleTextAttribute(handle,FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE| FOREGROUND_INTENSITY);
}

void InputBox::InputChar(int x,int y,char ch[],char* old)
{
    AdjustCursorPosition(x,y);
    cout<<ch;
    cin>>old;
}
