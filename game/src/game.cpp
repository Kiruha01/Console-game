#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;
int nScreenWidth = 120; // Ширина консольного окна
int nScreenHeight = 30; // Высота консольного окна

class Obj
{
    /*
    TODO:
    переписать создание анимации, через указатели. 
    продумать столкновения. 
    придумать прыжок
    
    */
public:
    Obj(int _x = 60, int _y = 25)
    {
        h = 3;
        w = 3;
        x = _x;
        y = _y;
        animation = new wchar_t**[1];
        animation[0] = new wchar_t* [3];
        for (size_t i = 0; i < 3; i++)
        {
            animation[0][i] = new wchar_t[3];
        }
        counter_of_animation = 0;
        for (size_t x = 0; x < h; x++)
        {
            for (size_t y = 0; y < w; y++)
            {
                animation[0][x][y] = '#';
            }
        }
    };

    // Получить кадр анимации
    virtual wchar_t get_animation(int x, int y)
    {
        return animation[0][y][x];
    };

    int& getX()
    {
        return x;
    }
    int& getY()
    {
        return y;
    }

    // Увеличивает counter_of_animation
    void incCounterAnim() 
    {
        ++counter_of_animation;
    }

    // Сбрасывает counter_of_animation
    void resetCounterAnim()
    {
        counter_of_animation = 0;
    }

    // Высота
    int getHeight() const 
    {
        return h;
    }

    // Ширина
    int getWidth() const 
    {
        return w;
    }

private:
    int x;
    int y;
protected:
    int counter_of_animation; // счётчик анимации
    int amount_animations = 1; // Количество кадров анимации
    int h; // Высота
    int w; // Ширина
    wchar_t*** animation;
};


/* animation:
[ 
  [ . . . ]
  [ . . . ]
  [ . . . ]
]
*/



class Player: public Obj
{
public:
    Player(int _x = 60, int _y = 25): Obj(_x, _y)
    {
        amount_animations = 3;
        h = 3;
        w = 3;

        animation = new wchar_t** [amount_animations];
        for (size_t i = 0; i < amount_animations; i++)
        {
            animation[i] = new wchar_t*[h];
            for (size_t j = 0; j < h; j++)
            {
                animation[i][j] = new wchar_t[w];
            }
        }

        animation[0][0][0] = ' ';
        animation[0][0][1] = '0';
        animation[0][0][2] = ' ';

        animation[0][1][0] = '/';
        animation[0][1][1] = '|';
        animation[0][1][2] = '\\';

        animation[0][2][0] = '/';
        animation[0][2][1] = ' ';
        animation[0][2][2] = '\\';

        animation[1][0][0] = ' ';
        animation[1][0][1] = '0';
        animation[1][0][2] = ' ';
                  
        animation[1][1][0] = ' ';
        animation[1][1][1] = '|';
        animation[1][1][2] = ' ';
                  
        animation[1][2][0] = '/';
        animation[1][2][1] = ' ';
        animation[1][2][2] = '\\';

        animation[2][0][0] = ' ';
        animation[2][0][1] = '0';
        animation[2][0][2] = ' ';
                  
        animation[2][1][0] = ' ';
        animation[2][1][1] = '|';
        animation[2][1][2] = ' ';
                  
        animation[2][2][0] = ' ';
        animation[2][2][1] = '|';
        animation[2][2][2] = ' ';
        
    }

    // Получить кадр анимации
    wchar_t get_animation(int x, int y)
        {
            if (counter_of_animation >= 20) counter_of_animation = 1;
            if (counter_of_animation == 0)
                return animation[0][y][x];
            else
                return animation[(counter_of_animation / 10) + 1][y][x];
        };

private:
    bool isjumping = false; // Прыгает ли человек сейчас

    //wchar_t*** animation;// 0 - stop; 1 - 1st step; 2 - 2nd step
};


class Floor : public Obj
{
public:
    Floor(int _x = 60, int _y = 25) : Obj(_x, _y)
    {
        w = 3;
        h = 2;
        for (size_t x = 0; x < h; x++)
        {
            for (size_t y = 0; y < w; y++)
            {
                animation[0][x][y] = '!';
            }
        }

    }

private:
    //wchar_t animation;
};

wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight + 1]; // Массив для записи в буфер
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана

DWORD dwBytesWritten = 0; // Для дебага



//=====================================DRAW===============================================

void draw(Player* pl, Obj* a)//отрисовка
{
    SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли

    for (size_t _y = 0; _y < nScreenHeight; _y++)
    {
        for (size_t _x = 0; _x < nScreenWidth; _x++)
        {
            screen[_y * nScreenWidth + _x] = ' ';
        }
    }

    for (int y = 0; y < pl->getHeight(); y++)
    {
        for (int x = 0; x < pl->getWidth(); x++)
        {
            screen[(pl->getY() + y)* nScreenWidth + x + pl->getX()] = pl->get_animation(x, y);
        }
    }

    for (int y = 0; y < a->getHeight(); y++)
    {
        for (int x = 0; x < a->getWidth(); x++)
        {
            screen[(a->getY() + y) * nScreenWidth + x + a->getX()] = a->get_animation(x, y);
        }
    }


    screen[nScreenWidth * nScreenHeight] = '\0'; 
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}


//=====================================!DRAW!===============================================



int main()
{
    Player p;

    
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

        draw(&p, &f);
    }

    
}
