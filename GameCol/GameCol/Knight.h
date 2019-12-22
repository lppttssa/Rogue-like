#pragma once
#pragma comment(lib, "pdcurses.lib")
#include "curses.h"
#include "Character.h"

class Enemy;
class Knight : public Character {
public:
	Knight(int hp, int damage, char sym, std::pair<int, int> c);

	int Collision(Enemy& enemy) override;
	int Collision(Knight& knight) override;
	int Collision(Wall& wall) override;
	int Collision(GameObject& gameObj) override;
	int Collision(EmptySpace& emptySpace) override;
	int Collision(Princess& princess) override;
};