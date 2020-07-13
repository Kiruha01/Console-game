#include "button.h"

Button::Button(int x, int y) : Obj(x, y)
{
	setHeight(1);
	setWidth(2);
	animation = new wchar_t** [2];
	for (size_t i = 0; i < 2; i++)
	{
		animation[i] = new wchar_t* [1];
		animation[i][0] = new wchar_t[2];
	}

	animation[0][0][0] = '}';
	animation[0][0][1] = ']';
	animation[1][0][0] = ']';
	animation[1][0][1] = ' ';
}

wchar_t Button::get_animation(int x, int y)
{
	if (isActivate)
	{
		return animation[1][y][x];
	}
	else
		return animation[0][y][x];
}
