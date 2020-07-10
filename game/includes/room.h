#pragma once
#include "obj.h"
#include "player.h"
#include "floor.h"
#include <vector>
#include "button.h"

class Room
{
public:
	Room(Player* player, int W = 120, int H = 30);
	

	class Door : public Obj
	{
	public:
		Door(int x, int y, Room* thisrm) : Obj(x, y)
		{
			thisroom = thisrm;
			setWidth(4);
			setHeight(4);
			animation = new wchar_t** [1];
			animation[0] = new wchar_t* [getHeight()];
			for (size_t i = 0; i < getHeight(); i++)
			{
				animation[0][i] = new wchar_t[getWidth()];
				animation[0][i][0] = '[';
				animation[0][i][1] = '_';
				animation[0][i][2] = '_';
				animation[0][i][3] = ']';
			}
		}

		bool checkCollwithPlayer(Player* p)
		{
			if ((p->x + p->getWidth() >= x) && (p->x <= x + getWidth()))
				if ((p->y + p->getHeight() >= y) && p->y <= y + getHeight())
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
			refdoor->getRoom()->getPlayer()->x = refdoor->x + offset_x;
			refdoor->getRoom()->getPlayer()->y = refdoor->y + offset_y;
			return refdoor->getRoom();
		}
	private:
		Door* refdoor = nullptr;
		int offset_x = 0;
		int offset_y = 0;
		Room* thisroom = nullptr;

	};

	// Проверка со столкновением с дверями. в случае столкновения возращает нужную дверь
	//virtual Door* checkCollWithDoors() = 0;


	// Создаёт пол на нужной высоте заданной длины
	void createFloor(int start_x, int end_x, int y);

	void createWall(int x, int start_y, int end_y);

	Player* getPlayer();
	
	std::vector<Obj*> getDrawObjs();

	std::vector<Obj*> getCollObjs();

protected:
	Player* p;
	std::vector<Obj*> allobj; // Отрисовка
	std::vector<Obj*> collobj; // Столкновения

private:
	int nScreenWidth; // Ширина
	int nScreenHeight; // Высота
};


//class MainRoom : public Room
//{
//public:
//	MainRoom(Player* player, int W = 120, int H = 30): Room(player, W, H)
//	{
//		createFloor(2, 110, 26);
//		createWall(2, 10, 26);
//		createWall(107, 10, 26);
//		createFloor(2, 50, 19);
//		createFloor(56, 110, 19);
//		Button* but = new Button(5, 23);
//
//		allobj.push_back(but);
//		toSec = new Door(106, 22, this);
//		allobj.push_back(toSec);
//		p->x = 5;
//		p->y = 23;
//	}
//	Door* toSec;
//
//	Door* checkCollWithDoors()
//	{
//		if (toSec->checkCollwithPlayer(p))
//			return toSec;
//		else
//			return nullptr;
//	}
//};
//
//class SecondRoom : public Room
//{
//public:
//	SecondRoom(Player* player, int W = 120, int H = 30) : Room(player, W, H)
//	{
//		createFloor(2, 120, 26);
//		createWall(2, 10, 26);
//		createWall(116, 10, 26);
//
//		toMain = new Door(2, 22, this);
//		allobj.push_back(toMain);
//		p->x = 5;
//		p->y = 20;
//	}
//	Door* toMain;
//
//	Door* checkCollWithDoors()
//	{
//		if (toMain->checkCollwithPlayer(p))
//			return toMain;
//		else
//			return nullptr;
//	}
//};