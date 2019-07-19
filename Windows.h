#ifndef  WINDOWS_H
#define WINDOWS_H

#include <windows.h>
#include <iostream>
#include <cstring>

using namespace std;

class Cells{
public:
    void Print(int x,int y,int lx,int ly);//显示以（x，y）为左上顶点，lx，ly为内部长和宽的长方形框
private:
    int AdjustCursorPosition(int X,int Y);//调整光标位置至(X,Y)
    void HideTheCursor();//隐藏光标
    void ShowTheCursor();//显示光标
    void SetConsoleTextRed();//输出红色字体
    void SetConsoleTextWrite();//输出白色字体
};

class SelectionButton:public Cells{
public:
    bool TryAgain(char wrongMessage[]);//输出wrongMessage的错误窗口并选择是否重试
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


