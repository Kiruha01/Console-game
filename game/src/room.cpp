#include "room.h"

Room::Room(Player* player, int W, int H)
{

	p = player;
	nScreenHeight = H;
	nScreenWidth = W;
}

void Room::createFloor(int start_x, int end_x, int y)
{
	if (end_x < start_x)
		std::swap(end_x, start_x);
	for (size_t i = 0; i < abs(end_x - start_x) / 3; i++)
	{
		Floor* f = new Floor(start_x + i * 3, y);
		allobj.push_back(f);
		collobj.push_back(f);
	}
}

void Room::createWall(int x, int start_y, int end_y)
{
	if (end_y < start_y)
		std::swap(end_y, start_y);
	for (size_t i = 0; i < abs(end_y - start_y) / 2; i++)
	{
		Floor* w = new Floor(x, start_y + i * 2);
		allobj.push_back(w);
		collobj.push_back(w);
	}
}

Player* Room::getPlayer()
{
	return p;
}

std::vector<Obj*> Room::getDrawObjs()
{
	return allobj;
}

std::vector<Obj*> Room::getCollObjs()
{
	return collobj;
}
