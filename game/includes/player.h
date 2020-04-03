#pragma once
#include <vector>
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

    void jump()
    {
        if (!isjumping)
        {
            isjumping = true;
            
        }
    }

    void fall()
    {
        if (counter == 0)
            ++getY();
        counter = (++counter) % 3;

    }

    // Получить кадр анимации
    wchar_t get_animation(int x, int y)
    {
        if (counter_of_animation >= 20) counter_of_animation = 1;
        if (counter_of_animation == 0)
            return animation[0][y][x];
        else
            return animation[(counter_of_animation / 10) + 1][y][x];
    }
    // 0 - down, 1 - up, 2 - left, 3 - right
    bool checkCollision(std::vector<Obj*> objs, int direction = 0)
    {
 


        bool isColl = false;
        for (int i = 0; i < objs.size(); ++i)
        {
            if (isColl) break;
            Obj* o = objs[i];
            switch (direction)
            {
            case 0:
                // Костыль: ПРыгаем
                if ((isjumping) && (counter < 7) && (!checkCollision(objs, 1)))
                {
                    --getY();
                    ++counter;
                }
                else
                {
                    isjumping = false;
                    counter = 0;
                }

                if ((isjumping) || ((getY() + h) == o->getY()) && (getX() + getWidth() > o->getX()) && (o->getX() + o->getWidth() > getX()))
                {
                    isColl = true;
                }
                break;
            case 1:
                if ((getY() == o->getY() + o->getHeight()) && (getX() + getWidth() > o->getX()) && (o->getX() + o->getWidth() > getX()))
                    isColl = true;
            case 2:
                if ((o->getX() + o->getWidth() == getX()) && (o->getY() + o->getHeight() > getY()) && (o->getY() < getY() + getHeight()))
                    isColl = true;
                break;
            case 3:
                if ((o->getX()  == getX() + getWidth()) && (o->getY() + o->getHeight() > getY()) && (o->getY() < getY() + getHeight()))
                    isColl = true;
                break;
            default:
                isColl = false;
                break;
            }
        }
        return isColl;
    }


    void move()
    {

    }

private:
    bool isjumping = false; // Прыгает ли человек сейчас
    int counter = 0; //счетчик для замедления подения и прыжка

    //wchar_t*** animation;// 0 - stop; 1 - 1st step; 2 - 2nd step
};