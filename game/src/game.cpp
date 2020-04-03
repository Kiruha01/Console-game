#include <Windows.h>
#include <vector>
#include <iostream>

#include "obj.h"
#include "player.h"
#include "floor.h"
#include "room.h"
using namespace std;

int nScreenWidth = 120; // Ширина консольного окна
int nScreenHeight = 30; // Высота консольного окна


wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1]; // Массив для записи в буфер
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана

DWORD dwBytesWritten = 0; // Для дебага

 /*
    TODO:
    исправить прыжок

    */

//=====================================DRAW===============================================

void draw(Player* p, vector<Obj*> objects)//отрисовка
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

    for (int y = 0; y < p->getHeight(); y++)
    {
        for (int x = 0; x < p->getWidth(); x++)
        {
            screen[(p->getY() + y) * nScreenWidth + x + p->getX()] = p->get_animation(x, y);
        }
    }

    screen[nScreenWidth * nScreenHeight] = '\0'; 
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}


//=====================================!DRAW!===============================================



int main()
{
    Player p(10,10);
    SecondRoom mr(&p);

    while (1) {
        Sleep(20);
        bool collisionDn = p.checkCollision(mr.allobj, 0);
        if (!collisionDn)
        {
            p.fall();
        }

        if (p.getY() >= nScreenHeight-2)
            exit(0);

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            if ((p.getX() > 0) && !p.checkCollision(mr.allobj, 2)) --p.getX();
            p.incCounterAnim();
        }
        else if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            if ((p.getX() < 120-3) && !p.checkCollision(mr.allobj, 3)) ++p.getX();
            p.incCounterAnim();
        }
        else
        {
            p.resetCounterAnim();
        }

        if (GetAsyncKeyState((unsigned short)' ') & 0x8000) // Клавишей "W" прыгаем
        {
            if (collisionDn) p.jump();
        }
        //else if (GetAsyncKeyState((unsigned short)'S') & 0x8000) // Клавишей "S" идём назад
        //{
        //    if (p.getY() < 30) ++p.getY();
        //    p.incCounterAnim();
        //}


        draw(&p, mr.allobj);
    }


}
