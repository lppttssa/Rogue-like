#include "Fireball.h"

Fireball::Fireball(int hp, int damage, char sym, std::pair<int, int> c, char w) : Character(hp, damage, sym, c), way(w) {}

int Fireball::Collision(Wall& wall) {
	return 3;
}

int Fireball::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int Fireball::Collision(EmptySpace& emptySpace) {
	return 1;
}

int Fireball::Collision(Princess& princess) {
	return 0;
}

int Fireball::Collision(Fireball& fireball) {
	return 0;
}

char Fireball::GetDir() {
	return way;
}