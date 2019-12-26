#include "Knight.h"
#include "Fireball.h"

Knight::Knight(int hp, int damage, int mh, char sym, std::pair<int, int> c) : Character(hp, damage, sym, c), max_hp(mh) {}

int Knight::GetMaxHp() {
	return max_hp;
}

int Knight::Collision(Wall& wall) {
	return 0;
}

int Knight::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int Knight::Collision(EmptySpace& emptySpace) {
	return 1;
}

int Knight::Collision(Knight& knight) {
	return 1;
}

int Knight::Collision(Princess& princess) {
	clear();
	while (true) {
		printw("WINNER");
		refresh();
	}
}

int Knight::Collision(Fireball& fireball) {
	fireball.SetHp(0);
	if (KillCharacter(fireball.GetDamage())) {
		clear();
		while (true) {
			printw("LOSER");
			refresh();
		}
	}
	return 3;
}

int Fireball::Collision(Knight& knight) {
	SetHp(0);
	if (knight.KillCharacter(GetDamage())) {
		clear();
		while (true) {
			printw("LOSER");
			refresh();
		}
	}
	return 2;
}

int Knight::Collision(AidKit& aidKit) {
	return 0;
}
