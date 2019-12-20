#include "Wall.h"

Wall::Wall() : GameObject('#') {};

bool Wall::Collision(Wall &wall) {
	return false;
}

bool Wall::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

bool Wall::Collision(EmptySpace& emptySpace) {
	return false;
}

bool Wall::Collision(Knight& knight) {
	return false;
}

bool Wall::Collision(Princess& princess) {
	return false;
}