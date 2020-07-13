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
    Дверь с кнопкой

    */

//=====================================DRAW===============================================

void draw(Room* r)//отрисовка
{
    SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли

    for (size_t _y = 0; _y < nScreenHeight; _y++)
    {
        for (size_t _x = 0; _x < nScreenWidth; _x++)
        {
            screen[_y * nScreenWidth + _x] = ' ';
        }
    }

    for (Obj* a : r->getDrawObjs())
    {
        for (int y = 0; y < a->getHeight(); y++)
        {
            for (int x = 0; x < a->getWidth(); x++)
            {
                if (a->get_animation(x, y) != ' ')
                    screen[(a->y + y) * nScreenWidth + x + a->x] = a->get_animation(x, y);
            }
        }
    }

    for (int y = 0; y < r->getPlayer()->getHeight(); y++)
    {
        for (int x = 0; x < r->getPlayer()->getWidth(); x++)
        {
            if (r->getPlayer()->get_animation(x, y) != ' ')
                screen[(r->getPlayer()->y + y) * nScreenWidth + x + r->getPlayer()->x] = r->getPlayer()->get_animation(x, y);
        }
    }

    screen[nScreenWidth * nScreenHeight] = '\0'; 
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}


//=====================================!DRAW!===============================================


Room* createRooms(Player* pl)
{
    Room* mr = new Room(pl);
    mr->createFloor(2, 110, 26);
    mr->createWall(2, 10, 26);
    mr->createWall(107, 10, 26);
    mr->createFloor(2, 45, 19);
    mr->createFloor(56, 110, 19);
    Room::Door* door_fromMain_toSecond = mr->createDoor(106, 15);

    Room* sr = new Room(pl);
    sr->createFloor(2, 110, 26);
    sr->createWall(2, 10, 26);
    sr->createWall(107, 10, 26);
    Room::Door* door_fromSecond_toMain = sr->createDoor(2, 22);

    door_fromMain_toSecond->setRef(door_fromSecond_toMain, 5, 0);
    door_fromSecond_toMain->setRef(door_fromMain_toSecond, -5, 0);



    return mr;
}


int main()
{
    Player p(10,10);
    Room* mr = createRooms(&p);

    Room* currentRoom = mr;


    while (1) {
        draw(currentRoom);
        Sleep(20);
        bool collisionDn = p.checkCollision(currentRoom->getCollObjs(), DOWN);
        if (!collisionDn)
        {
            p.fall();
        }

        if (p.y >= nScreenHeight-2)
            exit(0);

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            if ((p.x > 0) && !p.checkCollision(currentRoom->getCollObjs(), LEFT))
            {
                --p.x;
                Room::Door* curDoor = currentRoom->checkCollWithDoors();
                if (curDoor)
                {
                    currentRoom = curDoor->toref();
                    continue;
                }
            }
            p.incCounterAnim();
        }
        else if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            if ((p.x < 120 - 3) && !p.checkCollision(currentRoom->getCollObjs(), RIGHT))
            {
                ++p.x;
                Room::Door* curDoor = currentRoom->checkCollWithDoors();
                if (curDoor)
                {
                    currentRoom = curDoor->toref();
                    continue;
                }
            }
            p.incCounterAnim();
        }
        else
        {
            p.resetCounterAnim();
        }

        if (GetAsyncKeyState((unsigned short)' ') & 0x8000) // Клавишей " " прыгаем
        {
            if (collisionDn) p.jump();
        }

    }

}
