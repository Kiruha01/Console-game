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
        for (size_t y = 0; y < h; y++)
        {
            for (size_t x = 0; x < w; x++)
            {
                animation[0][y][x] = '#';
            }
        }
    };

    // �������� ���� ��������
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

    // ����������� counter_of_animation
    void incCounterAnim()
    {
        ++counter_of_animation;
    }

    // ���������� counter_of_animation
    void resetCounterAnim()
    {
        counter_of_animation = 0;
    }

    // ������
    int getHeight() const
    {
        return h;
    }

    // ������
    int getWidth() const
    {
        return w;
    }

private:
    int x;
    int y;
protected:
    int counter_of_animation; // ������� ��������
    int amount_animations = 1; // ���������� ������ ��������
    int h; // ������
    int w; // ������
    wchar_t*** animation;
};