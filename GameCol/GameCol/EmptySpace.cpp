#include "EmptySpace.h"

EmptySpace::EmptySpace() : GameObject('.') {};

bool EmptySpace::Collision(Wall& wall) {
	return false;
}

bool EmptySpace::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

bool EmptySpace::Collision(EmptySpace& emptySpace) {
	return false;
}

bool EmptySpace::Collision(Knight& knight) {
	return true;
}

bool EmptySpace::Collision(Princess& princess) {
	return false;
}