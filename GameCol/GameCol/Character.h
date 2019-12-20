#pragma once
#include <utility>
#include "GameObject.h"

class Character : public GameObject {
	int hp;
	int damage;
	std::pair<int, int> coord;

public:
	Character(int h, int d, int s, std::pair<int, int> coord = std::pair<int, int>(0, 0));

	std::pair<int, int> GetPos();

	int GetHp();

	int GetDamage();

	char GetSym();

	void SetPos(int x, int y);

	void SetHp(int h);

	void SetDamage(int d);

	void SetSym(char s);

	bool KillCharacter(int d);
};