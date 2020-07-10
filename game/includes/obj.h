#pragma once

class Obj
{

    /*

    Ф____ - x,y - anchor point
    |   |
    |   |
    |___|
 
 */
   
public:
    Obj(int _x = 60, int _y = 25);

    // Получить кадр анимации
    virtual wchar_t get_animation(int x, int y);

    // Увеличивает counter_of_animation
    void incCounterAnim();

    // Сбрасывает counter_of_animation
    void resetCounterAnim();

    // Высота
    int getHeight() const;

    // Ширина
    int getWidth() const;

    int x;
    int y;
protected:
    int counter_of_animation; // счётчик анимации
    wchar_t*** animation;

    void setHeight(int height);
    void setWidth(int width);
    int getAmountAnimation();
    void setAmountAnimation(int count);
private:
    int amount_animations = 1; // Количество кадров анимации
    int height; // Высота
    int width; // Ширина
};