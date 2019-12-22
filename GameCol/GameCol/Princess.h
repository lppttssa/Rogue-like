#pragma once
#pragma comment(lib, "pdcurses.lib")
#include "curses.h"
#include "GameObject.h"

class Princess : public GameObject {
public:
	Princess();
	int Collision(Enemy& enemy) override;
	int Collision(Princess& princess) override;
	int Collision(Wall& wall) override;
	int Collision(GameObject& gameObj) override;
	int Collision(EmptySpace& emptySpace) override;
	int Collision(Knight& knight) override;
};
