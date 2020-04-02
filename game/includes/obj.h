#pragma once

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
        animation = new wchar_t** [1];
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