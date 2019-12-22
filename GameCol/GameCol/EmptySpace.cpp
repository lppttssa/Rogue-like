#include "EmptySpace.h"

EmptySpace::EmptySpace() : GameObject('.') {};

int EmptySpace::Collision(Wall& wall) {
	return 0;
}

int EmptySpace::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int EmptySpace::Collision(EmptySpace& emptySpace) {
	return 0;
}

int EmptySpace::Collision(Knight& knight) {
	return 1;
}

int EmptySpace::Collision(Princess& princess) {
	return 0;
}

int EmptySpace::Collision(Enemy& enemy) {
	return 1;
}