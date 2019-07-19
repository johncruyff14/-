#ifndef  WINDOWS_H
#define WINDOWS_H

#include <windows.h>
#include <iostream>
#include <cstring>

using namespace std;

class Cells{
public:
    void Print(int x,int y,int lx,int ly);//��ʾ�ԣ�x��y��Ϊ���϶��㣬lx��lyΪ�ڲ����Ϳ�ĳ����ο�
private:
    int AdjustCursorPosition(int X,int Y);//�������λ����(X,Y)
    void HideTheCursor();//���ع��
    void ShowTheCursor();//��ʾ���
    void SetConsoleTextRed();//�����ɫ����
    void SetConsoleTextWrite();//�����ɫ����
};

class SelectionButton:public Cells{
public:
    bool TryAgain(char wrongMessage[]);//���wrongMessage�Ĵ��󴰿ڲ�ѡ���Ƿ�����
    int MakeSelection(int from,int to,int x,int y,bool LR,int separate,char *str[]);
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

class InputBox: public Cells{
public:
    void InputChar(int x,int y,char ch[],char* old);
};


#endif


