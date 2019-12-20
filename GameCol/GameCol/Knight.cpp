#include "Knight.h"

Knight::Knight(int hp, int damage, char sym, std::pair<int, int> c) : Character(hp, damage, sym, c) {}

bool Knight::Collision(Wall& wall) {
	return false;
}

bool Knight::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

bool Knight::Collision(EmptySpace& emptySpace) {
	return false;
}

bool Knight::Collision(Knight& knight) {
	return true;
}

bool Knight::Collision(Princess& princess) {
	clear();
	while (true) {
		printw("LOSER");
		refresh();
	}
}