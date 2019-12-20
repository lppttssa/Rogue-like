#include <utility>
#include "Character.h"

Character::Character(int h, int d, int s, std::pair<int, int> c) : hp(h), damage(d), coord(c), GameObject(s) {}

std::pair<int, int> Character::GetPos() {
	return coord;
}

int Character::GetHp() {
	return hp;
}

int Character::GetDamage() {
	return damage;
}

void Character::SetPos(int x, int y) {
	coord = std::make_pair(x, y);
}

void Character::SetHp(int h) {
	hp = h;
}

void Character::SetDamage(int d) {
	damage = d;
}


bool Character::KillCharacter(int d) {
	hp -= d;
	if (hp <= 0) {
		return true;
	}
	return false;
}
