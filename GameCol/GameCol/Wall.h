#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall();
	//bool Collision(Knight &knight) override;
	bool Collision(Wall& wall) override;
	bool Collision(GameObject& gameObj) override;
	bool Collision(EmptySpace& emptySpace) override;
	bool Collision(Knight& knight) override;
	bool Collision(Princess& princess) override;
};
