#include <Windows.h>
#include <vector>
#include <iostream>

#include "obj.h"
#include "player.h"
#include "floor.h"
using namespace std;
int nScreenWidth = 120; // Ширина консольного окна
int nScreenHeight = 30; // Высота консольного окна


wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1]; // Массив для записи в буфер
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана

DWORD dwBytesWritten = 0; // Для дебага



//=====================================DRAW===============================================

void draw(vector<Obj*> objects)//отрисовка
{
    SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли

    for (size_t _y = 0; _y < nScreenHeight; _y++)
    {
        for (size_t _x = 0; _x < nScreenWidth; _x++)
        {
            screen[_y * nScreenWidth + _x] = ' ';
        }
    }

    for (Obj* a : objects)
    {
        for (int y = 0; y < a->getHeight(); y++)
        {
            for (int x = 0; x < a->getWidth(); x++)
            {
                screen[(a->getY() + y) * nScreenWidth + x + a->getX()] = a->get_animation(x, y);
            }
        }
    }

    screen[nScreenWidth * nScreenHeight] = '\0'; 
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}


//=====================================!DRAW!===============================================



int main()
{
    Player p;
    Floor f(10, 26);

    vector<Obj*> objs;
    objs.push_back(&p);
    objs.push_back(&f);
    
    while (1) {
        Sleep(10);


        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            if (p.getX() > 0) --p.getX();
            p.incCounterAnim();
        }
        else if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            if (p.getX() < 120) ++p.getX();
            p.incCounterAnim();
        }
        else if (GetAsyncKeyState((unsigned short)' ') & 0x8000) // Клавишей "W" идём вперёд
        {
        //    if (p.getY() > 0) --p.getY();
        //    p.incCounterAnim();
        //}
        //else if (GetAsyncKeyState((unsigned short)'S') & 0x8000) // Клавишей "S" идём назад
        //{
        //    if (p.getY() < 30) ++p.getY();
        //    p.incCounterAnim();
        }
        else
        {
            p.resetCounterAnim();
        }

        draw(objs);
    }

    
}
