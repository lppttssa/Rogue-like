#pragma once
#pragma comment(lib, "pdcurses.lib")
#include "curses.h"
#include "Character.h"


class Enemy : public Character {
public:
	Enemy(int hp, int damage, char sym, std::pair<int, int> c);

	//bool Collision(Enemy& enemy) override;
	bool Collision(Knight& knight) override;
	bool Collision(Wall& wall) override;
	bool Collision(GameObject& gameObj) override;
	bool Collision(EmptySpace& emptySpace) override;
	bool Collision(Princess& princess) override;
};