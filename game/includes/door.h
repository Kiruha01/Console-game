#pragma once
#include "obj.h"

class Door : public Obj
{
public:
	Door(int x, int y) : Obj(x, y)
	{
		w = 4;
		h = 4;
		animation = new wchar_t** [1];
		animation[0] = new wchar_t* [h];
		for (size_t i = 0; i < h; i++)
		{
			animation[0][i] = new wchar_t[w];
			animation[0][i][0] = '[';
			animation[0][i][1] = '_';
			animation[0][i][2] = '_';
			animation[0][i][3] = ']';
		}
	}
	wchar_t get_animation(int x, int y)
	{
		return animation[0][y][x];
	};

};
