#include "..\includes\obj.h"

Obj::Obj(int x, int y)
{
    this->height = 3;
    this->width = 3;
    this->x = x;
    this->y = y;
    this->animation = new wchar_t** [1];
    this->animation[0] = new wchar_t* [3];
    for (size_t i = 0; i < 3; i++)
    {
        this->animation[0][i] = new wchar_t[3];
    }
    resetCounterAnim();
    for (size_t y = 0; y < getHeight(); y++)
    {
        for (size_t x = 0; x < getWidth(); x++)
        {
            this->animation[0][y][x] = '#';
        }
    }
}

wchar_t Obj::get_animation(int x, int y)
{
    return this->animation[0][y][x];
}


void Obj::incCounterAnim()
{
    ++this->counter_of_animation;
}

void Obj::resetCounterAnim()
{
    this->counter_of_animation = 0;
}

int Obj::getHeight() const
{
    return this->height;
}

int Obj::getWidth() const
{
    return this->width;
}

void Obj::setHeight(int height)
{
    this->height = height;
}

void Obj::setWidth(int width)
{
    this->width = width;
}

int Obj::getAmountAnimation()
{
    return this->amount_animations;
}

void Obj::setAmountAnimation(int count)
{
    this->amount_animations = count;
}
