#include "Wall.h"

Wall::Wall() : GameObject('#') {};

int Wall::Collision(Wall &wall) {
	return 0;
}

int Wall::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int Wall::Collision(EmptySpace& emptySpace) {
	return 0;
}

int Wall::Collision(Knight& knight) {
	return 0;
}

int Wall::Collision(Princess& princess) {
	return 0;
}

int Wall::Collision(Enemy& enemy) {
	return 0;
}

int Wall::Collision(Fireball& fireball) {
	return 3;
}