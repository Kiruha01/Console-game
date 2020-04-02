#pragma once
#include "obj.h"

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