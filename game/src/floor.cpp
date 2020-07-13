#include "floor.h"

Floor::Floor(int x, int y) : Obj(x, y)
{
    setWidth(3);
    setHeight(2);
    for (size_t _x = 0; _x < getHeight(); _x++)
    {
        for (size_t _y = 0; _y < getWidth(); _y++)
        {
            animation[0][_x][_y] = '#';
        }
    }
}

wchar_t Floor::get_animation(int x, int y)
{
    return animation[0][y][x];
}