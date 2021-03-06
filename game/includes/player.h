#pragma once
#include <vector>
#include "obj.h"

enum Direct
{
    UP, DOWN, LEFT, RIGHT
};

class Player : public Obj
{
public:
    Player(int _x = 60, int _y = 25);

    void jump();
    void fall();

    // �������� ���� ��������
    wchar_t get_animation(int x, int y);

    // 0 - down, 1 - up, 2 - left, 3 - right
    bool checkCollision(std::vector<Obj*> objs, Direct direction = DOWN);


private:
    bool isjumping = false; // ������� �� ������� ������
    int counter = 0; //������� ��� ���������� ������� � ������
};