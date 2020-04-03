#pragma once
#include "obj.h"
#include "player.h"
#include "floor.h"
#include <vector>

class Room
{
public:
	Room(Player* player, int W = 120, int H = 30)
	{
		p = player;
		nScreenHeight = H;
		nScreenWidth = W;
	}

	// Создаёт пол на нужной высоте заданной длины
	void createFloor(int start_x, int end_x, int y)
	{
		for (size_t i = 0; i < abs(end_x - start_x) / 3; i++)
		{
			Floor* f = new Floor(min(start_x, end_x) + i * 3, y);
			allobj.push_back(f);
		}
	}

	void createWall(int x, int start_y, int end_y)
	{
		for (size_t i = 0; i < abs(end_y - start_y) / 2; i++)
		{
			Floor* w = new Floor(x, min(start_y, end_y) + i * 2);
			allobj.push_back(w);
		}
	}

	std::vector<Obj*> allobj;

protected:
	Player* p;

private:
	int nScreenWidth; // Ширина
	int nScreenHeight; // Высота
};


class MainRoom : public Room
{
public:
	MainRoom(Player* player, int W = 120, int H = 30): Room(player, W, H)
	{
		createFloor(2, 110, 26);
		createWall(2, 10, 26);
		createWall(107, 10, 26);
		createFloor(2, 50, 19);
		createFloor(56, 110, 19);
		p->getX() = 5;
		p->getY() = 23;
	}
};