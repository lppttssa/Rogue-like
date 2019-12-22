#include "Knight.h"

Knight::Knight(int hp, int damage, char sym, std::pair<int, int> c) : Character(hp, damage, sym, c) {}

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
