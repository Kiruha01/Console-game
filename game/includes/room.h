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
		Door(int x, int y, Room* thisrm);

		// true - ���� ����� ����������� ��� �����, false - �����
		bool checkCollwithPlayer(Player* p);
		wchar_t get_animation(int x, int y);
		Room* getCurrentRoom() const;

		// ������ ��������� ����� �������� � �������� ������ ������������� �����
		void setRef(Door* r, int x_offset, int y_offset);

		Room* toref();
	private:
		Door* refdoor = nullptr;
		int offset_x = 0;
		int offset_y = 0;
		Room* thisroom = nullptr;

	};

	// �������� �� ������������� � �������. � ������ ������������ ��������� ������ �����
	Door* checkCollWithDoors();


	// ������ ��� �� ������ ������ �������� �����
	void createFloor(int start_x, int end_x, int y);
	void createWall(int x, int start_y, int end_y);
	Door* createDoor(int x, int y);

	void addObj(Obj* obj);
	void addDrawObj(Obj* obj);

	Player* getPlayer();
	std::vector<Obj*> getDrawObjs();
	std::vector<Obj*> getCollObjs();

protected:
	Player* p;
	std::vector<Obj*> allobj; // ���������
	std::vector<Obj*> collobj; // ������������
	std::vector<Door*> doors;

private:
	int nScreenWidth; // ������
	int nScreenHeight; // ������
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