#include "room.h"

Room::Room(Player* player, int W, int H)
{

	p = player;
	nScreenHeight = H;
	nScreenWidth = W;
}

Room::Door* Room::checkCollWithDoors()
{
	for (auto dr : this->doors)
	{
		if (dr->checkCollwithPlayer(p))
		{
			return dr;
		}
	}
	return nullptr;
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

Room::Door* Room::createDoor(int x, int y)
{
	Door* dr = new Door(x, y, this);
	this->doors.push_back(dr);
	this->addDrawObj(dr);
	return dr;
}

void Room::addObj(Obj* obj)
{
	this->collobj.push_back(obj);
	this->allobj.push_back(obj);
}

void Room::addDrawObj(Obj* obj)
{
	this->allobj.push_back(obj);
}

Player* Room::getPlayer()
{
	return this->p;
}

std::vector<Obj*> Room::getDrawObjs()
{
	return this->allobj;
}

std::vector<Obj*> Room::getCollObjs()
{
	return this->collobj;
}

Room::Door::Door(int x, int y, Room* thisrm) : Obj(x,y)
{
	this->thisroom = thisrm;
	this->setWidth(4);
	this->setHeight(4);
	this->animation = new wchar_t** [1];
	this->animation[0] = new wchar_t* [getHeight()];
	for (size_t i = 0; i < getHeight(); i++)
	{
		this->animation[0][i] = new wchar_t[getWidth()];
		this->animation[0][i][0] = '[';
		this->animation[0][i][1] = '_';
		this->animation[0][i][2] = '_';
		this->animation[0][i][3] = ']';
	}
}

bool Room::Door::checkCollwithPlayer(Player* p)
{
	if ((p->x + p->getWidth() >= this->x) && (p->x <= this->x + this->getWidth()))
		if ((p->y + p->getHeight() >= this->y) && p->y <= this->y + this->getHeight())
			return true;
	return false;
}

wchar_t Room::Door::get_animation(int x, int y)
{
	return this->animation[0][y][x];
}

Room* Room::Door::getCurrentRoom() const
{
	return this->thisroom;
}

void Room::Door::setRef(Door* r, int x_offset, int y_offset)
{
	this->offset_x = x_offset;
	this->offset_y = y_offset;
	this->refdoor = r;
	return;
}

Room* Room::Door::toref()
{
	this->refdoor->getCurrentRoom()->getPlayer()->x = this->refdoor->x + this->offset_x;
	this->refdoor->getCurrentRoom()->getPlayer()->y = this->refdoor->y + this->offset_y;
	return this->refdoor->getCurrentRoom();
}
