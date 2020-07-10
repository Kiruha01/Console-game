#pragma once

class Obj
{

    /*

    �____ - x,y - anchor point
    |   |
    |   |
    |___|
 
 */
   
public:
    Obj(int _x = 60, int _y = 25);

    // �������� ���� ��������
    virtual wchar_t get_animation(int x, int y);

    // ����������� counter_of_animation
    void incCounterAnim();

    // ���������� counter_of_animation
    void resetCounterAnim();

    // ������
    int getHeight() const;

    // ������
    int getWidth() const;

    int x;
    int y;
protected:
    int counter_of_animation; // ������� ��������
    wchar_t*** animation;

    void setHeight(int height);
    void setWidth(int width);
    int getAmountAnimation();
    void setAmountAnimation(int count);
private:
    int amount_animations = 1; // ���������� ������ ��������
    int height; // ������
    int width; // ������
};