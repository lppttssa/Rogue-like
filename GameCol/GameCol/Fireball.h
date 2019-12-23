#pragma once
#pragma comment(lib, "pdcurses.lib")
#include "curses.h"
#include "Character.h"

class Fireball : public Character {
	char way;
public:
	Fireball(int hp, int damage, char sym, std::pair<int, int> c, char w);

	int Collision(Enemy& enemy) override;
	int Collision(Knight& knight) override;
	int Collision(Wall& wall) override;
	int Collision(GameObject& gameObj) override;
	int Collision(EmptySpace& emptySpace) override;
	int Collision(Princess& princess) override;
	int Collision(Fireball& fireball) override;
	char GetDir();
};