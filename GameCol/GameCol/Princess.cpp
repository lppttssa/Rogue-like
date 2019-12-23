#include "Princess.h"

Princess::Princess() : GameObject('P') {};

int Princess::Collision(Wall& wall) {
	return 0;
}

int Princess::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int Princess::Collision(EmptySpace& emptySpace) {
	return 0;
}

int Princess::Collision(Knight& knight) {
	clear();
	while (true) {
		printw("WINNER");
		refresh();
	}
}

int Princess::Collision(Princess& princess) {
	return 0;
}

int Princess::Collision(Enemy& enemy) {
	return 0;
}

int Princess::Collision(Fireball& fireball) {
	return 0;
}
