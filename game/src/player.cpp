#include "player.h"
#define HIGHTofJUMPING 8

Player::Player(int _x, int _y) : Obj(_x, _y)
{
    setAmountAnimation(3);
    setHeight(3);
    setWidth(3);

    animation = new wchar_t** [getAmountAnimation()];
    for (size_t i = 0; i < getAmountAnimation(); i++)
    {
        animation[i] = new wchar_t* [getHeight()];
        for (size_t j = 0; j < getHeight(); j++)
        {
            animation[i][j] = new wchar_t[getWidth()];
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

void Player::jump()
{
    if (!this->isjumping)
    {
        this->isjumping = true;

    }
}

void Player::fall()
{
    if (this->counter == 0)
        ++y;
    this->counter = (++this->counter) % getAmountAnimation();

}

wchar_t Player::get_animation(int x, int y)
{
    if (counter_of_animation >= 20) counter_of_animation = 1;
    if (counter_of_animation == 0)
        return animation[0][y][x];
    else
        return animation[(counter_of_animation / 10) + 1][y][x];
}

// 0 - down, 1 - up, 2 - left, 3 - right
bool Player::checkCollision(std::vector<Obj*> objs, Direct direction)
{
    bool isColl = false;
    for (int i = 0; i < objs.size(); ++i)
    {
        if (isColl) break;
        Obj* o = objs[i];
        switch (direction)
        {
        case DOWN:
            // Костыль: ПРыгаем
            if ((isjumping) && (counter < HIGHTofJUMPING) && (!checkCollision(objs, UP)))
            {
                --y;
                ++counter;
            }
            else
            {
                isjumping = false;
                counter = 0;
            }

            if ((isjumping) || ((y + getHeight()) == o->y) && (x + getWidth() > o->x) && (o->x + o->getWidth() > x))
            {
                isColl = true;
            }
            break;
        case UP:
            if ((y == o->y + o->getHeight()) && (x + getWidth() > o->x) && (o->x + o->getWidth() > x))
                isColl = true;
        case LEFT:
            if ((o->x + o->getWidth() == x) && (o->y + o->getHeight() > y) && (o->y < y + getHeight()))
                isColl = true;
            break;
        case RIGHT:
            if ((o->x == x + getWidth()) && (o->y + o->getHeight() > y) && (o->y < y + getHeight()))
                isColl = true;
            break;
        default:
            isColl = false;
            break;
        }
    }
    return isColl;
}