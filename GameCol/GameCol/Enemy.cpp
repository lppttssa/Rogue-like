#include "Enemy.h"
#include "Knight.h"

Enemy::Enemy(int hp, int damage, char sym, std::pair<int, int> c) : Character(hp, damage, sym, c) {}

int Enemy::Collision(Wall& wall) {
	return 0;
}

int Enemy::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int Enemy::Collision(EmptySpace& emptySpace) {
	return 0;
}

int Enemy::Collision(Knight& knight) {
	if (knight.KillCharacter(GetDamage())) {
		clear();
		while (true) {
			printw("LOSER");
			refresh();
		}
	}
	else {
		if (KillCharacter(knight.GetDamage())) {
			return 2;
		}
	}
	return 0;
}

int Knight::Collision(Enemy& enemy) {
	if (KillCharacter(enemy.GetDamage())) {
		clear();
		while (true) {
			printw("LOSER");
			refresh();
		}
	}
	else {
		if (enemy.KillCharacter(GetDamage())) {
			return 3;
		}
	}
	return 0;
}

int Enemy::Collision(Princess& princess) {
	return 0;
}

int Enemy::Collision(Enemy& enemy) {
	return 0;
}

int Enemy::Collision(Fireball& fireball) {
	return 0;
}