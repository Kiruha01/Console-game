#pragma once
#include "obj.h"

class Button: public Obj
{
public:
	Button(int x = 25, int y=10) : Obj(x, y)
	{
		h = 1;
		w = 2;
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
	};

	wchar_t get_animation(int x, int y)
	{
		if (isActivate)
		{
			return animation[1][y][x];
		}
		else
			return animation[0][y][x];
	}


	bool isActivate = false;

private:

};
