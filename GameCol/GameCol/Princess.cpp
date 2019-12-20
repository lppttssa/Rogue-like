#include "Princess.h"

Princess::Princess() : GameObject('P') {};

bool Princess::Collision(Wall& wall) {
	return false;
}

bool Princess::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

bool Princess::Collision(EmptySpace& emptySpace) {
	return false;
}

bool Princess::Collision(Knight& knight) {
	clear();
	while (true) {
		printw("WINNER");
		refresh();
	}
}

bool Princess::Collision(Princess& princess) {
	return false;
}
