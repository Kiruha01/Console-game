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
	

	class Door : public Obj
	{
	public:
		Door(int x, int y, Room* thisrm) : Obj(x, y)
		{
			thisroom = thisrm;
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

		bool checkCollwithPlayer(Player* p)
		{
			if ((p->getX() + p->getWidth() >= getX()) && (p->getX() <= getX() + getWidth()))
				if ((p->getY() + p->getHeight() >= getY()) && p->getY() <= getY() + getHeight())
					return true;
			return false;
		}

		wchar_t get_animation(int x, int y)
		{
			return animation[0][y][x];
		}

		Room* getRoom() const
		{
			return thisroom;
		}

		// Задать дверь комнаты перехода и смещение игрока отностительно двери
		void setRef(Door* r, int x_offset, int y_offset)
		{
			offset_x = x_offset;
			offset_y = y_offset;
			refdoor = r;
			return;
		}

		Room* toref()
		{
			refdoor->getRoom()->getPl()->getX() = refdoor->getX() + offset_x;
			refdoor->getRoom()->getPl()->getY() = refdoor->getY() + offset_y;
			return refdoor->getRoom();
		}
	private:
		Door* refdoor = nullptr;
		int offset_x = 0;
		int offset_y = 0;
		Room* thisroom = nullptr;

	};

	// Проверка со столкновением с дверями. в случае столкновения возращает нужную дверь
	virtual Door* checkCollWithDoors() = 0;


	// Создаёт пол на нужной высоте заданной длины
	void createFloor(int start_x, int end_x, int y)
	{
		for (size_t i = 0; i < abs(end_x - start_x) / 3; i++)
		{
			Floor* f = new Floor(min(start_x, end_x) + i * 3, y);
			allobj.push_back(f);
			collobj.push_back(f);
		}
	}

	void createWall(int x, int start_y, int end_y)
	{
		for (size_t i = 0; i < abs(end_y - start_y) / 2; i++)
		{
			Floor* w = new Floor(x, min(start_y, end_y) + i * 2);
			allobj.push_back(w);
			collobj.push_back(w);
		}
	}

	Player* getPl()
	{
		return p;
	}
	
	std::vector<Obj*> getDrawObjs()
	{
		return allobj;
	}

	std::vector<Obj*> getCollObjs()
	{
		return collobj;
	}

protected:
	Player* p;
	std::vector<Obj*> allobj; // Отрисовка
	std::vector<Obj*> collobj; // Столкновения

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

		toSec = new Door(106, 22, this);
		allobj.push_back(toSec);
		p->getX() = 5;
		p->getY() = 23;
	}
	Door* toSec;

	Door* checkCollWithDoors()
	{
		if (toSec->checkCollwithPlayer(p))
			return toSec;
		else
			return nullptr;
	}
};

class SecondRoom : public Room
{
public:
	SecondRoom(Player* player, int W = 120, int H = 30) : Room(player, W, H)
	{
		createFloor(2, 120, 26);
		createWall(2, 10, 26);
		createWall(116, 10, 26);

		toMain = new Door(2, 22, this);
		allobj.push_back(toMain);
		p->getX() = 5;
		p->getY() = 20;
	}
	Door* toMain;

	Door* checkCollWithDoors()
	{
		if (toMain->checkCollwithPlayer(p))
			return toMain;
		else
			return nullptr;
	}
};