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

		// true - если игрок перекрывает эту дверь, false - иначе
		bool checkCollwithPlayer(Player* p);
		wchar_t get_animation(int x, int y);
		Room* getCurrentRoom() const;

		// Задать связанную дверь перехода и смещение игрока отностительно двери
		void setRef(Door* r, int x_offset, int y_offset);

		Room* toref();
	private:
		Door* refdoor = nullptr;
		int offset_x = 0;
		int offset_y = 0;
		Room* thisroom = nullptr;

	};

	// Проверка со столкновением с дверями. в случае столкновения возращает нужную дверь
	Door* checkCollWithDoors();


	// Создаёт пол на нужной высоте заданной длины
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
	std::vector<Obj*> allobj; // Отрисовка
	std::vector<Obj*> collobj; // Столкновения
	std::vector<Door*> doors;

private:
	int nScreenWidth; // Ширина
	int nScreenHeight; // Высота
};

