#pragma once
#include "obj.h"

class Button: public Obj
{
public:
	Button(int x = 25, int y=10);

	wchar_t get_animation(int x, int y);

	bool isActivate = false;

private:

};
