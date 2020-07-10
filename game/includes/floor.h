#pragma once
#include "obj.h"

class Floor : public Obj
{
public:
    Floor(int x = 60, int y = 25);

    wchar_t get_animation(int x, int y);

private:
    //wchar_t animation;
};