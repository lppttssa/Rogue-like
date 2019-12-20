#pragma once
#pragma comment(lib, "pdcurses.lib")
#include "curses.h"
#include "GameObject.h"

class Princess : public GameObject {
public:
	Princess();
	//bool Collision(Knight &knight) override;
	bool Collision(Princess& princess) override;
	bool Collision(Wall& wall) override;
	bool Collision(GameObject& gameObj) override;
	bool Collision(EmptySpace& emptySpace) override;
	bool Collision(Knight& knight) override;
};
