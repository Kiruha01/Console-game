#pragma once
#include "obj.h"

class Player : public Obj
{
public:
    Player(int _x = 60, int _y = 25) : Obj(_x, _y)
    {
        amount_animations = 3;
        h = 3;
        w = 3;

        animation = new wchar_t** [amount_animations];
        for (size_t i = 0; i < amount_animations; i++)
        {
            animation[i] = new wchar_t* [h];
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