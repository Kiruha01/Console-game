#pragma once
#include <vector>
#include "obj.h"

class Player : public Obj
{
public:
    Player(int _x = 60, int _y = 25);

    void jump();

    void fall();

    // �������� ���� ��������
    wchar_t get_animation(int x, int y);
    // 0 - down, 1 - up, 2 - left, 3 - right
    bool checkCollision(std::vector<Obj*> objs, int direction = 0);


    void move()
    {
    }

private:
    bool isjumping = false; // ������� �� ������� ������
    int counter = 0; //������� ��� ���������� ������� � ������

    //wchar_t*** animation;// 0 - stop; 1 - 1st step; 2 - 2nd step
};