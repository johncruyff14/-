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
    void Print(int x,int y,int lx,int ly);//��ʾ�ԣ�x��y��Ϊ���϶��㣬lx��lyΪ�ڲ����Ϳ�ĳ����ο�
protected:
    int AdjustCursorPosition(int X,int Y);//�������λ����(X,Y)
    void HideTheCursor();//���ع��
    void ShowTheCursor();//��ʾ���
    void SetConsoleTextRed();//�����ɫ����
    void SetConsoleTextWrite();//�����ɫ����
};

class SelectionButton:public  Cells{
public:
    bool TryAgain(char wrongMessage[]);//���wrongMessage�Ĵ��󴰿ڲ�ѡ���Ƿ�����
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
    char *menu1[] =//������
    {
        "��½ϵͳ",//0
        "ע���˺�",//1
        "�޸�����",//2
        "ϵͳ˵��", //3
        "��ȫ�˳�", //4
    };
    return selectionButton.MakeSelection(0,4,54,9,0,2,menu1);
}

int Windows::DisplayStudentMenu()
{
    char *menu2[] =//ѧ������
    {
        "��ѯ�ɼ�", //0
        "��Ŀ����", //1
        "ѧԺ����",//2
        "�޸����",//3
        "�˳�ϵͳ"//4
    };
    return selectionButton.MakeSelection(0,4,54,9,0,2,menu2);
}

int Windows::DisplayTeacherMenu()
{
    char *menu3[] =
    {
        "¼����Ŀ�ɼ�", //0
        "���Ӳ���ѧԺ", //1
        "�Զ����ε÷�", //2
        "�޸�ѧ����Ϣ", //3
        "��ѯѧ����Ϣ", //4
        "��Ŀ�ɼ�����", //5
        "ѧԺ�ֱܷ���", //6
        "ɾ��������Ŀ", //7
        "ɾ��ѧ����Ϣ", //8
        "�޸Ĺ������", //9
        "��ȫ�˳�ϵͳ", //10
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
        if(i==x)cout<<"�X";
        cout<<"�T";
    }
    cout<<"�[";
    for(int i=y;i<=y+ly;i++){
        AdjustCursorPosition(x,i+1);
        cout<<"�U";
        AdjustCursorPosition(x+lx,i+1);
        cout<<"�U";
    }
    AdjustCursorPosition(x,y+ly+1);
    for(int i=x;i<x+lx-1;i++){
        if(i==x)cout<<"�^";
        cout<<"�T";
    }
    cout<<"�a";
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
    char *str[]={"����","����"};
    flag=button.MakeSelection(0,1,49,9,1,20,str);
    SetConsoleTextWrite();
    if(flag==0)return 1;//����
    if(flag==1)return 0;//����
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
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE); // ���þ���ṹ���������ʼ��
    pos.X = X; //������������:�������λ��
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
