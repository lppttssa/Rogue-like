#pragma once
#include "GameObject.h"

class EmptySpace : public GameObject {
public:
	EmptySpace();
	//bool Collision(Knight &knight) override;
	int Collision(Enemy& enemy) override;
	int Collision(Wall& wall) override;
	int Collision(GameObject& gameObj) override;
	int Collision(EmptySpace& emptySpace) override;
	int Collision(Knight& knight) override;
	int Collision(Princess& princess) override;
	int Collision(Fireball& fireball) override;
	int Collision(AidKit& aidKit) override;
};
